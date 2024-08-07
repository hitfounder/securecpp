#pragma once

#include <string>

class Storage
{
public:
    virtual ~Storage() {}
    virtual void Write(const std::string& key, const std::string& value) = 0;
    virtual std::string Read(const std::string& key) const = 0;
};
