#ifndef _WRITER_LISTENER_H_H_H
#define _WRITER_LISTENER_H_H_H

#include <fastrtps/rtps/writer/RTPSWriter.h>
#include <fastrtps/rtps/writer/WriterListener.h>

class RTPSWriterListener : public eprosima::fastrtps::rtps::WriterListener
{
public:
    RTPSWriterListener();
    ~RTPSWriterListener();

public:
    void onWriterMatched(eprosima::fastrtps::rtps::RTPSWriter *, eprosima::fastrtps::rtps::MatchingInfo &info);

public:
    int n_matched;
};

#endif // ifndef _WRITER_LISTENER_H_H_H
