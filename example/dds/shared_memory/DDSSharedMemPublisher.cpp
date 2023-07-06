#include "DDSSharedMemPublisher.h"

#include "HelloWorldPubSubTypes.h"
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>
#include <fastdds/rtps/transport/shared_mem/SharedMemTransportDescriptor.h>

using namespace eprosima::fastdds::dds;
using namespace eprosima::fastdds::rtps;
using namespace eprosima::fastrtps::rtps;

DDSSharedMemPublisher::DDSSharedMemPublisher()
{
    participant_ = nullptr;
    publisher_ = nullptr;

    topic_ = nullptr;
    writer_ = nullptr;
}

DDSSharedMemPublisher::~DDSSharedMemPublisher()
{
    if (writer_ != nullptr) {
        publisher_->delete_datawriter(writer_);
    }
    if (topic_ != nullptr) {
        participant_->delete_topic(topic_);
    }
    if (publisher_ != nullptr) {
        participant_->delete_publisher(publisher_);
    }
    DomainParticipantFactory::get_instance()->delete_participant(participant_);
}

bool DDSSharedMemPublisher::init(const std::string &participantName, const int &segmentSize)
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

    auto shm_transport = std::make_shared<SharedMemTransportDescriptor>();
    shm_transport->segment_size(segmentSize);
    participantQos.transport().user_transports.push_back(shm_transport);

    participant_ = DomainParticipantFactory::get_instance()->create_participant(0, participantQos);

    if (participant_ == nullptr) {
        return false;
    }

    // REGISTER THE TYPE
    TypeSupport type(new HelloWorldPubSubType());
    type.register_type(participant_);

    // CREATE THE PUBLISHER
    publisher_ = participant_->create_publisher(PUBLISHER_QOS_DEFAULT);

    if (publisher_ == nullptr) {
        return false;
    }

    return true;
}

bool DDSSharedMemPublisher::initPub()
{
    // CREATE THE TOPIC
    topic_ = participant_->create_topic("HelloWorldSharedMemTopic", "HelloWorld", TOPIC_QOS_DEFAULT);
    if (topic_ == nullptr) {
        return false;
    }

    // CREATE THE DATAWRITER
    DataWriterQos writerQos;
    writerQos.history().kind = KEEP_LAST_HISTORY_QOS;
    writerQos.history().depth = 30;
    writerQos.resource_limits().max_samples = 50;
    writerQos.resource_limits().allocated_samples = 20;
    writerQos.reliable_writer_qos().times.heartbeatPeriod.seconds = 2;
    writerQos.reliable_writer_qos().times.heartbeatPeriod.nanosec = 200 * 1000 * 1000;
    writerQos.reliability().kind = RELIABLE_RELIABILITY_QOS;
    writerQos.publish_mode().kind = ASYNCHRONOUS_PUBLISH_MODE;

    writer_ = publisher_->create_datawriter(topic_, writerQos, &listener_);
    if (writer_ == nullptr) {
        return false;
    }

    return true;
}

bool DDSSharedMemPublisher::publish(void *data, bool waitForListener)
{
    if (!waitForListener) {
        return writer_->write(data);
    }
    return false;
}
