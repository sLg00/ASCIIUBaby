#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "image_loader.h"
#include "ascii_u.h"

void trim_whitespace(char *line) {
    size_t len = strlen(line);
    while (len > 0 && isspace((unsigned char)line[len - 1])) {
        line[len - 1] = '\0';
        len--;
    }
}

int compare_files(const char *file1, const char *file2) {
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");
    if (!f1 || !f2) {
        printf("Failed to open files: %s or %s\n", file1, file2);
        if (f1) fclose(f1);
        if (f2) fclose(f2);
        return 0;
    }

    char line1[1024], line2[1024];
    while (1) {
        char *res1 = fgets(line1, sizeof(line1), f1);
        char *res2 = fgets(line2, sizeof(line2), f2);
        if (res1) {
            trim_whitespace(line1);
        }
        if (res2) {
            trim_whitespace(line2);
        }

        // If one file ends earlier, mismatch
        if ((res1 == NULL) != (res2 == NULL)) {
            printf("Files end at different points!\n");
            fclose(f1);
            fclose(f2);
            return 0;
        }

        // If both are NULL, we reached EOF
        if (res1 == NULL && res2 == NULL) break;

        // Compare the trimmed lines
        if (strcmp(line1, line2) != 0) {
            fclose(f1);
            fclose(f2);
            return 0;
        }
    }

    fclose(f1);
    fclose(f2);
    return 1;
}

int main() {
    const char *output_file = "tests/output_ascii.txt";

    const char *expected_ascii_30 = "tests/expected_ascii_30.txt";
    system("./bin/ascii_u_baby -i tests/test_image.png -o tests/output_ascii.txt -s 30");


    if (compare_files(output_file, expected_ascii_30)) {
        printf("Integration tests (Height is 30) passed\n");
    } else {
        printf("Integration tests (Height is 30) failed - file contents do not match\n");
        return 1;
    }

    const char *golden_ascii_50 = "tests/golden_ascii_50.txt";
    system("./bin/ascii_u_baby -i tests/test_image.png -o tests/output_ascii.txt -s 50");

    if (compare_files(output_file, golden_ascii_50)) {
        printf("Integration tests (Height is 50) passed\n");
    } else {
        printf("Integration tests (Height is 50) failed - file contents do not match\n");
        return 1;
    }

    printf("All integration tests passed!\n");
    return 0;
}
