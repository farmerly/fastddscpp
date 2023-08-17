#ifndef TOPIC_DATA_TYPE_CREATOR
#define TOPIC_DATA_TYPE_CREATOR

#include "IDataPacket.h"
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/topic/TopicDataType.hpp>

typedef IDataPacket *(*DataPacketCreateCB)();
typedef void (*DataProcessCB)(IDataPacket *);

class ITopicDataTypeCreator
{
public:
    virtual eprosima::fastdds::dds::TopicDataType *createTopicDataType(std::string typeName) = 0;
    virtual DataPacketCreateCB                     getDataPacketCB(std::string typeName) = 0;
    virtual DataProcessCB                          getDataProcessCB(std::string typeName) = 0;
};

#endif