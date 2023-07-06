#ifndef _DDS_SHARED_MEM_PUBLISHER_H_H_H
#define _DDS_SHARED_MEM_PUBLISHER_H_H_H

#include "DDSPublisherListener.h"

#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/topic/Topic.hpp>

class DDSSharedMemPublisher
{
public:
    DDSSharedMemPublisher();
    virtual ~DDSSharedMemPublisher();

public:
    bool init(const std::string &participantName, const int &segmentSize);
    bool initPub();
    bool publish(void *data, bool waitForListener = true);

private:
    eprosima::fastdds::dds::DomainParticipant *participant_;
    eprosima::fastdds::dds::Publisher *publisher_;

    eprosima::fastdds::dds::Topic *topic_;
    eprosima::fastdds::dds::DataWriter *writer_;
    DDSPublisherListener listener_;
};

#endif // _DDS_SHARED_MEM_PUBLISHER_H_H_H
