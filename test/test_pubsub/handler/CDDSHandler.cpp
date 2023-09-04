#include "CDDSHandler.h"
#include "CDataPacket.h"
#include "CParticipantQosHandler.h"
#include "CPcSrcDataPubSubTypes.h"
#include "DDSConstants.h"
#include "HelloWorldOnePubSubTypes.h"
#include "HelloWorldTwoPubSubTypes.h"
#include <glog/logging.h>

using namespace eprosima::fastdds::dds;
using namespace eprosima::fastdds::rtps;
using namespace eprosima::fastrtps::rtps;

CDDSDataHandler::CDDSDataHandler()
{
    m_manager = new CDDSParticipantManager();
}

CDDSDataHandler::~CDDSDataHandler()
{
    if (m_manager) {
        delete m_manager;
    }
}

bool CDDSDataHandler::init(uint32_t domain_id, std::string participantName)
{
    CParticipantQosHandler manager(participantName);
    manager.addUDPV4Transport();
    // manager.addUDPV6Transport();
    // manager.addSHMTransport(1024 * 1024 * 16);
    DomainParticipantQos participantQos = manager.getDomainParticipantQos();

    m_manager->initDomainParticipant(domain_id, participantQos);
    m_manager->registerProxyFactory(this);

    LOG(INFO) << "CDDSDataHandler[" << participantName << "] 初始化完成, domainId: " << domain_id;
    return true;
}

bool CDDSDataHandler::registerDataWriter(std::string topicName)
{
    std::string typeName = getTypeNameByTopic(topicName);
    if (typeName.size() > 0) {
        return m_manager->registerDataWriter(topicName, typeName);
    }
    return false;
}

bool CDDSDataHandler::registerDataReader(std::string topicName, DataPacketProcessCB processCb, void *cbArgs)
{
    std::string typeName = getTypeNameByTopic(topicName);
    if (typeName.size() > 0) {
        return m_manager->registerDataReader(topicName, typeName, processCb, cbArgs);
    }
    return false;
}

bool CDDSDataHandler::sendData(std::string topicName, void *data)
{
    std::string typeName = getTypeNameByTopic(topicName);
    if (typeName.size() > 0) {
        return m_manager->sendData(topicName, typeName, data);
    }
    LOG(WARNING) << "未找到对应  TOPIC 的数据类型: " << topicName;
    return false;
}

bool CDDSDataHandler::publishHelloWorldOne(HelloWorldOne *data)
{
    return sendData(DDS_TOPIC_HELLO_WORLD_ONE, data);
}

bool CDDSDataHandler::publishHelloWorldTwo(HelloWorldTwo *data)
{
    return sendData(DDS_TOPIC_HELLO_WORLD_TWO, data);
}

bool CDDSDataHandler::publishCPcSrcTimeMatch(CPcSrcDataTimeMatch *data)
{
    return sendData(DDS_TOPIC_CPCSRC_TIMEMATCH, data);
}

eprosima::fastdds::dds::TopicDataType *CDDSDataHandler::createTopicDataType(std::string typeName)
{
    if (!typeName.compare(DDS_TYPE_HELLO_WORLD_ONE)) {
        return new HelloWorldOnePubSubType();
    } else if (!typeName.compare(DDS_TYPE_HELLO_WORLD_TWO)) {
        return new HelloWorldTwoPubSubType();
    } else if (!typeName.compare(DDS_TYPE_CPCSRC_TIMEMATCH)) {
        return new CPcSrcDataTimeMatchPubSubType();
    } else {
        LOG(WARNING) << "Not found TopicDataType: " << typeName;
    }
    return nullptr;
}

DataPacketCreateCB CDDSDataHandler::getDataPacketCreateCB(std::string typeName)
{
    if (!typeName.compare(DDS_TYPE_HELLO_WORLD_ONE)) {
        return createHelloWorldOneCB;
    } else if (!typeName.compare(DDS_TYPE_HELLO_WORLD_TWO)) {
        return createHelloWorldTwoCB;
    } else if (!typeName.compare(DDS_TYPE_CPCSRC_TIMEMATCH)) {
        return createCPcSrcTimeMatchCB;
    } else {
        LOG(WARNING) << "Not found DataPacketCB: " << typeName;
    }
    return nullptr;
}

std::string CDDSDataHandler::getTypeNameByTopic(std::string topicName)
{
    if (!topicName.compare(DDS_TOPIC_HELLO_WORLD_ONE)) {
        return DDS_TYPE_HELLO_WORLD_ONE;
    } else if (!topicName.compare(DDS_TOPIC_HELLO_WORLD_TWO)) {
        return DDS_TYPE_HELLO_WORLD_TWO;
    } else if (!topicName.compare(DDS_TOPIC_CPCSRC_TIMEMATCH)) {
        return DDS_TYPE_CPCSRC_TIMEMATCH;
    } else {
        LOG(WARNING) << "Not found typename by topic: " << topicName;
    }
    return "";
}

IDataPacket *CDDSDataHandler::createHelloWorldOneCB()
{
    return new CDataPacket<HelloWorldOne>();
}

IDataPacket *CDDSDataHandler::createHelloWorldTwoCB()
{
    return new CDataPacket<HelloWorldTwo>();
}

IDataPacket *CDDSDataHandler::createCPcSrcTimeMatchCB()
{
    return new CDataPacket<HelloWorldTwo>();
}
