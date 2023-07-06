#include "HelloWorldPublisher.h"

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/rtps/transport/UDPv4TransportDescriptor.h>

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

bool HelloWorldPublisher::init()
{
    DomainParticipantQos participantQos;
    participantQos.wire_protocol().builtin.discovery_config.discoveryProtocol = DiscoveryProtocol_t::SIMPLE;
    participantQos.wire_protocol().builtin.discovery_config.use_SIMPLE_EndpointDiscoveryProtocol = true;
    participantQos.wire_protocol().builtin.discovery_config.initial_announcements.count = 5;
    participantQos.wire_protocol().builtin.discovery_config.initial_announcements.period = eprosima::fastrtps::Duration_t(1, 0);
    participantQos.wire_protocol().builtin.discovery_config.m_simpleEDP.use_PublicationReaderANDSubscriptionWriter = true;
    participantQos.wire_protocol().builtin.discovery_config.m_simpleEDP.use_PublicationWriterANDSubscriptionReader = true;
    // RTPSParticipant 发现其他 RTPSParticipant 之后多久开始推送消息
    participantQos.wire_protocol().builtin.discovery_config.leaseDuration_announcementperiod = eprosima::fastrtps::Duration_t(3, 0);
    // 提示远端认为此 RTPSParticipant 应该存活的时间
    participantQos.wire_protocol().builtin.discovery_config.leaseDuration = eprosima::fastrtps::c_TimeInfinite;

    participantQos.name("Participant_publisher");

    // 配置 initial peers
    Locator_t locator;
    IPLocator::setIPv4(locator, "10.102.1.156");
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
    DataWriterQos writerQos;
    writerQos.reliability().kind = RELIABLE_RELIABILITY_QOS;
    writer_ = publisher_->create_datawriter(topic_, DATAWRITER_QOS_DEFAULT, &listener_);
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