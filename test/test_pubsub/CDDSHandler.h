#pragma once

#include "CDDSParticipantManager.h"
#include "HelloWorldOne.h"
#include "HelloWorldTwo.h"
#include "IDDSParticipantHandler.h"

class CDDSDataHandler : public IDDSParticipantHandler
{
public:
    CDDSDataHandler();
    virtual ~CDDSDataHandler();

public:
    bool init(uint32_t domain_id, std::string participantName) override;
    bool sendData(std::string topicName, void *data) override;
    bool registerDataWriter(std::string topicName) override;
    bool registerDataReader(std::string topicName, DataPacketProcessCB processCb, void *cbArgs) override;

public:
    bool publishHelloWorldOne(HelloWorldOne *data);
    bool publishHelloWorldTwo(HelloWorldTwo *data);

protected:
    eprosima::fastdds::dds::TopicDataType *createTopicDataType(std::string typeName) override;
    DataPacketCreateCB                     getDataPacketCreateCB(std::string typeName) override;

private:
    std::string            getTypeNameByTopic(std::string topicName);
    static IDDSDataPacket *createHelloWorldOneCB();
    static IDDSDataPacket *createHelloWorldTwoCB();

private:
    CDDSParticipantManager *m_manager;
};
