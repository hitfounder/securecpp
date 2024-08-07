#pragma once

#include "storage.h"

#include <memory>

class EncryptedStorage : public Storage
{
public:
    explicit EncryptedStorage(std::unique_ptr<Storage> baseStorage)
        : m_baseStorage(std::move(baseStorage)) {}

    void Write(const std::string& key, const std::string& value) override;    
    std::string Read(const std::string& key) const override;

private:
    std::unique_ptr<Storage> m_baseStorage;
};
