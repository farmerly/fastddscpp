#pragma once

#include "DDSDomainParticipant.h"
#include "IDataPacket.h"
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>

class CDDSTopicDataReader
{
public:
    CDDSTopicDataReader();
    ~CDDSTopicDataReader();

public:
    bool initDataReader(std::string                          topicName,
                        std::string                          typeName,
                        DDSDomainParticipant                *participant,
                        eprosima::fastdds::dds::TypeSupport &typeSupport,
                        IDataPacket *(*createCallback)(),
                        void (*processCallback)(IDataPacket *));

private:
    class DDSDataReaderListener : public eprosima::fastdds::dds::DataReaderListener
    {
    protected:
        void on_subscription_matched(eprosima::fastdds::dds::DataReader                      *reader,
                                     const eprosima::fastdds::dds::SubscriptionMatchedStatus &info);
        void on_data_available(eprosima::fastdds::dds::DataReader *reader);
        void on_liveliness_changed(eprosima::fastdds::dds::DataReader *reader, const eprosima::fastrtps::LivelinessChangedStatus &status);

    public:
        IDataPacket *(*createCallback)();
        void (*processCallback)(IDataPacket *);
    } m_readerListener;
    eprosima::fastdds::dds::DataReader *m_dataReader;
    eprosima::fastdds::dds::Topic      *m_topic;
};