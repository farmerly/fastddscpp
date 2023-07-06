#include <iostream>
using namespace std;

#include <unistd.h>

#ifdef HAVE_LOG_NO_INFO
    #undef HAVE_LOG_NO_INFO
#endif

#include "HelloWorldPublisher.h"
#include "HelloWorldSubscriber.h"

void sub_process(int i)
{
    pid_t pid = fork();
    if (pid == 0) {
        HelloWorldSubscriber *mysub = new HelloWorldSubscriber();
        if (mysub->init("hello", 8811, false)) {
            mysub->run();
        }
        delete mysub;
    }
}

void sub_thread(int i)
{
    HelloWorldSubscriber *mysub = new HelloWorldSubscriber();
    if (mysub->init("hello", 8811, false)) {
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
            if (mypub->init(8811, false)) {
                mypub->run();
            }
            delete mypub;
        } else if (strcmp(argv[1], "sub") == 0) {
            std::cout << "Starting subscriber." << std::endl;
            std::thread threadList[threadNum];
            for (int i = 0; i < threadNum; i++) {
                threadList[i] = std::thread(sub_thread, i);
            }
            for (int i = 0; i < threadNum; i++) {
                threadList[i].join();
            }
        } else {
            cout << "需要输入 pub 或者 sub" << endl;
        }
    } else {
        cout << "需要输入 pub 或者 sub" << endl;
    }

    return 0;
}
