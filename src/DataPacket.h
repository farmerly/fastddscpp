#pragma once

class DataPacket
{
public:
    DataPacket(){};
    virtual ~DataPacket(){};

public:
    virtual void *getData() = 0;
};