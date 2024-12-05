### ASCII U BABY v0.0.1

**ASCIIUBaby** is a simple C application that converts images to ASCII art.
Currently only PNG files are supported (using libpng).
The only purpose for its existence is an unhealthy late-in-life curiosity towards C.

#### Build
* To build, run 'make' in the project directory.
* To test, run 'make test' in the project directory.
* To clean-up after build and test, run 'make clean' in the project directory.

#### Use
The application takes 3 command line arguments:

* -i input_file
* -o output_file
* -s output file scale height (in chars): 1-...

More weapons coming soon (including unit tests).

##### Note
1. Latest binary version also included in the bin directory just in case
2. Only tested on Linux atm