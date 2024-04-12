#ifndef DDS_DOMAIN_PARTICIPANT_H_H_H
#define DDS_DOMAIN_PARTICIPANT_H_H_H

#include "CDDSTopicDataReader.hpp"
#include "CDDSTopicDataWriter.hpp"

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>

#include <fastdds/dds/topic/TopicDataType.hpp>
#include <mutex>
#include <unordered_map>

class CDDSDomainParticipant
{
public:
    CDDSDomainParticipant(int domainId, const eprosima::fastdds::dds::DomainParticipantQos &participantQos);
    virtual ~CDDSDomainParticipant();

public:
    template <typename T>
    CDDSTopicDataWriter<T> *createDataWriter(std::string topicName, eprosima::fastdds::dds::DataWriterQos dataWriterQos);

    template <typename T>
    CDDSTopicDataReader<T> *createDataReader(std::string                                  topicName,
                                             std::function<void(std::shared_ptr<T>)>      callback,
                                             const eprosima::fastdds::dds::DataReaderQos &dataReaderQos);

    eprosima::fastdds::dds::Topic *registerTopic(
        std::string                             topicName,
        eprosima::fastdds::dds::TopicDataType  *dataType,
        const eprosima::fastdds::dds::TopicQos &topicQos = eprosima::fastdds::dds::TOPIC_QOS_DEFAULT);

    bool unregisterTopic(std::string topicName);

private:
    eprosima::fastdds::dds::DomainParticipant                       *m_participant;
    eprosima::fastdds::dds::Subscriber                              *m_subscriber;
    eprosima::fastdds::dds::Publisher                               *m_publisher;
    std::unordered_map<std::string, eprosima::fastdds::dds::Topic *> m_mapTopics;
    std::mutex                                                       m_topicLock;
};

template <typename T>
CDDSTopicDataWriter<T> *CDDSDomainParticipant::createDataWriter(std::string topicName, eprosima::fastdds::dds::DataWriterQos dataWriterQos)
{
    std::lock_guard<std::mutex> guard(m_topicLock);
    if (m_mapTopics.find(topicName) == m_mapTopics.end())
        return nullptr;

    CDDSTopicDataWriter<T> *dataWriter = new CDDSTopicDataWriter<T>();
    dataWriter->initDataWriter(m_publisher, m_mapTopics.at(topicName), dataWriterQos);
    return dataWriter;
}

template <typename T>
CDDSTopicDataReader<T> *CDDSDomainParticipant::createDataReader(std::string                                  topicName,
                                                                std::function<void(std::shared_ptr<T>)>      callback,
                                                                const eprosima::fastdds::dds::DataReaderQos &dataReaderQos)
{
    std::lock_guard<std::mutex> guard(m_topicLock);
    if (m_mapTopics.find(topicName) == m_mapTopics.end())
        return nullptr;

    CDDSTopicDataReader<T> *dataReader = new CDDSTopicDataReader<T>();
    dataReader->initDataReader(m_subscriber, m_mapTopics.at(topicName), callback, dataReaderQos);
    return dataReader;
}

#endif