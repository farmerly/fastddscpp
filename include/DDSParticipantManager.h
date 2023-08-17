#ifndef DDS_TOPIC_DATA_WRITER_H_H_H
#define DDS_TOPIC_DATA_WRITER_H_H_H

#include "CDDSTopicDataReader.h"
#include "CDDSTopicDataWriter.h"
#include "DDSDomainParticipant.h"
#include "ITopicDataTypeWorker.h"
#include <map>
#include <string>

class DDSParticipantManager
{
public:
    DDSParticipantManager();
    ~DDSParticipantManager();

public:
    void initDomainParticipant(int domainId, const eprosima::fastdds::dds::DomainParticipantQos &participantQos);
    void registerProxyWorker(ITopicDataTypeWorker *worker);
    bool registerPublisher(std::string topicName, std::string typeName);
    bool registerSubscriber(std::string topicName, std::string typeName);

public:
    bool sendData(std::string topicName, std::string typeName, void *data);

private:
    DDSDomainParticipant                                               *m_domainParticipant;
    TopicDataTypeFactory                                               *m_proxyFactory;
    std::map<std::string, std::map<std::string, CDDSTopicDataWriter *>> m_mapWriter;
    std::map<std::string, std::map<std::string, CDDSTopicDataReader *>> m_mapReader;
};

#endif
