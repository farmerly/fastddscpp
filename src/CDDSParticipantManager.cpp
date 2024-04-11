#include "CDDSParticipantManager.h"
#include "CDDSTopicDataReader.hpp"
#include <fastdds/dds/topic/TypeSupport.hpp>
#include <glog/logging.h>

using namespace eprosima::fastdds::dds;

// CDDSParticipantManager::CDDSParticipantManager()
// {
//     m_proxyFactory = nullptr;
// }

// CDDSParticipantManager::~CDDSParticipantManager()
// {
//     if (m_proxyFactory) {
//         delete m_proxyFactory;
//         m_proxyFactory = nullptr;
//     }
// }

// void CDDSParticipantManager::initDomainParticipant(int domainId, const eprosima::fastdds::dds::DomainParticipantQos &participantQos)
// {
//     m_domainParticipant = new CDDSDomainParticipant(domainId, participantQos);
// }

// void CDDSParticipantManager::registerProxyFactory(ITopicDataTypeCreator *creator)
// {
//     m_proxyFactory = new CTopicDataTypeFactory(creator);
// }

// bool CDDSParticipantManager::registerDataWriter(std::string topicName, std::string typeName)
// {
//     TypeSupport          typeSupport(m_proxyFactory->createTopicDataType(typeName));
//     CDDSTopicDataWriter *topicWriter = new CDDSTopicDataWriter();
//     topicWriter->initDataWriter(topicName, typeName, m_domainParticipant, typeSupport);
//     if (m_mapWriter.find(topicName) == m_mapWriter.end()) {
//         m_mapWriter[topicName] = std::map<std::string, CDDSTopicDataWriter *>();
//     }
//     m_mapWriter[topicName].insert(std::pair<std::string, CDDSTopicDataWriter *>(typeName, topicWriter));
//     return true;
// }

// bool CDDSParticipantManager::registerDataReader(std::string topicName, std::string typeName, DataPacketProcessCB processCb, void *cbArgs)
// {
//     TopicDataType *dataType = m_proxyFactory->createTopicDataType(typeName);
//     if (dataType == nullptr) {
//         LOG(ERROR) << "获取 " << typeName << " 对应数据类型失败";
//         return false;
//     }
//     TypeSupport        typeSupport(dataType);
//     DataPacketCreateCB createCallback = m_proxyFactory->getDataPacketCreateCB(typeName);
//     if (createCallback == nullptr) {
//         LOG(ERROR) << "获取 " << typeName << " 对应构造方法失败";
//         return false;
//     }
//     CDDSTopicDataReader *topicReader = new CDDSTopicDataReader();
//     if (!topicReader->initDataReader(topicName, typeName, m_domainParticipant, typeSupport, createCallback, processCb, cbArgs)) {
//         LOG(ERROR) << "初始化 " << topicName << " DataReader 失败";
//         return false;
//     }
//     if (m_mapReader.find(topicName) == m_mapReader.end()) {
//         m_mapReader[topicName] = std::map<std::string, CDDSTopicDataReader *>();
//     }
//     m_mapReader[topicName].insert(std::pair<std::string, CDDSTopicDataReader *>(typeName, topicReader));
//     return true;
// }

// bool CDDSParticipantManager::sendData(std::string topicName, std::string typeName, void *data)
// {
//     if (m_mapWriter.find(topicName) == m_mapWriter.end()) {
//         LOG(WARNING) << "未找到当前订阅的TOPIC: " << topicName;
//         return false;
//     }

//     std::map<std::string, CDDSTopicDataWriter *> &mapWriter = m_mapWriter[topicName];
//     if (mapWriter.find(typeName) != mapWriter.end()) {
//         return mapWriter[typeName]->sendData(data);
//     }
//     LOG(WARNING) << "未找到当前订阅的数据类型: " << typeName;
//     return false;
// }