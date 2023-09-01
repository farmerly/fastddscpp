#include "CDDSTopicDataReader.h"
#include <glog/logging.h>

CDDSTopicDataReader::CDDSTopicDataReader()
{
}

CDDSTopicDataReader::~CDDSTopicDataReader()
{
}

bool CDDSTopicDataReader::initDataReader(std::string                          topicName,
                                         std::string                          typeName,
                                         CDDSDomainParticipant               *participant,
                                         eprosima::fastdds::dds::TypeSupport &typeSupport,
                                         IDataPacket *(*createCallback)(),
                                         void (*processCallback)(void *, IDataPacket *),
                                         void *processArgs)
{
    // 需要先注册回调函数, 之后再创建 dataReader, 以防监听启动后回调方法为null
    if (!createCallback || !processCallback) {
        return false;
    }
    m_readerListener.m_createCallback = createCallback;
    m_readerListener.m_processCallback = processCallback;
    m_readerListener.m_processArgs = processArgs;
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

void CDDSTopicDataReader::DDSDataReaderListener::on_subscription_matched(eprosima::fastdds::dds::DataReader                      *reader,
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

void CDDSTopicDataReader::DDSDataReaderListener::on_data_available(eprosima::fastdds::dds::DataReader *reader)
{
    eprosima::fastdds::dds::SampleInfo info;
    IDataPacket                       *m_data = m_createCallback();
    ReturnCode_t                       retCode = reader->take_next_sample(m_data->getData(), &info);
    if (retCode == ReturnCode_t::RETCODE_OK) {
        if (info.valid_data) {
            m_processCallback(m_processArgs, m_data);
        } else {
            LOG(ERROR) << "info invalid";
        }
    } else {
        LOG(ERROR) << "take_next_sample error";
    }
}

void CDDSTopicDataReader::DDSDataReaderListener::on_liveliness_changed(eprosima::fastdds::dds::DataReader                *reader,
                                                                       const eprosima::fastrtps::LivelinessChangedStatus &status)
{
    std::cout << "on_liveliness_changed: " << status.alive_count << std::endl;
}