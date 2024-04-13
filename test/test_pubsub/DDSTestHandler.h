#pragma once

#include "DDSParticipantManager.h"
#include <functional>
#include <unordered_map>

class DDSTestHandler : public DDSParticipantManager
{
public:
    DDSTestHandler(int domainId, std::string participantName);
    ~DDSTestHandler();

protected:
    ParticipantQosHandler createParticipantQos() override;

private:
    std::string m_participantName;
};