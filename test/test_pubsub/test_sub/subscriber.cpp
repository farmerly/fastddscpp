#include "CDDSHandler.h"
#include "DDSConstants.h"
#include <glog/logging.h>
#include <iostream>
#include <memory>

using namespace std;

void helloWorldOneCB(void *args, IDataPacket *data)
{
    LOG(INFO) << "收到数据";
}

void helloWorldTwoCB(void *args, IDataPacket *data)
{
    LOG(INFO) << "收到数据";
}

int main(int argc, char *argv[])
{
    shared_ptr<CDDSDataHandler> handler(new CDDSDataHandler());
    handler->init(127, "test_sub");
    handler->registerDataReader(DDS_TOPIC_HELLO_WORLD_ONE, helloWorldOneCB, nullptr);
    handler->registerDataReader(DDS_TOPIC_HELLO_WORLD_TWO, helloWorldTwoCB, nullptr);

    while (true) {
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    return 0;
}
