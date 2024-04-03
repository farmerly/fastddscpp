#ifndef DDS_DOMAIN_PARTICIPANT_H_H_H
#define DDS_DOMAIN_PARTICIPANT_H_H_H

#include "CDDSTopicDataReader.hpp"
#include "CDDSTopicDataWriter.hpp"

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>

#include <mutex>
#include <unordered_map>

class CDDSDomainParticipant
{
public:
    CDDSDomainParticipant(int domainId, const eprosima::fastdds::dds::DomainParticipantQos &participantQos);
    virtual ~CDDSDomainParticipant();

public:
    template <typename T>
    eprosima::fastdds::dds::DataWriter *createDataWriter(std::string topicName, eprosima::fastdds::dds::DataWriterQos dataWriterQos);
    template <typename T>
    eprosima::fastdds::dds::DataReader *createDataReader(std::string                                  topicName,
                                                         const eprosima::fastdds::dds::DataReaderQos &dataReaderQos,
                                                         std::function<void(T)>                       callback);
    eprosima::fastdds::dds::Topic      *registerTopic(std::string                             topicName,
                                                      const eprosima::fastdds::dds::TopicQos &topicQos,
                                                      eprosima::fastdds::dds::TypeSupport    &typeSupport);
    bool                                unregisterTopic(std::string topicName);

private:
    eprosima::fastdds::dds::DomainParticipant                       *m_participant;
    eprosima::fastdds::dds::Subscriber                              *m_subscriber;
    eprosima::fastdds::dds::Publisher                               *m_publisher;
    std::unordered_map<std::string, eprosima::fastdds::dds::Topic *> m_mapTopics;
    std::mutex                                                       m_topicLock;
};

template <typename T>
eprosima::fastdds::dds::DataWriter *CDDSDomainParticipant::createDataWriter(std::string                           topicName,
                                                                            eprosima::fastdds::dds::DataWriterQos dataWriterQos)
{
    std::lock_guard<std::mutex> guard(m_topicLock);
    if (m_mapTopics.find(topicName) == m_mapTopics.end())
        return nullptr;

    CDDSTopicDataWriter<T> dataWriter = new CDDSTopicDataWriter<T>();
    dataWriter.initDataWriter(m_publisher, m_mapTopics.at(topicName), dataWriterQos);
    return dataWriter;
}

template <typename T>
eprosima::fastdds::dds::DataReader *CDDSDomainParticipant::createDataReader(std::string                                  topicName,
                                                                            const eprosima::fastdds::dds::DataReaderQos &dataReaderQos,
                                                                            std::function<void(T)>                       callback)
{
    std::lock_guard<std::mutex> guard(m_topicLock);
    if (m_mapTopics.find(topicName) == m_mapTopics.end())
        return nullptr;

    CDDSTopicDataReader<T> dataReader = new CDDSTopicDataReader<T>();

    dataReader.initDataReader(m_subscriber, m_mapTopics.at(topicName), dataReaderQos, callback);
    return dataReader;
}

#endif