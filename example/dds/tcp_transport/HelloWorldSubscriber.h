#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/topic/Topic.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>

#include "DDSSubscriberListener.h"
#include "HelloWorldPubSubTypes.h"

class HelloWorldSubscriber
{
public:
    HelloWorldSubscriber();
    virtual ~HelloWorldSubscriber();

public:
    bool init(const std::string &participantName, const unsigned short &port, bool useTLS);
    void run();

private:
    eprosima::fastdds::dds::DomainParticipant *participant_;
    eprosima::fastdds::dds::Subscriber *subscriber_;
    eprosima::fastdds::dds::DataReader *reader_;
    eprosima::fastdds::dds::Topic *topic_;
    DDSSubscriberListener listener_;

private:
    eprosima::fastdds::dds::TypeSupport m_type;
};
