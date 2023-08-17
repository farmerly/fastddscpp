#include "CDDSTopicDataWriter.h"

CDDSTopicDataWriter::CDDSTopicDataWriter()
{
}

CDDSTopicDataWriter::~CDDSTopicDataWriter()
{
}

bool CDDSTopicDataWriter::initDataWriter(std::string                          topicName,
                                         std::string                          typeName,
                                         DDSDomainParticipant                *participant,
                                         eprosima::fastdds::dds::TypeSupport &typeSupport)
{
    m_topic = participant->registerTopic(topicName, typeName, eprosima::fastdds::dds::TOPIC_QOS_DEFAULT, typeSupport);
    if (m_topic == nullptr) {
        return false;
    }

    m_dataWriter = participant->createDataWriter(m_topic, eprosima::fastdds::dds::DATAWRITER_QOS_DEFAULT, m_writerListener);
    if (m_dataWriter == nullptr) {
        delete m_topic;
        return false;
    }
    return true;
}

bool CDDSTopicDataWriter::sendData(void *data)
{
    return m_dataWriter->write(data);
}

void CDDSTopicDataWriter::DDSDataWriterListener::on_publication_matched(eprosima::fastdds::dds::DataWriter                     *writer,
                                                                        const eprosima::fastdds::dds::PublicationMatchedStatus &info)
{
    if (info.current_count_change == 1) {
        std::cout << "Publisher matched" << std::endl;
    } else if (info.current_count_change == -1) {
        std::cout << "Publisher unmatched" << std::endl;
    } else {
        std::cout << info.current_count_change << " is not a valid value for PublicationMatchedStatus current count change" << std::endl;
    }
}