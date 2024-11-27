#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ascii_u.h"

// ascii chars from darkest to lightest
const char *ascii_characters = "@%#*+=-:. ";

void convert_to_ascii(const Image *img, const char *output_path){
    FILE *output_file = fopen(output_path, "w");
    if(!output_file){
        fprintf(stderr, "Failed to open output file: %s\n", output_path);
        return;
    }

    //scale image so it would look proportionate as an ascii representation
    const double aspect_ratio = 2.0;
    int scaled_width = img->width;
    int scaled_height = (int)(img->height / aspect_ratio);

    /*Loop through scaled dimensions of the image.
    Outer loop - vertical pixels, inner loop - horizontal pixels (hence the y, x notation for variables).
    Then map scaled pixels to original pixels.
    Then access pixels of the original image and extract red, green and blue channels of each pixel
    Then convert to grayscale using the luminance formula.
    Then map grayscale to ASCII.
    Then write outputs.
    */

    for(int y=0; y<scaled_height; y++){
        for(int x=0; x < scaled_width; x++){

           int original_y = (int)(y * aspect_ratio);
           int original_x = x;

           int index = (original_y * img->width + original_x) * 4;
           unsigned char r = img->data[index];
           unsigned char g = img->data[index + 1];
           unsigned char b = img->data[index + 2];

           double grayscale = 0.299 * r + 0.587 * g + 0.114 * b;
           int ascii_index = (int)(grayscale / 256.0 * (strlen(ascii_characters) -1));
           char ascii_char = ascii_characters[ascii_index];

           fputc(ascii_char, output_file);
        }
        fputc('\n', output_file);
    }

    fclose(output_file);
    printf("ASCII representation saved to: %s\n", output_path);
}