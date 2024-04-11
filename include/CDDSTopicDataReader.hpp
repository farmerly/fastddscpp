#pragma once

#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/topic/Topic.hpp>
#include <glog/logging.h>

template <typename T>
class CDDSTopicDataReader
{
    typedef std::function<void(std::shared_ptr<T>)> ProcessCallback;

public:
    CDDSTopicDataReader();
    ~CDDSTopicDataReader();

public:
    bool initDataReader(eprosima::fastdds::dds::Subscriber          *subscriber,
                        eprosima::fastdds::dds::Topic               *topic,
                        const eprosima::fastdds::dds::DataReaderQos &dataReaderQos,
                        ProcessCallback                              callback);

private:
    class DDSDataReaderListener : public eprosima::fastdds::dds::DataReaderListener
    {
    protected:
        void on_subscription_matched(eprosima::fastdds::dds::DataReader                      *reader,
                                     const eprosima::fastdds::dds::SubscriptionMatchedStatus &info);
        void on_data_available(eprosima::fastdds::dds::DataReader *reader);
        void on_liveliness_changed(eprosima::fastdds::dds::DataReader *reader, const eprosima::fastrtps::LivelinessChangedStatus &status);

    public:
        ProcessCallback m_callback;
    } m_readerListener;
    eprosima::fastdds::dds::DataReader *m_dataReader;
};

template <typename T>
CDDSTopicDataReader<T>::CDDSTopicDataReader() : m_dataReader(nullptr)
{
}

template <typename T>
CDDSTopicDataReader<T>::~CDDSTopicDataReader()
{
    m_dataReader->close();
    delete m_dataReader;
}

template <typename T>
bool CDDSTopicDataReader<T>::initDataReader(eprosima::fastdds::dds::Subscriber          *subscriber,
                                            eprosima::fastdds::dds::Topic               *topic,
                                            const eprosima::fastdds::dds::DataReaderQos &dataReaderQos,
                                            ProcessCallback                              callback)
{
    if (!subscriber || !topic)
        return false;

    m_readerListener.m_processCallback = callback;
    if (!m_dataReader)
        m_dataReader = subscriber->create_datareader(topic, dataReaderQos, m_readerListener);
    return (m_dataReader != nullptr);
}

template <typename T>
void CDDSTopicDataReader<T>::DDSDataReaderListener::on_subscription_matched(eprosima::fastdds::dds::DataReader                      *reader,
                                                                            const eprosima::fastdds::dds::SubscriptionMatchedStatus &info)
{
    if (info.current_count_change == 1) {
        LOG(INFO) << "\033[31mSubscription matched\033[0m";
    } else if (info.current_count_change == -1) {
        LOG(INFO) << "\033[31mSubscription unmatched\033[0m";
    } else {
        LOG(INFO) << info.current_count_change << " is not a valid value for SubscriptionMatchedStatus current count change";
    }
}

template <typename T>
void CDDSTopicDataReader<T>::DDSDataReaderListener::on_data_available(eprosima::fastdds::dds::DataReader *reader)
{
    eprosima::fastdds::dds::SampleInfo info;
    std::shared_ptr<T>                 message = std::make_shared<T>();
    ReturnCode_t                       retCode = reader->take_next_sample(message.get(), &info);
    if (retCode == ReturnCode_t::RETCODE_OK && info.valid_data) {
        m_callback(message);
    } else {
        LOG(ERROR) << "take_next_sample error";
    }
}

template <typename T>
void CDDSTopicDataReader<T>::DDSDataReaderListener::on_liveliness_changed(eprosima::fastdds::dds::DataReader                *reader,
                                                                          const eprosima::fastrtps::LivelinessChangedStatus &status)
{
    std::cout << "on_liveliness_changed: " << status.alive_count << std::endl;
}