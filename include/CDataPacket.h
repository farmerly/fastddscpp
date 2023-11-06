#pragma once

#include "IDataPacket.h"
#include <memory>

template <typename T>
class CDataPacket : public IDataPacket
{
public:
    CDataPacket()
    {
        m_data = new T();
    }

    CDataPacket(T *data)
    {
        m_data = data;
    }

    ~CDataPacket()
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