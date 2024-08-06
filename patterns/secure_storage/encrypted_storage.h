#pragma once

#include "storage.h"

#include <memory>

class EncryptedStorage : public Storage
{
public:
    explicit EncryptedStorage(std::unique_ptr<Storage> baseStorage)
        : m_baseStorage(std::move(baseStorage)) {}

    void Write(std::string_view key, std::string_view value) override
    {
        // TODO:
        m_baseStorage->Write(key, value);
    }
    
    std::string_view Read(std::string_view key) const override
    {
        // TODO:
        return m_baseStorage->Read(key);
    }

private:
    std::unique_ptr<Storage> m_baseStorage;
};