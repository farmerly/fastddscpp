#ifndef _DDS_MULTI_MANAGER_H_H_H
#define _DDS_MULTI_MANAGER_H_H_H

#include <fastdds/dds/domain/qos/DomainParticipantQos.hpp>

class CParticipantQosHandler
{
public:
    CParticipantQosHandler(std::string participant_name);
    ~CParticipantQosHandler();

public:
    eprosima::fastdds::dds::DomainParticipantQos &getDomainParticipantQos();

public:
    void addSHMTransport(uint32_t segment_size);
    void addTCPV4Transport(uint16_t listen_port, const std::vector<std::string> &peer_locators);
    void addTCPV6Transport();
    void addUDPV4Transport(const std::vector<std::string> &ipaddrs = {});
    void addUDPV6Transport();

private:
    eprosima::fastdds::dds::DomainParticipantQos m_participantQos;
};

#endif