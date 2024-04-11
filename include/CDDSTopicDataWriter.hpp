#pragma once

#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>
#include <glog/logging.h>

template <typename T>
class CDDSTopicDataWriter
{
public:
    CDDSTopicDataWriter() = default;
    ~CDDSTopicDataWriter() = default;

public:
    bool initDataWriter(eprosima::fastdds::dds::Publisher           *publisher,
                        eprosima::fastdds::dds::Topic               *topic,
                        const eprosima::fastdds::dds::DataWriterQos &dataWriterQos);
    bool writeMessage(const T &message);

private:
    class DDSDataWriterListener : public eprosima::fastdds::dds::DataWriterListener
    {
    protected:
        void on_publication_matched(eprosima::fastdds::dds::DataWriter                     *writer,
                                    const eprosima::fastdds::dds::PublicationMatchedStatus &info);
    } m_writerListener;
    eprosima::fastdds::dds::DataWriter *m_dataWriter;
};

template <typename T>
bool CDDSTopicDataWriter<T>::initDataWriter(eprosima::fastdds::dds::Publisher           *publisher,
                                            eprosima::fastdds::dds::Topic               *topic,
                                            const eprosima::fastdds::dds::DataWriterQos &dataWriterQos)
{
    if (!publisher || !topic)
        return false;

    if (!m_dataWriter)
        m_dataWriter = publisher->create_datawriter(topic, dataWriterQos, &m_writerListener);
    return (m_dataWriter != nullptr);
}

template <typename T>
bool CDDSTopicDataWriter<T>::writeMessage(const T &message)
{
    return m_dataWriter->write((void *)&message);
}

template <typename T>
void CDDSTopicDataWriter<T>::DDSDataWriterListener::on_publication_matched(eprosima::fastdds::dds::DataWriter                     *writer,
                                                                           const eprosima::fastdds::dds::PublicationMatchedStatus &info)
{
    if (info.current_count_change == 1) {
        LOG(INFO) << "\033[31mPublication matched\033[0m";
    } else if (info.current_count_change == -1) {
        LOG(INFO) << "\033[31mPublication unmatched\033[0m";
    } else {
        LOG(INFO) << info.current_count_change << " is not a valid value for PublicationMatchedStatus current count change" << std::endl;
    }
}