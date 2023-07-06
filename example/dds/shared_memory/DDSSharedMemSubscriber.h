#ifndef _DDS_SHARED_MEM_SUBSCRIBER_H_H_H
#define _DDS_SHARED_MEM_SUBSCRIBER_H_H_H

#include "DDSSubscriberListener.h"

#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/topic/Topic.hpp>

class DDSSharedMemSubscriber
{
public:
    DDSSharedMemSubscriber();
    virtual ~DDSSharedMemSubscriber();

public:
    bool init(const std::string &participantName, const int &segmentSize);
    eprosima::fastdds::dds::Topic *createTopic();
    bool initSub();

private:
    eprosima::fastdds::dds::DomainParticipant *participant_;
    eprosima::fastdds::dds::Subscriber *subscriber_;

    eprosima::fastdds::dds::Topic *topic_;
    eprosima::fastdds::dds::DataReader *reader_;
    DDSSubscriberListener listener_;
};

#endif // _DDS_SHARED_MEM_SUBSCRIBER_H_H_H
