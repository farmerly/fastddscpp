#ifndef DDS_TOPIC_DATA_WRITER_H_H_H
#define DDS_TOPIC_DATA_WRITER_H_H_H

#include "CDDSDomainParticipant.h"
#include "CDDSTopicDataReader.h"
#include "CDDSTopicDataWriter.h"
#include "CTopicDataTypeFactory.h"
#include "ITopicDataTypeCreator.h"
#include <map>
#include <string>

class CDDSParticipantManager
{
public:
    CDDSParticipantManager();
    ~CDDSParticipantManager();

public:
    void initDomainParticipant(int domainId, const eprosima::fastdds::dds::DomainParticipantQos &participantQos);
    void registerProxyFactory(ITopicDataTypeCreator *creator);
    bool registerDataWriter(std::string topicName, std::string typeName);
    bool registerDataReader(std::string topicName, std::string typeName, DataPacketProcessCB processCb, void *cbArgs);

public:
    bool sendData(std::string topicName, std::string typeName, void *data);

private:
    CDDSDomainParticipant                                              *m_domainParticipant;
    CTopicDataTypeFactory                                              *m_proxyFactory;
    std::map<std::string, std::map<std::string, CDDSTopicDataWriter *>> m_mapWriter;
    std::map<std::string, std::map<std::string, CDDSTopicDataReader *>> m_mapReader;
};

#endif
