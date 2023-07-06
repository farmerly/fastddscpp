#include "RTPSReaderListener.h"

using namespace eprosima::fastrtps::rtps;

RTPSReaderListener::RTPSReaderListener()
{
    n_received = 0;
    n_matched = 0;
}

RTPSReaderListener::~RTPSReaderListener()
{
}

void RTPSReaderListener::onReaderMatched(RTPSReader *, MatchingInfo &info)
{
    if (info.status == MATCHED_MATCHING) {
        n_matched++;
    }
}

void RTPSReaderListener::onNewCacheChangeAdded(RTPSReader *reader, const CacheChange_t *const change)
{
    printf("Received: %s\n", change->serializedPayload.data);
    reader->getHistory()->remove_change((CacheChange_t *)change);
    n_received++;
}
