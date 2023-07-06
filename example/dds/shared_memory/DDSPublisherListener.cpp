#include "DDSPublisherListener.h"

using namespace eprosima::fastdds::dds;

DDSPublisherListener::DDSPublisherListener()
{
    _matched = 0;
}

DDSPublisherListener::~DDSPublisherListener()
{
}

void DDSPublisherListener::on_publication_matched(DataWriter *writer, const PublicationMatchedStatus &info)
{
    if (info.current_count_change == 1) {
        _matched++;
        std::cout << "Publisher matched" << std::endl;
    } else if (info.current_count_change == -1) {
        _matched--;
        std::cout << "Publisher unmatched" << std::endl;
    } else {
        std::cout << info.current_count_change << " is not a valid value for PublicationMatchedStatus current count change" << std::endl;
    }
}