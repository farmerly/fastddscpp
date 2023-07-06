#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "DDSSharedMemPublisher.h"
#include "DDSSharedMemSubscriber.h"
#include "utils/common.h"
#include <fastrtps/Domain.h>
#include <fastrtps/log/Log.h>

#include "HelloWorldPubSubTypes.h"

using namespace eprosima;
using namespace fastrtps;
using namespace rtps;

#define SEGMENT_SIZE (2 * 1024 * 1024)

void sig_handler(int signum)
{
    Domain::stopAll();
    exit(EXIT_SUCCESS);
}

void test_publisher(int val)
{
    std::cout << "pub 程序启动" << std::endl;

    DDSSharedMemPublisher pub;
    pub.init("pub", SEGMENT_SIZE);
    pub.initPub();

    int i = 1;
    while (true) {
        std::shared_ptr<HelloWorld> data = std::make_shared<HelloWorld>();
        data->index(i);
        data->message("这是推送的 HelloWorld 数据");

        if (pub.publish(data.get(), false)) {
            std::cout << "HelloWorld 推送成功：" << i << std::endl;
        } else {
            std::cout << "HelloWorld 推送失败：" << i << std::endl;
        }
        i++;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void test_subscriber(int val)
{
    std::cout << "sub 程序启动" << std::endl;

    DDSSharedMemSubscriber sub;
    sub.init("sub", SEGMENT_SIZE);
    sub.initSub();

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10 * 1000));
    }
}

int main(int argc, char *argv[])
{
    register_sig(sig_handler);
    if (argc > 1) {
        if (strcmp(argv[1], "pub") == 0) {
            int val = (argc > 2) ? atoi(argv[2]) : 1;
            test_publisher(val);
        } else if (strcmp(argv[1], "sub") == 0) {
            int val = (argc > 2) ? atoi(argv[2]) : 1;
            test_subscriber(val);
        }
    } else {
        test_subscriber(1);
    }

    Domain::stopAll();
    Log::Reset();
    return 0;
}
