#include "CDDSHandler.h"
#include "DDSConstants.h"
#include <glog/logging.h>
#include <iostream>
#include <memory>

using namespace std;

int main(int argc, char *argv[])
{
    shared_ptr<CDDSDataHandler> handler(new CDDSDataHandler());
    handler->init(127, "test_pub");
    handler->registerDataWriter(DDS_TOPIC_HELLO_WORLD_ONE);
    handler->registerDataWriter(DDS_TOPIC_HELLO_WORLD_TWO);

    int                  index = 0;
    std::vector<uint8_t> vecPoints(10000000);
    while (true) {
        HelloWorldOne helloOne;
        helloOne.index(++index);
        helloOne.points(vecPoints);
        if (handler->publishHelloWorldOne(&helloOne)) {
            LOG(INFO) << "发送 HelloWorldOne 数据成功: " << helloOne.index();
        } else {
            LOG(INFO) << "\033[31m发送 HelloWorldOne 数据失败: " << helloOne.index() << "\033[0m";
        }

        HelloWorldTwo helloTwo;
        helloTwo.index(++index);
        helloTwo.message("HelloWorldTwo");
        if (handler->publishHelloWorldTwo(&helloTwo)) {
            LOG(INFO) << "发送 HelloWorldTwo 数据成功: " << helloTwo.index();
        } else {
            LOG(INFO) << "\033[31m发送 HelloWorldTwo 数据失败: " << helloTwo.index() << "\033[0m";
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    return 0;
}
