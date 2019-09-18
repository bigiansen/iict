# iict - Ien's Image Converter Tool

Usage:
Works by enumerating the current directory's files and comparing the file extensions with the supplied arguments.

```sh
iict output_format(.jpg/.jpeg or .png) [file extension filters]
```

- The arguments non case-sensitive.

- Allowed input image formats are ([stb_image](https://github.com/nothings/stb/blob/master/stb_image.h)):
    - `JPEG`, `PNG`, `TGA`, `BMP`, `PSD`, `GIF`, `HDR`, `PIC`, `PNM`
    
- The allowed output format arguments are:
  - ` .jpg/.jpeg` 
  - ` .png`
  
- The file extension filters are used textually and do not represent formats, 
this means that if you want to convert all jpeg files, you should provide all possible extension representations (`.jpg`, `.jpeg`, etc.).

- Files that correspond to the supplied extension filters that are not images, or are not supported by
`stb_image` are ignored.

## Examples:

Convert all .jfif images to .jpg:

```
iict .jpg .jfif
```

Convert all .jpg images to .png:

```
iict .png .jpg .jpeg
```
