#ifndef TOPIC_DATA_TYPE_WORKER_H_H_H
#define TOPIC_DATA_TYPE_WORKER_H_H_H

#include "CTopicDataTypeFactory.h"

class ITopicDataTypeWorker
{
public:
    ITopicDataTypeWorker() = default;
    virtual ~ITopicDataTypeWorker() = default;

public:
    virtual CTopicDataTypeFactory *createProxyFactory() = 0;
};

#endif