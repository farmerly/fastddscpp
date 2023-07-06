#include "DDSPublisherListener.h"

DDSPublisherListener::DDSPublisherListener()
{
}

DDSPublisherListener::~DDSPublisherListener()
{
}

void DDSPublisherListener::on_publication_matched(eprosima::fastdds::dds::DataWriter *writer,
                                                  const eprosima::fastdds::dds::PublicationMatchedStatus &info)
{
    if (info.current_count_change == 1) {
        std::cout << "Publisher matched." << std::endl;
    } else if (info.current_count_change == -1) {
        std::cout << "Publisher unmatched." << std::endl;
    } else {
        std::cout << info.current_count_change << " is not a valid value for PublicationMatchedStatus current count change." << std::endl;
    }
}
