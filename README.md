### ASCII U BABY v0.0.1

**ASCIIUBaby** is a simple C application that converts images to ASCII art.
Currently only PNG files are supported (using libpng).
The only purpose for its existence is an unhealthy late-in-life curiosity towards C.

#### Build
* NOTE: libpng is required to build
* To build, run 'make' in the project directory.
* To run unit tests, run 'make test-unit' in the project directory.
* To run integration tests, run 'make test-integration' in the project directory.
* To clean-up after build and test, run 'make clean' in the project directory.

For MacOS, you may install `libpng` using Homebrew.

#### Use
The application takes 4 command line arguments:

* -i input_file
* -o output_file
* -s output file scale height (in chars): 1-...
* -h help



##### Notes
1. Only tested on Linux atm
2. JPEG support next