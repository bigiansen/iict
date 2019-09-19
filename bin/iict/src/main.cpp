#include <cinttypes>
#include <iostream>
#include <mutex>
#include <set>
#include <thread>

#include <strutils/strutils.hpp>
#include <ien/task_queue.hpp>

#include <stb_image.h>
#include <stb_image_write.h>

#include "image.hpp"
#include "std_filesystem.hpp"

typename std::uint8_t u8;

int main(int argc, char** argv)
{
    if(argc < 3)
    {
        std::cerr << "Not enough arguments!" << std::endl;
        return -1;
    }

    unsigned int max_threads = std::thread::hardware_concurrency();

    // +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    image_output_format fmt;
    std::string ofmt_str(argv[1]);
    strutils::to_lower_in_place(ofmt_str);
    if(ofmt_str == ".jpg" || ofmt_str == ".jpeg")
    {
        fmt = image_output_format::JPEG;
    }
    else if(ofmt_str == ".png")
    {
        fmt = image_output_format::PNG;
    }
    else
    {
        std::cerr << "Invalid output format parameter! -> " << ofmt_str << std::endl;
        return -2;
    }
    
    std::set<std::string> supported_extensions;
    for(int i = 2; i < argc; ++i)
    {
        supported_extensions.emplace(strutils::to_lower(std::string(argv[i])));
    }
    // +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    
    auto current_dir = STDFS_NAMESPACE::current_path();
    std::set<std::string> paths;
    for(auto& entry : STDFS_NAMESPACE::directory_iterator(current_dir))
    {
        if(supported_extensions.count(entry.path().extension().string()))
        {
            paths.emplace(entry.path().u8string());
        }
    }

    ien::task_queue queue;
    std::mutex paths_mux;
    std::mutex cout_mux;
    auto thread_lambda = [&]() 
    {
        STDFS_NAMESPACE::path path;
        paths_mux.lock();
        {
            path = STDFS_NAMESPACE::path(*(paths.begin()));
            paths.erase(paths.begin());
        }
        paths_mux.unlock();

        image img(path.string());
        path.replace_extension(ofmt_str);

        cout_mux.lock();
        std::cout << ">> " << path.string() << std::endl;
        cout_mux.unlock();

        img.write_to_file(path.string(), fmt);
    };

    for(size_t i = 0; i < paths.size(); ++i)
    {
        queue.emplace_back(thread_lambda);
    }
    queue.run();

    std::cout << "Finished!" << std::endl;
}