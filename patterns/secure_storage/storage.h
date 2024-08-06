#pragma once

#include <string_view>

class Storage
{
public:
    virtual ~Storage() {}
    virtual void Write(std::string_view key, std::string_view value) = 0;
    virtual std::string_view Read(std::string_view key) const = 0;
};
