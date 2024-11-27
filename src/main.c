#include <stdio.h>
#include <getopt.h>

#include "image_loader.h"
#include "ascii_u.h"

void print_usage(char *argv[]) {
    printf("Usage: %s -i <png_file> -o <ascii_file>\n", argv[0]);
    printf("\t -i - (required) denote an input PNG file\n");
    printf("\t -o - (required) denote an output ASCII file\n");
}

int main(int argc, char *argv[]) {
    char *input_file = NULL;
    char *output_file = NULL;
    int c;

    while ((c = getopt(argc, argv, "i:o:h")) != -1){
        switch(c){
            case 'i':
                input_file = optarg;
                break;
            case 'o':
                output_file = optarg;
                break;
            case '?':
                printf("Unknown option %c\n", c);
                break;
            case 'h':
                print_usage(argv);
                break;
            default:
                return -1;
        }
    }

    if (input_file == NULL || output_file == NULL){
        printf("Please specify both parameters\n");
        print_usage(argv);
        return 2;
    }

    Image *img = load_png(input_file);

    if(!img){
        fprintf(stderr, "Failed to load PNG file %s\n", input_file);
        return 1;
    }
    convert_to_ascii(img, output_file);
    free_image(img);

    printf("input file is %s\n", input_file);
    printf("output file is %s\n", output_file);
    return 0;
}
