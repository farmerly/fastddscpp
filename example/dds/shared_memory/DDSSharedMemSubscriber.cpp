#include "DDSSharedMemSubscriber.h"

#include "HelloWorldPubSubTypes.h"
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fastdds/rtps/transport/shared_mem/SharedMemTransportDescriptor.h>

using namespace eprosima::fastdds::dds;
using namespace eprosima::fastdds::rtps;
using namespace eprosima::fastrtps::rtps;

DDSSharedMemSubscriber::DDSSharedMemSubscriber()
{
    participant_ = nullptr;
    subscriber_ = nullptr;

    reader_ = nullptr;
    topic_ = nullptr;
}

DDSSharedMemSubscriber::~DDSSharedMemSubscriber()
{
    if (reader_ != nullptr) {
        subscriber_->delete_datareader(reader_);
    }
    if (topic_ != nullptr) {
        participant_->delete_topic(topic_);
    }
    if (subscriber_ != nullptr) {
        participant_->delete_subscriber(subscriber_);
    }
    DomainParticipantFactory::get_instance()->delete_participant(participant_);
}

bool DDSSharedMemSubscriber::init(const std::string &participantName, const int &segmentSize)
{
    // CREATE THE PARTICIPANT
    DomainParticipantQos participantQos;
    participantQos.wire_protocol().builtin.discovery_config.discoveryProtocol = DiscoveryProtocol_t::SIMPLE;
    participantQos.wire_protocol().builtin.discovery_config.use_SIMPLE_EndpointDiscoveryProtocol = true;
    participantQos.wire_protocol().builtin.discovery_config.m_simpleEDP.use_PublicationReaderANDSubscriptionWriter = true;
    participantQos.wire_protocol().builtin.discovery_config.m_simpleEDP.use_PublicationWriterANDSubscriptionReader = true;
    participantQos.wire_protocol().builtin.discovery_config.leaseDuration = eprosima::fastrtps::c_TimeInfinite;
    participantQos.name(participantName.c_str());

    // SharedMem transport configuration
    participantQos.transport().use_builtin_transports = false;
    auto sm_transport = std::make_shared<SharedMemTransportDescriptor>();
    sm_transport->segment_size(2 * 1024 * 1024);
    participantQos.transport().user_transports.push_back(sm_transport);

    participant_ = DomainParticipantFactory::get_instance()->create_participant(0, participantQos);

    if (participant_ == nullptr) {
        return false;
    }

    // REGISTER THE TYPE
    TypeSupport type(new HelloWorldPubSubType());
    type.register_type(participant_);

    // CREATE THE SUBSCRIBER
    subscriber_ = participant_->create_subscriber(SUBSCRIBER_QOS_DEFAULT);
    if (subscriber_ == nullptr) {
        return false;
    }
    return true;
}

bool DDSSharedMemSubscriber::initSub()
{
    // CREATE THE TOPIC
    topic_ = participant_->create_topic("HelloWorldSharedMemTopic", "HelloWorld", TOPIC_QOS_DEFAULT);

    if (topic_ == nullptr) {
        return false;
    }

    // CREATE THE DATAREADER
    DataReaderQos readerQos;
    readerQos.history().kind = KEEP_LAST_HISTORY_QOS;
    readerQos.history().depth = 30;
    readerQos.resource_limits().max_samples = 50;
    readerQos.resource_limits().allocated_samples = 20;
    readerQos.reliability().kind = RELIABLE_RELIABILITY_QOS;
    readerQos.durability().kind = TRANSIENT_LOCAL_DURABILITY_QOS;

    reader_ = subscriber_->create_datareader(topic_, readerQos, &listener_);
    if (reader_ == nullptr) {
        return false;
    }
    return true;
}