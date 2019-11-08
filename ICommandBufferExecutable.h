#pragma once

class ICommandBufferExecutable
{
public:
    virtual void Execute() = 0;
};