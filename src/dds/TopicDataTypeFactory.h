#ifndef TOPIC_DATA_TYPE_FACTORY_H_H_H
#define TOPIC_DATA_TYPE_FACTORY_H_H_H

#include "TopicDataTypeCreator.h"

class TopicDataTypeFactory
{
public:
    TopicDataTypeFactory(TopicDataTypeCreator *creator);
    ~TopicDataTypeFactory();

public:
    eprosima::fastdds::dds::TopicDataType *createTopicDataType(std::string typeName);
    DataPacketCreateCB                     getDataPacketCB(std::string typeName);
    DataProcessCB                          getDataProcessCB(std::string typeName);

private:
    TopicDataTypeCreator *m_creator;
};

#endif