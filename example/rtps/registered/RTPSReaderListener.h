#ifndef _READER_LISTENER_H_H_H
#define _READER_LISTENER_H_H_H

#include <fastrtps/rtps/reader/RTPSReader.h>
#include <fastrtps/rtps/reader/ReaderListener.h>

class RTPSReaderListener : public eprosima::fastrtps::rtps::ReaderListener
{
public:
    RTPSReaderListener();
    ~RTPSReaderListener();

public:
    void onNewCacheChangeAdded(eprosima::fastrtps::rtps::RTPSReader *reader, const eprosima::fastrtps::rtps::CacheChange_t *const change);
    void onReaderMatched(eprosima::fastrtps::rtps::RTPSReader *, eprosima::fastrtps::rtps::MatchingInfo &info);

public:
    uint32_t n_received;
    uint32_t n_matched;
};

#endif // ifndef _READER_LISTENER_H_H_H
