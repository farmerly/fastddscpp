#pragma once

class IDDSDataPacket
{
public:
    IDDSDataPacket() = default;
    virtual ~IDDSDataPacket() = default;

public:
    // 在调用回调函数后，IDDSDataPacket 会释放，需要保留数据要使用 moveData
    virtual void *getData() = 0;
    // 获取数据地址，函数执行完成后 IDDSDataPacket 的数据会指向空指针
    virtual void *moveData() = 0;
};