#pragma once

#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/topic/Topic.hpp>

template <typename T>
class IDDSTopicDataReader : public eprosima::fastdds::dds::DataReader
{
    typedef std::function<void(std::shared_ptr<T>)> ProcessCallback;

public:
    virtual ~IDDSTopicDataReader() = default;

public:
    virtual bool initDataReader(eprosima::fastdds::dds::Subscriber          *subscriber,
                                eprosima::fastdds::dds::Topic               *topic,
                                ProcessCallback                              callback,
                                const eprosima::fastdds::dds::DataReaderQos &dataReaderQos) = 0;
};