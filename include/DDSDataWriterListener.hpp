#pragma once

#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <glog/logging.h>

class DDSDataWriterListener : public eprosima::fastdds::dds::DataWriterListener
{
protected:
    void on_publication_matched(eprosima::fastdds::dds::DataWriter *writer, const eprosima::fastdds::dds::PublicationMatchedStatus &info)
    {
        LOG(INFO) << "on_publication_matched: " << info.total_count;
    }

    void on_offered_deadline_missed(eprosima::fastdds::dds::DataWriter                        *writer,
                                    const eprosima::fastdds::dds::OfferedDeadlineMissedStatus &status)
    {
        LOG(INFO) << "on_publication_matched: " << status.total_count;
    }

    void on_liveliness_lost(eprosima::fastdds::dds::DataWriter *writer, const eprosima::fastdds::dds::LivelinessLostStatus &status)
    {
        LOG(INFO) << "on_liveliness_lost: " << status.total_count;
    }
};
