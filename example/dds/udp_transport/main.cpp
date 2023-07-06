#include <iostream>
using namespace std;

#include "HelloWorldPublisher.h"
#include "HelloWorldSubscriber.h"

void sub_thread()
{
    std::thread::id tid = std::this_thread::get_id();
    std::cout << "当前线程ID: " << tid << std::endl;

    HelloWorldSubscriber *mysub = new HelloWorldSubscriber();
    if (mysub->init()) {
        mysub->run();
    }
    delete mysub;
}

int main(int argc, char *argv[])
{
    int threadNum = 1;
    if (argc > 1) {
        if (strcmp(argv[1], "pub") == 0) {
            std::cout << "Starting publisher." << std::endl;

            HelloWorldPublisher *mypub = new HelloWorldPublisher();
            if (mypub->init()) {
                mypub->run();
            }
            delete mypub;
        } else if (strcmp(argv[1], "sub") == 0) {
            std::cout << "Starting subscriber." << std::endl;
            std::thread threadList[threadNum];
            for (int i = 0; i < threadNum; i++) {
                threadList[i] = std::thread(sub_thread);
            }
            for (int i = 0; i < threadNum; i++) {
                threadList[i].join();
            }
        } else {
            cout << "需要输入 pub 或者 sub" << endl;
        }
    } else {
        cout << "需要输入 pub 或者 sub" << endl;
        return 0;
    }

    return 0;
}