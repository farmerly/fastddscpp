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

    int index = 0;
    while (true) {
        HelloWorldOne helloOne;
        HelloWorldTwo helloTwo;

        helloOne.id(++index);
        helloOne.message("HelloWorldOne");
        helloTwo.id(++index);
        helloTwo.message("HelloWorldTwo");

        if (handler->publishHelloWorldOne(&helloOne)) {
            LOG(INFO) << "发送 HelloWorldOne 数据成功: " << helloOne.id();
        }
        if (handler->publishHelloWorldTwo(&helloTwo)) {
            LOG(INFO) << "发送 HelloWorldTwo 数据成功: " << helloTwo.id();
        }
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    return 0;
}
