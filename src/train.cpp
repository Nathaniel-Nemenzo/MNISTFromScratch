#include <iostream>
#include <fstream>
#include <assert.h>
#include <unistd.h>

#include "utils.h"

int main(int argc, char **argv) {
    std::string image_file;
    std::string label_file;
    std::string output_file;
    
    // process command line arguments
    for (;;) {
        switch(getopt(argc, argv, "d:l:o:h")) {
            case 'd':
                image_file = optarg;
                continue;
            case 'l':
                label_file = optarg;
                continue;
            case 'o':
                output_file = optarg;
                continue;
            case 'h':
            case '?':
            default:
                std::cout << "[usage]: ./train -d [images] -l [labels] -o [output file for weights]" << std::endl;
                break;
        }
        break;
    }
    
    u_char **image_data = read_mnist_image(image_file);
    u_char *label_data = read_mnist_labels(label_file);

    return 0;
}