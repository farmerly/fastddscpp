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
    bool createDataWriter(std::string topicName, std::string typeName);
    bool createDataReader(std::string topicName, std::string typeName, processCb, void *cbArgs);

public:
    bool sendData(std::string topicName, std::string typeName, void *data);

private:
    CDDSDomainParticipant *m_domainParticipant;
};

#endif
