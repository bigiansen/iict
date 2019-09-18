#pragma once

#if __has_include(<filesystem>)
    #include <filesystem>
    #define STDFS_NAMESPACE std::filesystem
#elif __has_include(<experimental/filesystem>)
    #warning "Using <experimental/filesystem>"
    #include <experimental/filesystem>
    #define STDFS_NAMESPACE std::experimental::filesystem
#else
    #error "<filesytem> header was not found!"
#endif