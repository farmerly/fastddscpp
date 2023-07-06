#ifndef _RTPS_READER_REGISTER_H_H_H
#define _RTPS_READER_REGISTER_H_H_H

#include <fastrtps/rtps/history/ReaderHistory.h>
#include <fastrtps/rtps/participant/RTPSParticipant.h>
#include <fastrtps/rtps/reader/RTPSReader.h>

#include "RTPSReaderListener.h"

class RTPSReaderRegister
{
public:
    RTPSReaderRegister();
    ~RTPSReaderRegister();

public:
    bool init();
    bool reg();
    void run();

private:
    eprosima::fastrtps::rtps::RTPSParticipant *mp_participant;
    eprosima::fastrtps::rtps::RTPSReader *mp_reader;
    eprosima::fastrtps::rtps::ReaderHistory *mp_history;
    RTPSReaderListener m_listener;
};

#endif // ifndef _RTPS_READER_REGISTER_H_H_H
