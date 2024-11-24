#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

typedef struct {
    unsigned char *data;
    int width;
    int height;
} Image;

Image *load_png(const char *file_path);
void free_image(Image *img);

#endif
