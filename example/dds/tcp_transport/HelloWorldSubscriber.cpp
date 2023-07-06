#include "HelloWorldSubscriber.h"

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/rtps/transport/TCPv4TransportDescriptor.h>

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
    DomainParticipantFactory::get_instance()->delete_participant(participant_);
}

bool HelloWorldSubscriber::init(const std::string &participantName, const unsigned short &port, bool useTLS)
{
    DomainParticipantQos participantQos;
    participantQos.wire_protocol().builtin.discovery_config.discoveryProtocol = DiscoveryProtocol_t::SIMPLE;
    participantQos.wire_protocol().builtin.discovery_config.use_SIMPLE_EndpointDiscoveryProtocol = true;
    participantQos.wire_protocol().builtin.discovery_config.m_simpleEDP.use_PublicationReaderANDSubscriptionWriter = true;
    participantQos.wire_protocol().builtin.discovery_config.m_simpleEDP.use_PublicationWriterANDSubscriptionReader = true;
    participantQos.name(participantName.c_str());

    participantQos.transport().use_builtin_transports = false;
    auto tcp_transport = std::make_shared<TCPv4TransportDescriptor>();
    if (useTLS) {
        using TLSVerifyMode = TCPTransportDescriptor::TLSConfig::TLSVerifyMode;
        using TLSOptions = TCPTransportDescriptor::TLSConfig::TLSOptions;
        tcp_transport->apply_security = true;
        tcp_transport->tls_config.password = "test";
        tcp_transport->tls_config.verify_file = "tls/ca.crt";
        tcp_transport->tls_config.verify_mode = TLSVerifyMode::VERIFY_PEER;
        tcp_transport->tls_config.add_option(TLSOptions::DEFAULT_WORKAROUNDS);
    }

    Locator_t initial_peer_locator;
    initial_peer_locator.kind = LOCATOR_KIND_TCPv4;
    IPLocator::setIPv4(initial_peer_locator, "127.0.0.1");
    initial_peer_locator.port = port;

    participantQos.wire_protocol().builtin.initialPeersList.push_back(initial_peer_locator);
    std::cout << "size: " << participantQos.wire_protocol().builtin.initialPeersList.size() << std::endl;
    participantQos.transport().user_transports.push_back(tcp_transport);

    DomainParticipantFactory *factory = DomainParticipantFactory::get_instance();
    participant_ = factory->create_participant(0, participantQos);
    if (participant_ == nullptr) {
        return false;
    }

    m_type.register_type(participant_);
    topic_ = participant_->create_topic("HelloWorldTopic", "HelloWorld", TOPIC_QOS_DEFAULT);
    if (topic_ == nullptr) {
        return false;
    }

    SubscriberQos subscriberQos;
    subscriber_ = participant_->create_subscriber(subscriberQos, nullptr);
    if (subscriber_ == nullptr) {
        return false;
    }

    DataReaderQos dataReaderQos;
    dataReaderQos.history().kind = KEEP_LAST_HISTORY_QOS;
    dataReaderQos.history().depth = 1;
    dataReaderQos.reliability().kind = RELIABLE_RELIABILITY_QOS;
    reader_ = subscriber_->create_datareader(topic_, dataReaderQos, &listener_);
    if (reader_ == nullptr) {
        return false;
    }
    return true;
}

void HelloWorldSubscriber::run()
{
    std::cout << "thread run: " << std::this_thread::get_id() << std::endl;
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
