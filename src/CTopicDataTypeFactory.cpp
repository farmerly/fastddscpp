#include "CTopicDataTypeFactory.h"

using namespace eprosima::fastdds::dds;

CTopicDataTypeFactory::CTopicDataTypeFactory(ITopicDataTypeCreator *creator)
{
    m_creator = creator;
}

CTopicDataTypeFactory::~CTopicDataTypeFactory()
{
}

TopicDataType *CTopicDataTypeFactory::createTopicDataType(std::string typeName)
{
    return m_creator->createTopicDataType(typeName);
}

DataPacketCreateCB CTopicDataTypeFactory::getDataPacketCreateCB(std::string typeName)
{
    return m_creator->getDataPacketCreateCB(typeName);
}
