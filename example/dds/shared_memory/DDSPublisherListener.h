#ifndef _DDS_PUBLISHER_LISTENER_H_H_H
#define _DDS_PUBLISHER_LISTENER_H_H_H

#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>

class DDSPublisherListener : public eprosima::fastdds::dds::DataWriterListener
{
public:
    DDSPublisherListener();
    virtual ~DDSPublisherListener();
    void on_publication_matched(eprosima::fastdds::dds::DataWriter *writer, const eprosima::fastdds::dds::PublicationMatchedStatus &info);

public:
    int getMatched()
    {
        return _matched;
    };

private:
    int _matched;
};

#endif // _DDS_PUBLISHER_LISTENER_H_H_H