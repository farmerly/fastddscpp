#include "DDSParticipantManager.h"
#include "HelloWorldConstants.h"
#include "HelloWorldOne.h"
#include "HelloWorldTwo.h"

class HelloWorldHandler : public ITopicDataTypeCreator, public ITopicDataTypeWorker
{
public:
    HelloWorldHandler();
    virtual ~HelloWorldHandler();

protected:
    CTopicDataTypeFactory                 *createProxyFactory() override;
    eprosima::fastdds::dds::TopicDataType *createTopicDataType(std::string typeName) override;
    DataPacketCreateCB                     getDataPacketCB(std::string typeName) override;
    DataPacketProcessCB                    getDataProcessCB(std::string typeName) override;

private:
    std::string         getTypeNameByTopic(std::string topicName);
    static IDataPacket *createCBHelloWorldOne();
    static IDataPacket *createCBHelloWorldTwo();
    static void         processCBHelloWorldOne(IDataPacket *data);
    static void         processCBHelloWorldTwo(IDataPacket *data);

public:
    bool init(uint32_t domain_id);
    bool publish(std::string topicName, void *data);
    bool registerPublisher(std::string topicName);
    bool registerSubscriber(std::string topicName);

private:
    DDSParticipantManager m_manager;
};
