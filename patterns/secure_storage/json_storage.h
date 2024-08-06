#pragma once

#include "storage.h"

class JsonStorage : public Storage
{
public:
    void Write(std::string_view key, std::string_view value) override
    {
        // TODO:
    }
    
    std::string_view Read(std::string_view key) const override
    {
        // TODO:
        return "";
    }
};
