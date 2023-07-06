#ifndef TOPIC_DATA_TYPE_WORKER_H_H_H
#define TOPIC_DATA_TYPE_WORKER_H_H_H

#include "TopicDataTypeFactory.h"

class TopicDataTypeWorker
{
public:
    virtual TopicDataTypeFactory *createProxyFactory() = 0;
};

#endif