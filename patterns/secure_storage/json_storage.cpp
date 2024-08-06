#include "json_storage.h"

#include <nlohmann/json.hpp>

#include <filesystem>
#include <fstream>

using json = nlohmann::json;

namespace
{
    const std::filesystem::path JsonFilePath{std::filesystem::temp_directory_path() / "data.json"};
    const char DataSectionName[] = {"data"};
}

JsonStorage::JsonStorage() {
    FromJson();
}

void JsonStorage::FromJson() {
    std::ifstream f{JsonFilePath};
    const json j = json::parse(f, nullptr, false);
    if (!j.is_discarded()) {
        m_data = j.at(DataSectionName);
    }
}

void JsonStorage::ToJson() {
    json j;
    j[DataSectionName] = m_data;
    std::ofstream f{JsonFilePath};
    f << j.dump();
}

void JsonStorage::Write(std::string_view key, std::string_view value) {
    m_data[std::string(key)] = std::string(value);
    ToJson();
}

std::string_view JsonStorage::Read(std::string_view key) const {
    const auto found{m_data.find(std::string(key))};
    if (found == std::end(m_data)) {
        throw std::runtime_error("No data with key '" + std::string(key) + "'");
    }
    return found->second;
}
