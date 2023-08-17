#pragma once

class IDataPacket
{
public:
    IDataPacket() = default;
    virtual ~IDataPacket() = default;

public:
    virtual void *getData() = 0;
};