#include "CDDSDomainParticipant.h"
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/qos/PublisherQos.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/subscriber/qos/SubscriberQos.hpp>
#include <glog/logging.h>
#include <mutex>

using namespace eprosima::fastdds::dds;

CDDSDomainParticipant::CDDSDomainParticipant(int domainId, const eprosima::fastdds::dds::DomainParticipantQos &participantQos)
{
    m_participant = DomainParticipantFactory::get_instance()->create_participant(domainId, participantQos);
    if (m_participant) {
        eprosima::fastdds::dds::SubscriberQos subscriberQos(SUBSCRIBER_QOS_DEFAULT);
        m_subscriber = m_participant->create_subscriber(subscriberQos, nullptr);

        eprosima::fastdds::dds::PublisherQos publisherQos(PUBLISHER_QOS_DEFAULT);
        m_publisher = m_participant->create_publisher(publisherQos, nullptr);
    }
}

CDDSDomainParticipant::~CDDSDomainParticipant()
{
    if (m_participant) {
        DomainParticipantFactory::get_instance()->delete_participant(m_participant);
    }
}

Topic *CDDSDomainParticipant::registerTopic(std::string topicName, const TopicQos &topicQos, TypeSupport &typeSupport)
{
    std::lock_guard<std::mutex> guard(m_topicLock);
    if (m_mapTopics.find(topicName) != m_mapTopics.end())
        return m_mapTopics.at(topicName);

    ReturnCode_t errCode = typeSupport.register_type(m_participant);
    if (errCode != ReturnCode_t::RETCODE_OK)
        return nullptr;

    Topic *topic = m_participant->create_topic(topicName, typeSupport->getName(), topicQos);
    if (topic != nullptr) {
        m_mapTopics.insert(std::pair<std::string, Topic *>(topicName, topic));
    }
    return topic;
}

bool CDDSDomainParticipant::unregisterTopic(std::string topicName)
{
    std::lock_guard<std::mutex> guard(m_topicLock);
    if (m_mapTopics.find(topicName) == m_mapTopics.end())
        return true;

    auto topic = m_mapTopics.at(topicName);
    if (topic) {
        ReturnCode_t errCode = m_participant->delete_topic(topic);
        if (errCode != ReturnCode_t::RETCODE_OK) {
            LOG(ERROR) << "unregister_type " << topicName << " error, errcode: " << errCode();
            return false;
        }
        delete topic;
    }
    m_mapTopics.erase(topicName);
    return true;
}