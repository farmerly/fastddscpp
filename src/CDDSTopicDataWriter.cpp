#include "CDDSTopicDataWriter.h"
#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>
#include <glog/logging.h>

using namespace eprosima::fastdds::dds;

CDDSTopicDataWriter::CDDSTopicDataWriter()
{
}

CDDSTopicDataWriter::~CDDSTopicDataWriter()
{
}

bool CDDSTopicDataWriter::initDataWriter(std::string                          topicName,
                                         std::string                          typeName,
                                         CDDSDomainParticipant               *participant,
                                         eprosima::fastdds::dds::TypeSupport &typeSupport)
{
    TopicQos topicQos(TOPIC_QOS_DEFAULT);
    Topic   *topic = participant->registerTopic(topicName, typeName, topicQos, typeSupport);
    if (topic == nullptr) {
        return false;
    }

    eprosima::fastdds::dds::DataWriterQos dataWriterQos(DATAWRITER_QOS_DEFAULT);
    m_dataWriter = participant->createDataWriter(topic, dataWriterQos, m_writerListener);
    return (m_dataWriter != nullptr);
}

bool CDDSTopicDataWriter::sendData(void *data)
{
    return m_dataWriter->write(data);
}

void CDDSTopicDataWriter::DDSDataWriterListener::on_publication_matched(eprosima::fastdds::dds::DataWriter                     *writer,
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