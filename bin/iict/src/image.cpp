#include "image.hpp"

#include <stb_image.h>
#include <stb_image_write.h>

static const int DESIRED_CHANNELS = 4;

image::image(const std::string& path)
{
    _data = stbi_load(path.c_str(), &_w, &_h, &_ch, DESIRED_CHANNELS);
}

image::~image()
{
    free();
}

void image::free()
{
    if(_data != nullptr)
    {
        stbi_image_free(_data);
    }
}

void image::write_to_file(const std::string& path, image_output_format fmt)
{
    if(_data == nullptr) { return; }
    switch (fmt)
    {
        case image_output_format::JPEG:
            stbi_write_jpg(path.c_str(), _w, _h, DESIRED_CHANNELS, _data, 100);
            break;
        case image_output_format::PNG:
            stbi_write_png(path.c_str(), _w, _h, DESIRED_CHANNELS, _data, _w * DESIRED_CHANNELS);
            break;
    }
}
