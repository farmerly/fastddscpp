#include <glog/logging.h>
#include <iostream>
#include <memory>

#include "CDDSHandler.h"
#include "DDSConstants.h"
#include "HelloWorldOne.h"
#include "HelloWorldTwo.h"

using namespace std;

// void helloWorldOneCB(void *args, IDDSDataPacket *packet)
// {
//     HelloWorldOne *data = (HelloWorldOne *)packet->moveData();
//     LOG(INFO) << "收到 HelloWorldOne 数据: " << data->index() << ", size: " << data->getCdrSerializedSize(*data);
//     delete data;
// }

// void helloWorldTwoCB(void *args, IDDSDataPacket *packet)
// {
//     HelloWorldTwo *data = (HelloWorldTwo *)packet->moveData();
//     LOG(INFO) << "收到 HelloWorldTwo 数据: " << data->index() << ", size: " << data->getCdrSerializedSize(*data);
//     delete data;
// }

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " sub/pub" << std::endl;
        return -1;
    }

    if (strcmp(argv[1], "sub") == 0) {
        //     shared_ptr<CDDSDataHandler> handler(new CDDSDataHandler());
        //     handler->init(127, "test_sub");
        //     handler->registerDataReader(DDS_TOPIC_HELLO_WORLD_ONE, helloWorldOneCB, nullptr);
        //     handler->registerDataReader(DDS_TOPIC_HELLO_WORLD_TWO, helloWorldTwoCB, nullptr);

        //     while (true) {
        //         this_thread::sleep_for(chrono::milliseconds(500));
        //     }
        run_dds_data_reader();
    } else {
        run_dds_data_writer();
        //     shared_ptr<CDDSDataHandler> handler(new CDDSDataHandler());
        //     handler->init(127, "test_pub");
        //     handler->registerDataWriter(DDS_TOPIC_HELLO_WORLD_ONE);
        //     handler->registerDataWriter(DDS_TOPIC_HELLO_WORLD_TWO);

        //     int                  index = 0;
        //     std::vector<uint8_t> vecPoints(10000000);

        //     while (true) {
        //         HelloWorldOne helloOne;
        //         helloOne.index(++index);
        //         helloOne.points(vecPoints);
        //         if (handler->publishHelloWorldOne(&helloOne)) {
        //             LOG(INFO) << "发送 HelloWorldOne 数据成功: " << helloOne.getCdrSerializedSize(helloOne);
        //         } else {
        //             LOG(INFO) << "\033[31m发送 HelloWorldOne 数据失败: " << helloOne.index() << "\033[0m";
        //         }

        //         ChildData child;
        //         child.baseId(index);
        //         child.childId(index);
        //         HelloWorldTwo helloTwo;
        //         helloTwo.index(++index);
        //         helloTwo.children().push_back(child);
        //         helloTwo.message("HelloWorldTwo");
        //         if (handler->publishHelloWorldTwo(&helloTwo)) {
        //             LOG(INFO) << "发送 HelloWorldTwo 数据成功: " << helloTwo.getCdrSerializedSize(helloTwo);
        //         } else {
        //             LOG(INFO) << "\033[31m发送 HelloWorldTwo 数据失败: " << helloTwo.index() << "\033[0m";
        //         }
        //         this_thread::sleep_for(chrono::milliseconds(100));
        //     }
    }

    return 0;
}