#ifndef DDS_TOPIC_DATA_WRITER_H_H_H
#define DDS_TOPIC_DATA_WRITER_H_H_H

#include "CDDSDomainParticipant.h"
#include "CDDSTopicDataReader.h"
#include "CDDSTopicDataWriter.h"
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
    bool registerDataWriter(std::string topicName, std::string typeName);
    bool registerDataReader(std::string topicName, std::string typeName);

public:
    bool sendData(std::string topicName, std::string typeName, void *data);

private:
    CDDSDomainParticipant                                              *m_domainParticipant;
    CTopicDataTypeFactory                                              *m_proxyFactory;
    std::map<std::string, std::map<std::string, CDDSTopicDataWriter *>> m_mapWriter;
    std::map<std::string, std::map<std::string, CDDSTopicDataReader *>> m_mapReader;
};

#endif
