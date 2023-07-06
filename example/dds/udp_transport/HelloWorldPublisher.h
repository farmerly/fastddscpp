#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/topic/Topic.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>

#include "DDSPublisherListener.h"
#include "HelloWorldPubSubTypes.h"

class HelloWorldPublisher
{
public:
    HelloWorldPublisher();
    virtual ~HelloWorldPublisher();

public:
    bool init();
    bool publish(std::shared_ptr<HelloWorld> hello);
    void run();

private:
    eprosima::fastdds::dds::DomainParticipant *participant_;
    eprosima::fastdds::dds::Publisher *publisher_;
    eprosima::fastdds::dds::DataWriter *writer_;
    eprosima::fastdds::dds::Topic *topic_;
    DDSPublisherListener listener_;

private:
    eprosima::fastdds::dds::TypeSupport m_type;
};
