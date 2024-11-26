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
}