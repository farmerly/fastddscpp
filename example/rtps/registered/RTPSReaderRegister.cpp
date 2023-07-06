#include "RTPSReaderRegister.h"

#include <fastrtps/attributes/TopicAttributes.h>
#include <fastrtps/qos/ReaderQos.h>
#include <fastrtps/rtps/RTPSDomain.h>
#include <fastrtps/rtps/attributes/HistoryAttributes.h>
#include <fastrtps/rtps/attributes/RTPSParticipantAttributes.h>
#include <fastrtps/rtps/attributes/ReaderAttributes.h>
#include <fastrtps/rtps/history/ReaderHistory.h>
#include <fastrtps/rtps/participant/RTPSParticipant.h>
#include <fastrtps/rtps/reader/RTPSReader.h>

using namespace eprosima::fastrtps::rtps;

RTPSReaderRegister::RTPSReaderRegister()
{
    mp_participant = nullptr;
    mp_reader = nullptr;
    mp_history = nullptr;
}

RTPSReaderRegister::~RTPSReaderRegister()
{
    RTPSDomain::removeRTPSParticipant(mp_participant);
    delete (mp_history);
}

bool RTPSReaderRegister::init()
{
    // create Participant
    RTPSParticipantAttributes param;
    param.builtin.discovery_config.discoveryProtocol = DiscoveryProtocol::SIMPLE;
    param.builtin.use_WriterLivelinessProtocol = true;
    mp_participant = RTPSDomain::createParticipant(0, param);
    if (mp_participant == nullptr)
        return false;

    // create ReaderHistory
    HistoryAttributes hisAttr;
    hisAttr.payloadMaxSize = 255;
    mp_history = new ReaderHistory(hisAttr);

    // create Reader
    ReaderAttributes rAttr;
    Locator_t locator(22222);
    rAttr.endpoint.unicastLocatorList.push_back(locator);
    mp_reader = RTPSDomain::createRTPSReader(mp_participant, rAttr, mp_history, &m_listener);
    if (mp_reader == nullptr) {
        return false;
    }

    return true;
}

bool RTPSReaderRegister::reg()
{
    eprosima::fastrtps::TopicAttributes topicAttr;
    topicAttr.topicKind = NO_KEY;
    topicAttr.topicDataType = "string";
    topicAttr.topicName = "exampleTopic";
    eprosima::fastrtps::ReaderQos readerQos;
    return mp_participant->registerReader(mp_reader, topicAttr, readerQos);
}

void RTPSReaderRegister::run()
{
    printf("Press Enter to stop the Reader.\n");
    std::cin.ignore();
}
