#include "CDDSHandler.h"
#include "CDDSDomainParticipant.h"
#include "CDDSTopicDataReader.hpp"
#include "CDDSTopicDataWriter.hpp"
#include "CParticipantQosHandler.h"
#include "DDSConstants.h"
#include "HelloWorldOne.h"
#include "HelloWorldOnePubSubTypes.h"
#include "HelloWorldTwo.h"
#include "HelloWorldTwoPubSubTypes.h"
#include <chrono>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fastdds/dds/topic/qos/TopicQos.hpp>
#include <glog/logging.h>
#include <thread>

using namespace eprosima::fastdds::dds;
using namespace eprosima::fastdds::rtps;
using namespace eprosima::fastrtps::rtps;

void processHelloWorldOne(std::shared_ptr<HelloWorldOne> data)
{
    std::cout << "recv message: " << data->index() << std::endl;
}

void run_dds_data_writer()
{
    CParticipantQosHandler participantQosManager("test_writer");
    participantQosManager.addSHMTransport(153600);
    CDDSDomainParticipant participant(170, participantQosManager.getQos());

    eprosima::fastdds::dds::TopicQos topicQos(TOPIC_QOS_DEFAULT);
    participant.registerTopic(DDS_TOPIC_HELLO_WORLD_ONE, new HelloWorldOnePubSubType(), topicQos);
    eprosima::fastdds::dds::DataWriterQos dataWriterQos(DATAWRITER_QOS_DEFAULT);
    CDDSTopicDataWriter<HelloWorldOne> *dataWriter = participant.createDataWriter<HelloWorldOne>(DDS_TOPIC_HELLO_WORLD_ONE, dataWriterQos);

    int index = 0;
    while (true) {
        HelloWorldOne message;
        message.index(++index);
        message.points(std::vector<uint8_t>(100));
        if (dataWriter->writeMessage(message)) {
            std::cout << "send message: " << message.index() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void run_dds_data_reader()
{
    CParticipantQosHandler participantQosManager("test_reader");
    participantQosManager.addSHMTransport(153600);
    CDDSDomainParticipant participant(170, participantQosManager.getQos());

    eprosima::fastdds::dds::TopicQos topicQos(TOPIC_QOS_DEFAULT);
    participant.registerTopic(DDS_TOPIC_HELLO_WORLD_ONE, new HelloWorldOnePubSubType(), topicQos);
    eprosima::fastdds::dds::DataReaderQos dataReaderQos(DATAREADER_QOS_DEFAULT);
    CDDSTopicDataReader<HelloWorldOne>   *dataReader =
        participant.createDataReader<HelloWorldOne>(DDS_TOPIC_HELLO_WORLD_ONE, processHelloWorldOne, dataReaderQos);

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
