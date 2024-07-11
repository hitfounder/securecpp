#pragma once

class Policy
{
public:
    virtual ~Policy() {}
    virtual void Apply() = 0; 
};