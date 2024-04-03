#pragma once

#include "IDDSDataPacket.h"
#include <memory>

template <typename T>
class CDDSDataPacket : public IDDSDataPacket
{
public:
    CDDSDataPacket()
    {
        m_data = new T();
    }

    CDDSDataPacket(T *data)
    {
        m_data = data;
    }

    ~CDDSDataPacket()
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

    void *moveData() override
    {
        T *data = m_data;
        m_data = nullptr;
        return data;
    }

private:
    T *m_data;
};