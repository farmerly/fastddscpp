#pragma once

#include "DataPacket.h"
#include <memory>

template <typename T>
class DataPacketImpl : public DataPacket
{
public:
    DataPacketImpl()
    {
        m_data = new T();
    }

    DataPacketImpl(T *data)
    {
        m_data = data;
    }

    ~DataPacketImpl()
    {
        if (m_data) {
            delete m_data;
        }
    }

public:
    void *getData() override
    {
        return m_data;
    }

private:
    T *m_data;
};