#include "RTPSWriterRegister.h"

#include <fastrtps/attributes/TopicAttributes.h>
#include <fastrtps/qos/WriterQos.h>
#include <fastrtps/rtps/RTPSDomain.h>
#include <fastrtps/rtps/attributes/HistoryAttributes.h>
#include <fastrtps/rtps/attributes/RTPSParticipantAttributes.h>
#include <fastrtps/rtps/attributes/WriterAttributes.h>
#include <fastrtps/rtps/history/WriterHistory.h>
#include <fastrtps/rtps/participant/RTPSParticipant.h>
#include <fastrtps/rtps/writer/RTPSWriter.h>

using namespace eprosima::fastrtps::rtps;

RTPSWriterRegister::RTPSWriterRegister()
{
    mp_participant = nullptr;
    mp_writer = nullptr;
    mp_history = nullptr;
}

RTPSWriterRegister::~RTPSWriterRegister()
{
    RTPSDomain::removeRTPSParticipant(mp_participant);
    delete (mp_history);
}

bool RTPSWriterRegister::init()
{
    // create Participant
    RTPSParticipantAttributes param;
    param.builtin.discovery_config.discoveryProtocol = DiscoveryProtocol::SIMPLE;
    param.builtin.use_WriterLivelinessProtocol = true;
    mp_participant = RTPSDomain::createParticipant(0, param);
    if (mp_participant == nullptr)
        return false;

    // create WriterHistory
    HistoryAttributes hisAttr;
    hisAttr.payloadMaxSize = 255;
    hisAttr.maximumReservedCaches = 50;
    mp_history = new WriterHistory(hisAttr);

    // create writer
    WriterAttributes wAttr;
    wAttr.endpoint.reliabilityKind = BEST_EFFORT;
    mp_writer = RTPSDomain::createRTPSWriter(mp_participant, wAttr, mp_history, &m_listener);
    if (mp_writer == nullptr)
        return false;

    return true;
}

bool RTPSWriterRegister::reg()
{
    std::cout << "Registering Writer" << std::endl;
    eprosima::fastrtps::TopicAttributes topicAttr;
    topicAttr.topicKind = NO_KEY;
    topicAttr.topicDataType = "string";
    topicAttr.topicName = "exampleTopic";
    eprosima::fastrtps::WriterQos writerQos;
    return mp_participant->registerWriter(mp_writer, topicAttr, writerQos);
}

void RTPSWriterRegister::run(uint16_t samples)
{
    std::cout << "Waiting for matched Readers" << std::endl;
    while (m_listener.n_matched == 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

    for (int i = 0; i < samples; ++i) {
        CacheChange_t *ch = mp_writer->new_change(
            []() -> uint32_t {
                return 255;
            },
            ALIVE);
        if (!ch) {
            std::cout << "cleaning history..." << std::endl;
            mp_writer->remove_older_changes(20);
            ch = mp_writer->new_change(
                []() -> uint32_t {
                    return 255;
                },
                ALIVE);
        }

#if defined(_WIN32)
        ch->serializedPayload.length = sprintf_s((char *)ch->serializedPayload.data, 255, "My example string: %d", i) + 1;
#else
        ch->serializedPayload.length = sprintf((char *)ch->serializedPayload.data, "My example string: %d", i) + 1;
#endif // if defined(_WIN32)
        printf("sending: %s\n", (char *)ch->serializedPayload.data);
        mp_history->add_change(ch);
    }
}
