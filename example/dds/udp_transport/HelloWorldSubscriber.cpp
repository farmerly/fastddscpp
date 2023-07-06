#include "HelloWorldSubscriber.h"

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/rtps/transport/UDPv4TransportDescriptor.h>

using namespace eprosima::fastdds::dds;
using namespace eprosima::fastdds::rtps;
using namespace eprosima::fastrtps::rtps;

HelloWorldSubscriber::HelloWorldSubscriber() : m_type(new HelloWorldPubSubType())
{
    participant_ = nullptr;
    subscriber_ = nullptr;
    reader_ = nullptr;
    topic_ = nullptr;
}

HelloWorldSubscriber::~HelloWorldSubscriber()
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
    eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->delete_participant(participant_);
}

bool HelloWorldSubscriber::init()
{
    DomainParticipantQos participantQos;
    participantQos.wire_protocol().builtin.discovery_config.discoveryProtocol = DiscoveryProtocol_t::SIMPLE;
    participantQos.wire_protocol().builtin.discovery_config.use_SIMPLE_EndpointDiscoveryProtocol = true;
    participantQos.wire_protocol().builtin.discovery_config.initial_announcements.count = 5;
    participantQos.wire_protocol().builtin.discovery_config.initial_announcements.period = eprosima::fastrtps::Duration_t(1, 0);
    participantQos.wire_protocol().builtin.discovery_config.m_simpleEDP.use_PublicationReaderANDSubscriptionWriter = true;
    participantQos.wire_protocol().builtin.discovery_config.m_simpleEDP.use_PublicationWriterANDSubscriptionReader = true;
    participantQos.wire_protocol().builtin.discovery_config.leaseDuration = eprosima::fastrtps::c_TimeInfinite;
    participantQos.name("Participant_subscriber");

    // 配置 initial peers
    Locator_t locator;
    IPLocator::setIPv4(locator, "10.100.1.72");
    // 7400 + 250 * domainID + 10 + 2 * participantID
    // locator.port = 7412;
    participantQos.wire_protocol().builtin.initialPeersList.push_back(locator);

    participantQos.transport().use_builtin_transports = false;
    auto udp_transport = std::make_shared<UDPv4TransportDescriptor>();
    udp_transport->non_blocking_send = true;
    participantQos.transport().user_transports.push_back(udp_transport);

    participant_ = DomainParticipantFactory::get_instance()->create_participant(0, participantQos);
    if (participant_ == nullptr) {
        return false;
    }

    m_type.register_type(participant_);
    TopicQos topicQos;
    topic_ = participant_->create_topic("HelloWorldTopic", "HelloWorld", topicQos);
    if (topic_ == nullptr) {
        return false;
    }

    subscriber_ = participant_->create_subscriber(SUBSCRIBER_QOS_DEFAULT, nullptr);
    if (subscriber_ == nullptr) {
        return false;
    }

    DataReaderQos readerQos;
    readerQos.reliability().kind = RELIABLE_RELIABILITY_QOS;
    reader_ = subscriber_->create_datareader(topic_, readerQos, &listener_);
    if (reader_ == nullptr) {
        return false;
    }
    return true;
}

void HelloWorldSubscriber::run()
{
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}