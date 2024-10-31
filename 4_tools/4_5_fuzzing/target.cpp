#include <cstdint>

#include <nlohmann/json.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, std::size_t Size) {
    nlohmann::json::parse(Data, Data + Size,
        nullptr /*parse_callback*/, false /*allow exceptions*/);
    return 0;
}
