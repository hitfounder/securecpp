#pragma once

#include "storage.h"

#include <unordered_map>

class JsonStorage : public Storage
{
public:
    JsonStorage();
    void Write(std::string_view key, std::string_view value) override;
    std::string_view Read(std::string_view key) const override;

private:
    void FromJson();
    void ToJson();

private:
    using KeyValueMap = std::unordered_map<std::string, std::string>;
    KeyValueMap m_data;
};
