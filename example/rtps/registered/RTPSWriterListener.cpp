#include "RTPSWriterListener.h"

using namespace eprosima::fastrtps::rtps;

RTPSWriterListener::RTPSWriterListener()
{
    n_matched = 0;
}

RTPSWriterListener::~RTPSWriterListener()
{
}

void RTPSWriterListener::onWriterMatched(RTPSWriter *, MatchingInfo &info)
{
    if (info.status == MATCHED_MATCHING) {
        ++n_matched;
    }
}
