#ifndef TOPIC_DATA_TYPE_CREATOR
#define TOPIC_DATA_TYPE_CREATOR

#include "IDataPacket.h"
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/topic/TopicDataType.hpp>

typedef IDataPacket *(*DataPacketCreateCB)();
typedef void (*DataPacketProcessCB)(void *, IDataPacket *);

class ITopicDataTypeCreator
{
public:
    ITopicDataTypeCreator() = default;
    virtual ~ITopicDataTypeCreator() = default;

public:
    virtual eprosima::fastdds::dds::TopicDataType *createTopicDataType(std::string typeName) = 0;
    virtual DataPacketCreateCB                     getDataPacketCreateCB(std::string typeName) = 0;
};

#endif