#ifndef TOPIC_DATA_TYPE_FACTORY_H_H_H
#define TOPIC_DATA_TYPE_FACTORY_H_H_H

#include "ITopicDataTypeCreator.h"

class TopicDataTypeFactory
{
public:
    TopicDataTypeFactory(ITopicDataTypeCreator *creator);
    ~TopicDataTypeFactory();

public:
    eprosima::fastdds::dds::TopicDataType *createTopicDataType(std::string typeName);
    DataPacketCreateCB                     getDataPacketCB(std::string typeName);
    DataProcessCB                          getDataProcessCB(std::string typeName);

private:
    ITopicDataTypeCreator *m_creator;
};

#endif