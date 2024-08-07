#include "json_storage.h"

#include <absl/strings/escaping.h>
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
    std::ofstream(JsonFilePath) << j.dump();
}

void JsonStorage::Write(const std::string& key, const std::string& value) {
    m_data[absl::Base64Escape(key)] = absl::Base64Escape(value);
    ToJson();
}

std::string JsonStorage::Read(const std::string& key) const {
    const auto found{m_data.find(absl::Base64Escape(key))};
    if (found == std::end(m_data)) {
        throw std::runtime_error("No data with key '" + key + "'");
    }
    std::string result;
    if (!absl::Base64Unescape(found->second, &result)) {
        throw std::runtime_error("Corrupted data");
    }
    return result;
}
