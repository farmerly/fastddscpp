#pragma once

#include "CDDSDomainParticipant.h"
#include "IDDSDataPacket.h"
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
                        CDDSDomainParticipant               *participant,
                        eprosima::fastdds::dds::TypeSupport &typeSupport,
                        IDDSDataPacket *(*createCallback)(),
                        void (*processCallback)(void *, IDDSDataPacket *),
                        void *processArgs);

private:
    class DDSDataReaderListener : public eprosima::fastdds::dds::DataReaderListener
    {
    protected:
        void on_subscription_matched(eprosima::fastdds::dds::DataReader                      *reader,
                                     const eprosima::fastdds::dds::SubscriptionMatchedStatus &info);
        void on_data_available(eprosima::fastdds::dds::DataReader *reader);
        void on_liveliness_changed(eprosima::fastdds::dds::DataReader *reader, const eprosima::fastrtps::LivelinessChangedStatus &status);

    public:
        void *m_processArgs;
        IDDSDataPacket *(*m_createCallback)();
        void (*m_processCallback)(void *, IDDSDataPacket *);
    } m_readerListener;
    eprosima::fastdds::dds::DataReader *m_dataReader;
};