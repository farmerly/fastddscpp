#include "DDSSubscriberListener.h"
#include "HelloWorld.h"

#include <fastdds/dds/subscriber/SampleInfo.hpp>
#include <memory>

using namespace eprosima::fastdds::dds;

DDSSubscriberListener::DDSSubscriberListener()
{
    _matched = 0;
}

DDSSubscriberListener::~DDSSubscriberListener()
{
}

void DDSSubscriberListener::on_subscription_matched(DataReader *reader, const SubscriptionMatchedStatus &info)
{
    if (info.current_count_change == 1) {
        _matched++;
        std::cout << "Subscriber matched" << std::endl;
    } else if (info.current_count_change == -1) {
        _matched--;
        std::cout << "Subscriber unmatched" << std::endl;
    } else {
        std::cout << info.current_count_change << " is not a valid value for SubscriptionMatchedStatus current count change" << std::endl;
    }
}

void DDSSubscriberListener::on_data_available(DataReader *reader)
{
    HelloWorld hello;
    SampleInfo info;

    if (reader->take_next_sample(&hello, &info) == ReturnCode_t::RETCODE_OK) {
        if (info.valid_data) {
            std::cout << "Received Message: index, " << hello.index() << ", " << hello.message() << std::endl;
        }
    }
}

void DDSSubscriberListener::on_liveliness_changed(eprosima::fastdds::dds::DataReader *reader,
                                                  const eprosima::fastrtps::LivelinessChangedStatus &status)
{
    std::cout << "on_liveliness_changed: " << status.alive_count << std::endl;
}