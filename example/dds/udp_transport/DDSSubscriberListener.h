#ifndef _DDS_SUBSCRIBER_LISTENER_H_H_H
#define _DDS_SUBSCRIBER_LISTENER_H_H_H

#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>

#include "HelloWorld.h"

class DDSSubscriberListener : public eprosima::fastdds::dds::DataReaderListener
{
public:
    DDSSubscriberListener();
    ~DDSSubscriberListener();

public:
    void on_subscription_matched(eprosima::fastdds::dds::DataReader *reader, const eprosima::fastdds::dds::SubscriptionMatchedStatus &info);
    void on_data_available(eprosima::fastdds::dds::DataReader *reader);
};

#endif // _DDS_SUBSCRIBER_LISTENER_H_H_H
