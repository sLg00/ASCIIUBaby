#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "image_loader.h"
#include "ascii_u.h"

void test_scaling() {

    int original_width = 300;
    int original_height = 300;
    int target_height = 30;


    const double aspect_ratio = 2.0;
    int scaled_width = (int)(original_width * (target_height * aspect_ratio) / original_height);

    assert(scaled_width == 60);

    printf("test_scaling passed\n");
}

void test_gsc_ascii_mapping() {
    const char *ascii_characters = "@%#*+=-:. ";
    double grayscale = 127.5;
    int ascii_idx = (int)(grayscale / 256.0 * (strlen(ascii_characters) -1));
    char ascii_char = ascii_characters[ascii_idx];

    assert(ascii_char == '+');

    printf("test_gsc_ascii_mapping passed\n");
}

int main(){
    test_scaling();
    test_gsc_ascii_mapping();
    printf("All unit tests passed\n");
    return 0;
}