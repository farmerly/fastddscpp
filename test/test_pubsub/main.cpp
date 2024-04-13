#include <cstring>
#include <iostream>
#include <memory>

#include "CDDSHandler.h"
#include "DDSConstants.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " sub/pub" << std::endl;
        return -1;
    }

    if (strcmp(argv[1], "sub") == 0) {
        run_dds_data_reader();
    } else if (strcmp(argv[1], "pub") == 0) {
        run_dds_data_writer();
    } else {
        std::cerr << "unknown command: " << argv[1] << std::endl;
    }

    return 0;
}