#include "CDDSDomainParticipant.h"
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/qos/PublisherQos.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/subscriber/qos/SubscriberQos.hpp>

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

eprosima::fastdds::dds::DataWriter *CDDSDomainParticipant::createDataWriter(eprosima::fastdds::dds::Topic              *topic,
                                                                            eprosima::fastdds::dds::DataWriterQos       dataWriterQos,
                                                                            eprosima::fastdds::dds::DataWriterListener &listener)
{
    return m_publisher->create_datawriter(topic, dataWriterQos, &listener);
}

eprosima::fastdds::dds::DataReader *CDDSDomainParticipant::createDataReader(eprosima::fastdds::dds::Topic              *topic,
                                                                            eprosima::fastdds::dds::DataReaderQos       dataReaderQos,
                                                                            eprosima::fastdds::dds::DataReaderListener &listener)
{
    return m_subscriber->create_datareader(topic, dataReaderQos, &listener);
}

Topic *CDDSDomainParticipant::registerTopic(std::string topicName, std::string typeName, const TopicQos &topicQos, TypeSupport &typeSupport)
{
    ReturnCode_t errCode = typeSupport.register_type(m_participant);
    if (errCode != ReturnCode_t::RETCODE_OK) {
        return nullptr;
    }
    return m_participant->create_topic(topicName, typeName, topicQos);
}

bool CDDSDomainParticipant::unregisterTopic(std::string type_name)
{
    ReturnCode_t errCode = m_participant->unregister_type(type_name);
    if (errCode != ReturnCode_t::RETCODE_OK) {
        std::cerr << "unregister_type " << type_name << " error, errcode: " << errCode() << std::endl;
        return false;
    }
    return true;
}