#include <fastrtps/rtps/RTPSDomain.h>
#include <stdio.h>

#include <bitset>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>

#include "RTPSReaderRegister.h"
#include "RTPSWriterRegister.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc > 1) {
        if (strcmp(argv[1], "writer") == 0) {
            RTPSWriterRegister writer;
            if (writer.init() && writer.reg()) {
                writer.run(10);
            }
        } else if (strcmp(argv[1], "reader") == 0) {
            RTPSReaderRegister reader;
            if (reader.init() && reader.reg()) {
                reader.run();
            }
        } else {
            cout << "error code, 需要输入 writer 或者 reader" << endl;
        }
    } else {
        cout << "需要输入 writer 或者 reader" << endl;
        return 0;
    }

    eprosima::fastrtps::rtps::RTPSDomain::stopAll();
    return 0;
}