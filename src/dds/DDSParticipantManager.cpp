#include "DDSParticipantManager.h"
#include "DDSTopicDataReader.h"
#include <fastdds/dds/topic/TypeSupport.hpp>

using namespace eprosima::fastdds::dds;
using namespace std;

DDSParticipantManager::DDSParticipantManager()
{
    m_proxyFactory = nullptr;
}

DDSParticipantManager::~DDSParticipantManager()
{
    if (m_proxyFactory) {
        delete m_proxyFactory;
        m_proxyFactory = nullptr;
    }
}

void DDSParticipantManager::initDomainParticipant(int domainId, const eprosima::fastdds::dds::DomainParticipantQos &participantQos)
{
    m_domainParticipant = new DDSDomainParticipant(domainId, participantQos);
}

void DDSParticipantManager::registerProxyWorker(TopicDataTypeWorker *worker)
{
    m_proxyFactory = worker->createProxyFactory();
}

bool DDSParticipantManager::registerPublisher(std::string topicName, std::string typeName)
{
    TypeSupport         typeSupport(m_proxyFactory->createTopicDataType(typeName));
    DDSTopicDataWriter *topicWriter = new DDSTopicDataWriter();
    topicWriter->initDataWriter(topicName, typeName, m_domainParticipant, typeSupport);
    if (m_mapWriter.find(topicName) == m_mapWriter.end()) {
        m_mapWriter[topicName] = map<string, DDSTopicDataWriter *>();
    }
    m_mapWriter[topicName].insert(pair<string, DDSTopicDataWriter *>(typeName, topicWriter));
    return true;
}

bool DDSParticipantManager::registerSubscriber(std::string topicName, std::string typeName)
{
    TypeSupport         typeSupport(m_proxyFactory->createTopicDataType(typeName));
    DataPacketCreateCB  createCallback = m_proxyFactory->getDataPacketCB(typeName);
    DataProcessCB       processCallback = m_proxyFactory->getDataProcessCB(typeName);
    DDSTopicDataReader *topicReader = new DDSTopicDataReader();
    topicReader->initDataReader(topicName, typeName, m_domainParticipant, typeSupport, createCallback, processCallback);
    if (m_mapReader.find(topicName) == m_mapReader.end()) {
        m_mapReader[topicName] = map<string, DDSTopicDataReader *>();
    }
    m_mapReader[topicName].insert(pair<string, DDSTopicDataReader *>(typeName, topicReader));
    return true;
}

bool DDSParticipantManager::sendData(std::string topicName, std::string typeName, void *data)
{
    if (m_mapWriter.find(topicName) != m_mapWriter.end()) {
        map<string, DDSTopicDataWriter *> &mapWriter = m_mapWriter[topicName];
        if (mapWriter.find(typeName) != mapWriter.end()) {
            return mapWriter[typeName]->sendData(data);
        }
    }
    return false;
}