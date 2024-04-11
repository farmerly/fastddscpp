#include "CDDSHandler.h"
#include "CDDSDomainParticipant.h"
#include "CDDSTopicDataReader.hpp"
#include "CDDSTopicDataWriter.hpp"
#include "CParticipantQosHandler.h"
#include "DDSConstants.h"
#include "HelloWorldOnePubSubTypes.h"
#include "HelloWorldTwoPubSubTypes.h"
#include <chrono>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fastdds/dds/topic/qos/TopicQos.hpp>
#include <glog/logging.h>
#include <thread>

using namespace eprosima::fastdds::dds;
using namespace eprosima::fastdds::rtps;
using namespace eprosima::fastrtps::rtps;

void processHelloWorldOne(std::shared_ptr<HelloWorldOne> data)
{
    std::cout << "recv message: " << data->index() << std::endl;
}

void run_dds_data_writer()
{
    CParticipantQosHandler participantQosManager("test_writer");
    participantQosManager.addSHMTransport(153600);
    CDDSDomainParticipant participant(170, participantQosManager.getQos());

    eprosima::fastdds::dds::TopicQos    topicQos(TOPIC_QOS_DEFAULT);
    eprosima::fastdds::dds::TypeSupport typeSupport(new HelloWorldOnePubSubType());
    participant.registerTopic(DDS_TOPIC_HELLO_WORLD_ONE, topicQos, typeSupport);
    eprosima::fastdds::dds::DataWriterQos dataWriterQos(DATAWRITER_QOS_DEFAULT);
    CDDSTopicDataWriter<HelloWorldOne> *dataWriter = participant.createDataWriter<HelloWorldOne>(DDS_TOPIC_HELLO_WORLD_ONE, dataWriterQos);

    int index = 0;
    while (true) {
        HelloWorldOne message;
        message.index(++index);
        message.points(std::vector<uint8_t>(100));
        if (dataWriter->writeMessage(message)) {
            std::cout << "send message: " << message.index() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void run_dds_data_reader()
{
    CParticipantQosHandler participantQosManager("test_reader");
    participantQosManager.addSHMTransport(153600);
    CDDSDomainParticipant participant(170, participantQosManager.getQos());

    eprosima::fastdds::dds::TopicQos    topicQos(TOPIC_QOS_DEFAULT);
    eprosima::fastdds::dds::TypeSupport typeSupport(new HelloWorldOnePubSubType());
    participant.registerTopic(DDS_TOPIC_HELLO_WORLD_ONE, topicQos, typeSupport);
    eprosima::fastdds::dds::DataReaderQos dataReaderQos(DATAREADER_QOS_DEFAULT);
    CDDSTopicDataReader<HelloWorldOne>   *dataReader =
        participant.createDataReader<HelloWorldOne>(DDS_TOPIC_HELLO_WORLD_ONE, dataReaderQos, processHelloWorldOne);

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

// CDDSDataHandler::CDDSDataHandler()
// {
//     m_manager = new CDDSParticipantManager();
// }

// CDDSDataHandler::~CDDSDataHandler()
// {
//     if (m_manager) {
//         delete m_manager;
//     }
// }

// bool CDDSDataHandler::init(uint32_t domain_id, std::string participantName)
// {
//     CParticipantQosHandler manager(participantName);
//     manager.addUDPV4Transport();
//     // manager.addUDPV6Transport();
//     // manager.addSHMTransport(1024 * 1024 * 16);
//     DomainParticipantQos participantQos = manager.getDomainParticipantQos();

//     m_manager->initDomainParticipant(domain_id, participantQos);
//     m_manager->registerProxyFactory(this);

//     LOG(INFO) << "CDDSDataHandler[" << participantName << "] 初始化完成, domainId: " << domain_id;
//     return true;
// }

// bool CDDSDataHandler::registerDataWriter(std::string topicName)
// {
//     std::string typeName = getTypeNameByTopic(topicName);
//     if (typeName.size() > 0) {
//         return m_manager->registerDataWriter(topicName, typeName);
//     }
//     return false;
// }

// bool CDDSDataHandler::registerDataReader(std::string topicName, DataPacketProcessCB processCb, void *cbArgs)
// {
//     std::string typeName = getTypeNameByTopic(topicName);
//     if (typeName.size() > 0) {
//         return m_manager->registerDataReader(topicName, typeName, processCb, cbArgs);
//     }
//     return false;
// }

// bool CDDSDataHandler::sendData(std::string topicName, void *data)
// {
//     std::string typeName = getTypeNameByTopic(topicName);
//     if (typeName.size() > 0) {
//         return m_manager->sendData(topicName, typeName, data);
//     }
//     LOG(WARNING) << "未找到对应  TOPIC 的数据类型: " << topicName;
//     return false;
// }

// bool CDDSDataHandler::publishHelloWorldOne(HelloWorldOne *data)
// {
//     return sendData(DDS_TOPIC_HELLO_WORLD_ONE, data);
// }

// bool CDDSDataHandler::publishHelloWorldTwo(HelloWorldTwo *data)
// {
//     return sendData(DDS_TOPIC_HELLO_WORLD_TWO, data);
// }

// eprosima::fastdds::dds::TopicDataType *CDDSDataHandler::createTopicDataType(std::string typeName)
// {
//     if (!typeName.compare(DDS_TYPE_HELLO_WORLD_ONE)) {
//         return new HelloWorldOnePubSubType();
//     } else if (!typeName.compare(DDS_TYPE_HELLO_WORLD_TWO)) {
//         return new HelloWorldTwoPubSubType();
//     } else {
//         LOG(WARNING) << "Not found TopicDataType: " << typeName;
//     }
//     return nullptr;
// }

// DataPacketCreateCB CDDSDataHandler::getDataPacketCreateCB(std::string typeName)
// {
//     if (!typeName.compare(DDS_TYPE_HELLO_WORLD_ONE)) {
//         return createHelloWorldOneCB;
//     } else if (!typeName.compare(DDS_TYPE_HELLO_WORLD_TWO)) {
//         return createHelloWorldTwoCB;
//     } else {
//         LOG(WARNING) << "Not found DataPacketCB: " << typeName;
//     }
//     return nullptr;
// }

// std::string CDDSDataHandler::getTypeNameByTopic(std::string topicName)
// {
//     if (!topicName.compare(DDS_TOPIC_HELLO_WORLD_ONE)) {
//         return DDS_TYPE_HELLO_WORLD_ONE;
//     } else if (!topicName.compare(DDS_TOPIC_HELLO_WORLD_TWO)) {
//         return DDS_TYPE_HELLO_WORLD_TWO;
//     } else {
//         LOG(WARNING) << "Not found typename by topic: " << topicName;
//     }
//     return "";
// }

// IDDSDataPacket *CDDSDataHandler::createHelloWorldOneCB()
// {
//     return new CDDSDataPacket<HelloWorldOne>();
// }

// IDDSDataPacket *CDDSDataHandler::createHelloWorldTwoCB()
// {
//     return new CDDSDataPacket<HelloWorldTwo>();
// }
