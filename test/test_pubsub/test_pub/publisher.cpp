#include "CDDSHandler.h"
#include "CPcSrcData.h"
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
    handler->registerDataWriter(DDS_TOPIC_CPCSRC_TIMEMATCH);

    int                  index = 0;
    std::vector<uint8_t> vecPoints(10000000);

    CPcSrcDataTimeMatch timeMatchData;
    for (int i = 0; i < 1; i++) {
        CPcSrcData data;
        for (int j = 0; j < 35200; j++) {
            CPcPoint point;
            data.vecPoints().push_back(point);
        }
        timeMatchData.vecSrcData().push_back(data);
    }

    while (true) {
        HelloWorldOne helloOne;
        helloOne.index(++index);
        helloOne.points(vecPoints);
        if (handler->publishHelloWorldOne(&helloOne)) {
            LOG(INFO) << "发送 HelloWorldOne 数据成功: " << helloOne.index();
        } else {
            LOG(INFO) << "\033[31m发送 HelloWorldOne 数据失败: " << helloOne.index() << "\033[0m";
        }

        ChildData child;
        child.baseId(index);
        child.childId(index);
        HelloWorldTwo helloTwo;
        helloTwo.index(++index);
        helloTwo.children().push_back(child);
        helloTwo.message("HelloWorldTwo");
        if (handler->publishHelloWorldTwo(&helloTwo)) {
            LOG(INFO) << "发送 HelloWorldTwo 数据成功: " << helloTwo.index();
        } else {
            LOG(INFO) << "\033[31m发送 HelloWorldTwo 数据失败: " << helloTwo.index() << "\033[0m";
        }

        timeMatchData.unFrameId(++index);
        if (handler->publishCPcSrcTimeMatch(&timeMatchData)) {
            LOG(INFO) << "发送 CPcSrcDataTimeMatch 数据成功: " << timeMatchData.getCdrSerializedSize(timeMatchData);
        } else {
            LOG(INFO) << "\033[31m发送 CPcSrcDataTimeMatch 数据失败: " << timeMatchData.getCdrSerializedSize(timeMatchData) << "\033[0m";
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    return 0;
}
