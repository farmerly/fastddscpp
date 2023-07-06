#include "HelloWorldConstants.h"
#include "HelloWorldHandler.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    HelloWorldHandler *handler = new HelloWorldHandler();
    if (handler->init(10)) {
        handler->registerPublisher(DDS_TOPIC_HELLO_WORLD_ONE);
    }

    int index = 0;
    while (true) {
        HelloWorldOne helloOne;
        HelloWorldTwo helloTwo;

        helloOne.id(++index);
        helloOne.message("HelloWorldOne");
        helloTwo.id(++index);
        helloTwo.message("HelloWorldTwo");

        if (handler->publish(DDS_TOPIC_HELLO_WORLD_ONE, &helloOne)) {
            std::cout << "Message: " << helloOne.message() << " with index: " << helloOne.id() << " SENT" << std::endl;
        }
        if (handler->publish(DDS_TOPIC_HELLO_WORLD_TWO, &helloTwo)) {
            std::cout << "Message: " << helloTwo.message() << " with index: " << helloTwo.id() << " SENT" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    delete handler;
    return 0;
}
