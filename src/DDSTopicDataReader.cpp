#include "DDSTopicDataReader.h"

DDSTopicDataReader::DDSTopicDataReader()
{
}

DDSTopicDataReader::~DDSTopicDataReader()
{
}

bool DDSTopicDataReader::initDataReader(std::string                          topicName,
                                        std::string                          typeName,
                                        DDSDomainParticipant                *participant,
                                        eprosima::fastdds::dds::TypeSupport &typeSupport,
                                        IDataPacket *(*createCallback)(),
                                        void (*processCallback)(IDataPacket *))
{
    // 需要先注册回调函数, 之后再创建 dataReader, 以防监听启动后回调方法为null
    if (!createCallback || !processCallback) {
        return false;
    }
    m_readerListener.createCallback = createCallback;
    m_readerListener.processCallback = processCallback;
    m_topic = participant->registerTopic(topicName, typeName, eprosima::fastdds::dds::TOPIC_QOS_DEFAULT, typeSupport);
    if (m_topic == nullptr) {
        return false;
    }
    m_dataReader = participant->createDataReader(m_topic, eprosima::fastdds::dds::DATAREADER_QOS_DEFAULT, m_readerListener);
    if (m_dataReader == nullptr) {
        delete m_topic;
        return false;
    }
    return true;
}

void DDSTopicDataReader::DDSDataReaderListener::on_subscription_matched(eprosima::fastdds::dds::DataReader                      *reader,
                                                                        const eprosima::fastdds::dds::SubscriptionMatchedStatus &info)
{
    if (info.current_count_change == 1) {
        std::cout << "Subscriber matched" << std::endl;
    } else if (info.current_count_change == -1) {
        std::cout << "Subscriber unmatched" << std::endl;
    } else {
        std::cout << info.current_count_change << " is not a valid value for SubscriptionMatchedStatus current count change" << std::endl;
    }
}

void DDSTopicDataReader::DDSDataReaderListener::on_data_available(eprosima::fastdds::dds::DataReader *reader)
{
    IDataPacket                       *m_data = createCallback();
    eprosima::fastdds::dds::SampleInfo info;
    ReturnCode_t                       retCode = reader->take_next_sample(m_data->getData(), &info);
    if (retCode == ReturnCode_t::RETCODE_OK) {
        if (info.valid_data) {
            processCallback(m_data);
        } else {
            std::cout << "info invalid" << std::endl;
        }
    } else {
        std::cout << "take_next_sample error" << std::endl;
    }
}

void DDSTopicDataReader::DDSDataReaderListener::on_liveliness_changed(eprosima::fastdds::dds::DataReader                *reader,
                                                                      const eprosima::fastrtps::LivelinessChangedStatus &status)
{
    std::cout << "on_liveliness_changed: " << status.alive_count << std::endl;
}