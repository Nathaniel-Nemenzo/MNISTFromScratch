#include "utils.h"

int reverse_int(int i) {
    // declare and store 1-byte quantities
    unsigned char c1, c2, c3, c4;
    c1 = i & 0xFF;
    c2 = (i >> 8) & 0xFF;
    c3 = (i >> 16) & 0xFF;
    c4 = (i >> 24) & 0xFF;

    // add and return
    return ((int) c1 << 24) + ((int) c2 << 16) + ((int) c3 << 8) + c4;
}

u_char **read_mnist_image(const std::string &file_name) {
    std::ifstream file(file_name, std::ios::binary);

    // read magic and metadata
    uint32_t magic_number, num_images, num_rows, num_cols;
    if (file.is_open()) {
        file.read((char *)&magic_number, sizeof(magic_number));
        // magic_number is stored in MSB, so we have to reverse to get MSB format
        magic_number = reverse_int(magic_number);
        if (magic_number != 2051) {
            std::cout << "ERROR: Incorrect magic number for mnist images file" << file_name << std::endl;
            throw;
        }
        // read number of images
        file.read((char *)&num_images, sizeof(num_images));
        num_images = reverse_int(num_images);
        // read number of rows
        file.read((char *)&num_rows, sizeof(num_rows));
        num_rows = reverse_int(num_rows);
        // read number of columns
        file.read((char *)&num_cols, sizeof(num_cols));
        num_cols = reverse_int(num_cols);
        // create output
        u_char **images = new u_char*[num_images];
        // read in images
        for (size_t i = 0; i < num_images; i++) {
            images[i] = new u_char[num_rows * num_cols];
            // read into images[i]
            file.read((char *)&images[i], num_rows * num_cols);
        }

        return images;
    } else {
        std::cout << "ERROR: Cannot open file " << file_name << std::endl;
        throw;
    }    
}

u_char *read_mnist_labels(const std::string &file_name) {
    std::ifstream file(file_name, std::ios::binary);

    // read magic and metadata
    uint32_t magic_number, num_labels;
    if (file.is_open()) {
        // read in magic number
        file.read((char *)&magic_number, sizeof(magic_number));
        magic_number = reverse_int(magic_number);
        if (magic_number != 2049) {
            std::cout << "ERROR: Incorrect magic number for mnist labels file" << file_name << std::endl;
            throw;
        }
        // read in number of labels
        file.read((char *)&num_labels, sizeof(num_labels));
        num_labels = reverse_int(num_labels);
        // create output
        u_char *labels = new u_char[num_labels];
        // read in labels
        for (size_t i = 0; i < num_labels; i++) {
            file.read((char *)&labels[i], 1);
        }
        return labels;
    } else {
        std::cout << "ERROR: Cannot open file " << file_name << std::endl;
        throw;
    }
}

int process_cmd_args(int argc, char **argv) {
    static const std::string TRAIN = "train";
    static const std::string TEST = "test";
    
    if (std::string(argv[1]) == TRAIN) {
        return 0;
    } else if (std::string(argv[1]) == TEST) {
        return 1;
    } else {
        return 2;
    }
}