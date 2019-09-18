#pragma once

#include <cinttypes>
#include <string>

enum class image_output_format
{
    PNG,
    JPEG
};

class image
{
private:
    uint8_t* _data;
    int _w, _h, _ch;
public:
    image(const std::string& path);
    ~image();
    
    void free();
    void write_to_file(const std::string& path, image_output_format fmt);
};