#pragma once

#include "ITopicDataTypeCreator.h"

class IDDSParticipantHandler : public ITopicDataTypeCreator
{
public:
    IDDSParticipantHandler() = default;
    virtual ~IDDSParticipantHandler() = default;

public:
    virtual bool init(uint32_t domain_id, std::string participantName) = 0;
    virtual bool sendData(std::string topicName, void *data) = 0;
    // 注册 fastdds 的 dataWriter
    virtual bool registerDataWriter(std::string topicName) = 0;
    // 注册 fastdds 的 dataReader
    virtual bool registerDataReader(std::string topicName, DataPacketProcessCB processCb, void *cbArgs) = 0;
};