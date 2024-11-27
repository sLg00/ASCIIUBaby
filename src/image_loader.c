#include <stdio.h>
#include <stdlib.h>
#include <png.h>

#include "image_loader.h"

Image *load_png(const char *file_path){
    FILE *fp = fopen(file_path,"rb");
    if(!fp) {
        fprintf(stderr, "Failed to open file %s\n", file_path);
        return NULL;
    }

    unsigned char header[8];
    fread(header, 1, 8, fp);
    if(png_sig_cmp(header, 0, 8)) {
        fprintf(stderr, "File is not a valid PNG: %s\n", file_path);
        fclose(fp);
        return NULL;
    }

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info = png_create_info_struct(png);
    if (!png || !info){
        fclose(fp);
        return NULL;
    }

    //set up a setjmp point in case loading the png runs into errors
    if (setjmp(png_jmpbuf(png))) {
        png_destroy_read_struct(&png, &info, NULL);
        fclose(fp);
        return NULL;
    }

    png_init_io(png, fp);
    png_set_sig_bytes(png, 8);
    png_read_info(png, info);

    //retrieve image properties
    int width = png_get_image_width(png, info);
    int height = png_get_image_height(png, info);
    png_byte color_type = png_get_color_type(png, info);
    png_byte bit_depth = png_get_bit_depth(png, info);

    //ensure a standardized image format (8 bit RGBA) and update the metadata in info
    if(bit_depth == 16) png_set_strip_16(png);
    if(color_type == PNG_COLOR_TYPE_PALETTE) png_set_palette_to_rgb(png);
    if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) png_set_expand_gray_1_2_4_to_8(png);
    if(png_get_valid(png, info, PNG_INFO_tRNS)) png_set_tRNS_to_alpha(png);
    if(color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY)
        png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

    png_read_update_info(png, info);

    //allocate memory for the data
    unsigned char *data = (unsigned char *)malloc(png_get_rowbytes(png, info) * height);

    //set up row pointers for libpng to utilize
    png_bytep *row_pointers =  (png_bytep *)malloc(sizeof (png_bytep) * height);
    for(int i = 0; i < height; i++){
        row_pointers[i] = data + i * png_get_rowbytes(png, info);
    }

    //read image data into the data buffer
    png_read_image(png, row_pointers);
    free(row_pointers);
    png_destroy_read_struct(&png, &info, NULL);
    fclose(fp);

    //create an image structure with the required attributes
    Image *image = (Image *)malloc(sizeof(Image));
    image->data = data;
    image->width = width;
    image->height = height;

    return image;
}

// free up memory related to image data and the image structure itself
void free_image(Image *img){
    if(img){
        free(img->data);
        free(img);
    }
}




