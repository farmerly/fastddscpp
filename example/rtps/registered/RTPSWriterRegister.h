#ifndef _RTPS_WRITER_REGISTER_H_H_H
#define _RTPS_WRITER_REGISTER_H_H_H

#include <fastrtps/rtps/history/WriterHistory.h>
#include <fastrtps/rtps/participant/RTPSParticipant.h>
#include <fastrtps/rtps/writer/RTPSWriter.h>

#include "RTPSWriterListener.h"

class RTPSWriterRegister
{
public:
    RTPSWriterRegister();
    ~RTPSWriterRegister();

public:
    bool init();
    bool reg();
    void run(uint16_t samples);

private:
    eprosima::fastrtps::rtps::RTPSParticipant *mp_participant;
    eprosima::fastrtps::rtps::RTPSWriter *mp_writer;
    eprosima::fastrtps::rtps::WriterHistory *mp_history;
    RTPSWriterListener m_listener;
};

#endif // ifndef _RTPS_WRITER_REGISTER_H_H_H
