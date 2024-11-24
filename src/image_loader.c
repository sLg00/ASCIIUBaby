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
}



