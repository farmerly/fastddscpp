#include "DDSSubscriberListener.h"

DDSSubscriberListener::DDSSubscriberListener()
{
}

DDSSubscriberListener::~DDSSubscriberListener()
{
}

void DDSSubscriberListener::on_subscription_matched(eprosima::fastdds::dds::DataReader *reader,
                                                    const eprosima::fastdds::dds::SubscriptionMatchedStatus &info)
{
    if (info.current_count_change == 1) {
        std::cout << "Subscriber matched." << std::endl;
    } else if (info.current_count_change == -1) {
        std::cout << "Subscriber unmatched." << std::endl;
    } else {
        std::cout << info.current_count_change << " is not a valid value for SubscriptionMatchedStatus current count change" << std::endl;
    }
}

void DDSSubscriberListener::on_data_available(eprosima::fastdds::dds::DataReader *reader)
{
    auto hello = std::make_shared<HelloWorld>();
    eprosima::fastdds::dds::SampleInfo info;
    if (reader->take_next_sample(hello.get(), &info) == eprosima::fastrtps::types::ReturnCode_t::RETCODE_OK) {
        if (info.valid_data) {
            std::cout << "Message: " << hello->message() << " with index: " << hello->index() << " RECEIVED." << std::endl;
        }
    }
}
