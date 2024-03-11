#pragma once

#include <optional>

template <typename T>
class SingleUse {
public:
    explicit SingleUse(const T& data)
        : m_data(data) {}

    SingleUse(const SingleUse&) = delete;
    SingleUse& operator=(const SingleUse&) = delete;

    SingleUse(SingleUse&&) = default;
    SingleUse& operator=(SingleUse&&) = default;

    T extract() {
        if (m_data.has_value()) {
            OptionalData data;
            std::swap(m_data, data);
            return data.value();
        }
        throw std::runtime_error("Value already used");
    }
    
private:
    using OptionalData = std::optional<T>;

    OptionalData m_data;
};