#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "image_loader.h"
#include "ascii_u.h"

int compare_files(const char *file1, const char *file2){
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");
    if(!f1 || !f2){
        if (f1) fclose(f1);
        if (f2) fclose(f2);
        return 0;
    }

    char line1[1024], line2[1024];
    while(fgets(line1, sizeof(line1),f1) && fgets(line2, sizeof(line2), f2)) {
        if(strcmp(line1, line2) != 0){
            fclose(f1);
            fclose(f2);
            return 0;
        }
    }
    int result = feof(f1) && feof(f2);
    fclose(f1);
    fclose(f2);
    return result;
}

int main() {
    //const char *input_image = "tests/test_image.png";
    const char *output_file = "tests/output_ascii.txt";

    const char *expected_ascii_30 = "tests/expected_ascii.txt";
   system("./bin/ascii_u_baby -i tests/test_image.png -o tests/output_ascii.txt -s 30");
    if(compare_files(output_file, expected_ascii_30)){
        printf("Integration tests (Height is 30) passed\n");
    } else {
        printf("Integration tests (Height is 30) failed - file contents do not match\n");
        return 1;
    }

    const char *golden_ascii_50 = "tests/golden_ascii_50.txt";
    system("./bin/ascii_u_baby -i tests/test_image.png -o tests/output_ascii.txt -s 50");
    if(compare_files(output_file, golden_ascii_50)){
        printf("Integration tests (Height is 50) passed\n");
    } else {
        printf("Integration tests (Height is 50) failed - file contents do not match\n");
        return 1;
    }

    printf("All integration tests passed!\n");
    return 0;
}
