#ifndef TOPIC_DATA_TYPE_FACTORY_H_H_H
#define TOPIC_DATA_TYPE_FACTORY_H_H_H

#include "ITopicDataTypeCreator.h"

class CTopicDataTypeFactory : public ITopicDataTypeCreator
{
public:
    CTopicDataTypeFactory(ITopicDataTypeCreator *creator);
    ~CTopicDataTypeFactory();

public:
    eprosima::fastdds::dds::TopicDataType *createTopicDataType(std::string typeName) override;
    DataPacketCreateCB                     getDataPacketCreateCB(std::string typeName) override;

private:
    ITopicDataTypeCreator *m_creator;
};

#endif