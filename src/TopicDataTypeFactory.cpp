#include "TopicDataTypeFactory.h"

using namespace eprosima::fastdds::dds;

TopicDataTypeFactory::TopicDataTypeFactory(ITopicDataTypeCreator *creator)
{
    m_creator = creator;
}

TopicDataTypeFactory::~TopicDataTypeFactory()
{
}

TopicDataType *TopicDataTypeFactory::createTopicDataType(std::string typeName)
{
    return m_creator->createTopicDataType(typeName);
}

DataPacketCreateCB TopicDataTypeFactory::getDataPacketCB(std::string typeName)
{
    return m_creator->getDataPacketCB(typeName);
}

DataProcessCB TopicDataTypeFactory::getDataProcessCB(std::string typeName)
{
    return m_creator->getDataProcessCB(typeName);
}