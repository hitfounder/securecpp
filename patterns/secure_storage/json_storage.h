#pragma once

#include "storage.h"

#include <unordered_map>

class JsonStorage : public Storage
{
public:
    JsonStorage();
    void Write(const std::string& key, const std::string& value) override;
    std::string Read(const std::string& key) const override;

private:
    void FromJson();
    void ToJson();

private:
    using KeyValueMap = std::unordered_map<std::string, std::string>;
    KeyValueMap m_data;
};
