#pragma once

#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/topic/Topic.hpp>

template <typename T>
class IDDSTopicDataWriter : public eprosima::fastdds::dds::DataWriter
{
public:
    virtual ~IDDSTopicDataWriter() = default;

public:
    virtual bool initDataWriter(eprosima::fastdds::dds::Publisher           *publisher,
                                eprosima::fastdds::dds::Topic               *topic,
                                const eprosima::fastdds::dds::DataWriterQos &dataWriterQos) = 0;
    virtual bool writeMessage(const T &message) = 0;
};
