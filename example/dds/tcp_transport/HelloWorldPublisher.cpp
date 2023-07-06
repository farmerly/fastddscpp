#include "HelloWorldPublisher.h"

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/rtps/transport/TCPv4TransportDescriptor.h>

using namespace eprosima::fastdds::dds;
using namespace eprosima::fastdds::rtps;
using namespace eprosima::fastrtps::rtps;

HelloWorldPublisher::HelloWorldPublisher() : m_type(new HelloWorldPubSubType())
{
    participant_ = nullptr;
    publisher_ = nullptr;
    writer_ = nullptr;
    topic_ = nullptr;
}

HelloWorldPublisher::~HelloWorldPublisher()
{
    if (writer_ != nullptr) {
        publisher_->delete_datawriter(writer_);
    }
    if (publisher_ != nullptr) {
        participant_->delete_publisher(publisher_);
    }
    if (topic_ != nullptr) {
        participant_->delete_topic(topic_);
    }
    DomainParticipantFactory::get_instance()->delete_participant(participant_);
}

bool HelloWorldPublisher::init(const unsigned short &port, bool useTLS)
{
    DomainParticipantQos participantQos;
    participantQos.wire_protocol().builtin.discovery_config.leaseDuration = eprosima::fastrtps::c_TimeInfinite;
    participantQos.wire_protocol().builtin.discovery_config.leaseDuration_announcementperiod = eprosima::fastrtps::Duration_t(0, 0);
    participantQos.name("Participant_publisher");

    participantQos.transport().use_builtin_transports = false;
    auto tcp_transport = std::make_shared<TCPv4TransportDescriptor>();

    if (useTLS) {
        using TLSOptions = TCPTransportDescriptor::TLSConfig::TLSOptions;
        tcp_transport->apply_security = true;
        tcp_transport->tls_config.password = "test";
        tcp_transport->tls_config.cert_chain_file = "tls/server.crt";
        tcp_transport->tls_config.private_key_file = "tls/server.key";
        tcp_transport->tls_config.tmp_dh_file = "tls/dh2048.pem";
        tcp_transport->tls_config.add_option(TLSOptions::DEFAULT_WORKAROUNDS);
        tcp_transport->tls_config.add_option(TLSOptions::SINGLE_DH_USE);
        tcp_transport->tls_config.add_option(TLSOptions::NO_SSLV2);
    }

    tcp_transport->sendBufferSize = 0;
    tcp_transport->receiveBufferSize = 0;
    tcp_transport->add_listener_port(port);
    participantQos.transport().user_transports.push_back(tcp_transport);

    DomainParticipantFactory *factory = DomainParticipantFactory::get_instance();
    participant_ = factory->create_participant(0, participantQos);
    if (participant_ == nullptr) {
        return false;
    }

    // Register the Type
    m_type.register_type(participant_);

    // Create the publications Topic
    topic_ = participant_->create_topic("HelloWorldTopic", "HelloWorld", TOPIC_QOS_DEFAULT);
    if (topic_ == nullptr) {
        return false;
    }

    // Create the Publisher
    publisher_ = participant_->create_publisher(PUBLISHER_QOS_DEFAULT, nullptr);
    if (publisher_ == nullptr) {
        return false;
    }

    // Create the DataWriter
    DataWriterQos dataWriterQos;
    dataWriterQos.history().kind = KEEP_LAST_HISTORY_QOS;
    dataWriterQos.history().depth = 1;
    dataWriterQos.reliability().kind = RELIABLE_RELIABILITY_QOS;
    writer_ = publisher_->create_datawriter(topic_, dataWriterQos, &listener_);
    if (writer_ == nullptr) {
        return false;
    }
    return true;
}

bool HelloWorldPublisher::publish(std::shared_ptr<HelloWorld> hello)
{
    return writer_->write(hello.get());
}

void HelloWorldPublisher::run()
{
    int index = 0;
    while (true) {
        auto hello = std::make_shared<HelloWorld>();
        hello->index(++index);
        hello->message("HelloWorld");

        if (publish(hello)) {
            std::cout << "Message: " << hello->message() << " with index: " << hello->index() << " SENT" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
