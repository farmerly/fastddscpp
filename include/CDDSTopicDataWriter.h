#pragma once

#include "CDDSDomainParticipant.h"
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>

class CDDSTopicDataWriter
{
public:
    CDDSTopicDataWriter();
    ~CDDSTopicDataWriter();

public:
    bool initDataWriter(std::string                          topicName,
                        std::string                          typeName,
                        CDDSDomainParticipant               *participant,
                        eprosima::fastdds::dds::TypeSupport &typeSupport);
    bool sendData(void *data);

private:
    class DDSDataWriterListener : public eprosima::fastdds::dds::DataWriterListener
    {
    protected:
        void on_publication_matched(eprosima::fastdds::dds::DataWriter                     *writer,
                                    const eprosima::fastdds::dds::PublicationMatchedStatus &info);
    } m_writerListener;
    eprosima::fastdds::dds::DataWriter *m_dataWriter;
};