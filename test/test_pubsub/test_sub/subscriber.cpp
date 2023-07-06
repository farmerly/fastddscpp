#include "HelloWorldConstants.h"
#include "HelloWorldHandler.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    HelloWorldHandler *handler = new HelloWorldHandler();
    if (handler->init(10)) {
        handler->registerSubscriber(DDS_TOPIC_HELLO_WORLD_ONE);
    }
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    delete handler;
    return 0;
}
