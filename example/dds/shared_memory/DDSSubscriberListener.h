#ifndef _DDS_SUBSCRIBER_LISTENER_H_H_H
#define _DDS_SUBSCRIBER_LISTENER_H_H_H

#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>

class DDSSubscriberListener : public eprosima::fastdds::dds::DataReaderListener
{
public:
    DDSSubscriberListener();
    ~DDSSubscriberListener();
    void on_subscription_matched(eprosima::fastdds::dds::DataReader *reader, const eprosima::fastdds::dds::SubscriptionMatchedStatus &info);
    // 消息处理
    void on_data_available(eprosima::fastdds::dds::DataReader *reader);
    // DataWriter 活跃状态变更
    void on_liveliness_changed(eprosima::fastdds::dds::DataReader *reader, const eprosima::fastrtps::LivelinessChangedStatus &status);

public:
    int getMatched()
    {
        return _matched;
    };

private:
    int _matched;
};

#endif // _DDS_SUBSCRIBER_LISTENER_H_H_H