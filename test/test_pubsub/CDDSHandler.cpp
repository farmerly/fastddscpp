#include "CDDSHandler.h"
#include "DDSConstants.h"
#include "DDSDomainParticipant.h"
#include "DDSTopicDataReader.hpp"
#include "DDSTopicDataWriter.hpp"
#include "HelloWorldOne.h"
#include "HelloWorldOnePubSubTypes.h"
#include "HelloWorldTwo.h"
#include "HelloWorldTwoPubSubTypes.h"
#include "ParticipantQosHandler.h"
#include <chrono>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fastdds/dds/topic/qos/TopicQos.hpp>
#include <glog/logging.h>
#include <iostream>
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
    ParticipantQosHandler participantQosManager("test_writer");
    participantQosManager.addSHMTransport(153600);
    DDSDomainParticipant participant(170, participantQosManager.getQos());

    eprosima::fastdds::dds::TopicQos topicQos(TOPIC_QOS_DEFAULT);
    participant.registerTopic(DDS_TOPIC_HELLO_WORLD_ONE, new HelloWorldOnePubSubType(), topicQos);
    eprosima::fastdds::dds::DataWriterQos dataWriterQos(DATAWRITER_QOS_DEFAULT);
    DDSTopicDataWriter<HelloWorldOne> *dataWriter = participant.createDataWriter<HelloWorldOne>(DDS_TOPIC_HELLO_WORLD_ONE, dataWriterQos);

    int index = 0;
    while (true) {
        HelloWorldOne message;
        message.index(++index);
        message.points(std::vector<uint8_t>(100));
        if (dataWriter->writeMessage(message)) {
            std::cout << "send message: " << message.index() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void run_dds_data_reader()
{
    ParticipantQosHandler participantQosManager("test_reader");
    participantQosManager.addSHMTransport(153600);
    DDSDomainParticipant participant(170, participantQosManager.getQos());

    eprosima::fastdds::dds::TopicQos topicQos(TOPIC_QOS_DEFAULT);
    participant.registerTopic(DDS_TOPIC_HELLO_WORLD_ONE, new HelloWorldOnePubSubType(), topicQos);
    participant.registerTopic(DDS_TOPIC_HELLO_WORLD_TWO, new HelloWorldTwoPubSubType(), topicQos);
    eprosima::fastdds::dds::DataReaderQos dataReaderQos(DATAREADER_QOS_DEFAULT);
    DDSTopicDataReader<HelloWorldOne>    *dataReader =
        participant.createDataReader<HelloWorldOne>(DDS_TOPIC_HELLO_WORLD_ONE, processHelloWorldOne, dataReaderQos);

    while (std::cin.get() != '\n') {
    }

    // delete dataReader;
}
