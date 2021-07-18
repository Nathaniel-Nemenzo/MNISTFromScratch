#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <string>

/* reverse_int(): converts from little -> big endian or big -> little endian depending on what form is passed in
*/
int reverse_int(int i);

/* read_mnist_image(): reads mnist images into a uchar[]*
*/
u_char **read_mnist_image(const std::string &filename);

/* read_mnist_labels(): reads mnist labels into a uchar[]
*/
u_char *read_mnist_labels(const std::string &filename);

/* process_cmd_args(): processes command line arguments:
        0: train
        1: test
*/
int process_cmd_args(int argc, char **argv);

#endif