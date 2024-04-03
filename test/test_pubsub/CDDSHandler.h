#pragma once

#include "CDDSParticipantManager.h"
#include "HelloWorldOne.h"
#include "HelloWorldTwo.h"
#include "IDDSParticipantHandler.h"

class CDDSDataHandler
{
public:
    CDDSDataHandler();
    virtual ~CDDSDataHandler();

public:
    bool init(uint32_t domain_id, std::string participantName);
    bool sendData(std::string topicName, void *data);
    bool registerDataWriter(std::string topicName);
    bool registerDataReader(std::string topicName, DataPacketProcessCB processCb, void *cbArgs) override;

public:
    bool publishHelloWorldOne(HelloWorldOne *data);
    bool publishHelloWorldTwo(HelloWorldTwo *data);

private:
    std::string getTypeNameByTopic(std::string topicName);

private:
    CDDSParticipantManager *m_manager;
};
