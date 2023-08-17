#ifndef DDS_DOMAIN_PARTICIPANT_H_H_H
#define DDS_DOMAIN_PARTICIPANT_H_H_H

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>

class DDSDomainParticipant
{
public:
    DDSDomainParticipant(int domainId, const eprosima::fastdds::dds::DomainParticipantQos &participantQos);
    virtual ~DDSDomainParticipant();

public:
    eprosima::fastdds::dds::DataWriter *createDataWriter(eprosima::fastdds::dds::Topic *topic,
                                                         eprosima::fastdds::dds::DataWriterQos dataWriterQos,
                                                         eprosima::fastdds::dds::DataWriterListener &listener);
    eprosima::fastdds::dds::DataReader *createDataReader(eprosima::fastdds::dds::Topic *topic,
                                                         eprosima::fastdds::dds::DataReaderQos dataReaderQos,
                                                         eprosima::fastdds::dds::DataReaderListener &listener);
    eprosima::fastdds::dds::Topic *registerTopic(std::string topicName, std::string typeName,
                                                 const eprosima::fastdds::dds::TopicQos &topicQos,
                                                 eprosima::fastdds::dds::TypeSupport &typeSupport);
    bool unregisterTopic(std::string typeName);

private:
    eprosima::fastdds::dds::DomainParticipant *m_participant;
    eprosima::fastdds::dds::Subscriber *m_subscriber;
    eprosima::fastdds::dds::Publisher *m_publisher;
};

#endif