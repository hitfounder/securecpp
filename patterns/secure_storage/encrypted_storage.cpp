#include "encrypted_storage.h"

#include <absl/cleanup/cleanup.h>

#include <windows.h>

#include <stdexcept>

namespace
{
    std::string Encrypt(const std::string& plaintext, const std::string& entropy) {
        DATA_BLOB input;
        input.pbData = const_cast<BYTE*>(reinterpret_cast<const BYTE*>(plaintext.data()));
        input.cbData = static_cast<DWORD>(plaintext.length());

        DATA_BLOB output;
        const BOOL result = ::CryptProtectData(
            /*pDataIn=*/&input,
            /*szDataDescr=*/
            L"This is the description string.",
            /*pOptionalEntropy=*/nullptr,
            /*pvReserved=*/nullptr,
            /*pPromptStruct=*/nullptr, /*dwFlags=*/CRYPTPROTECT_AUDIT,
            /*pDataOut=*/&output);

        if (!result) {
            throw std::runtime_error("Failed to encrypt");
        }

        const absl::Cleanup cleanup = [data=output.pbData] { LocalFree(data); };

        std::string ciphertext;
        ciphertext.assign(reinterpret_cast<std::string::value_type*>(output.pbData), output.cbData);
        return ciphertext;
    }

    std::string Decrypt(const std::string& ciphertext, const std::string& entropy) {
        DATA_BLOB input;
        input.pbData = const_cast<BYTE*>(reinterpret_cast<const BYTE*>(ciphertext.data()));
        input.cbData = static_cast<DWORD>(ciphertext.length());

        DATA_BLOB output;
        const BOOL result = CryptUnprotectData(&input, nullptr, nullptr, nullptr, nullptr, 0, &output);
        if (!result) {
            throw std::runtime_error("Failed to decrypt");
        }

        const absl::Cleanup cleanup = [data=output.pbData] { LocalFree(data); };

        std::string plaintext;
        plaintext.assign(reinterpret_cast<char*>(output.pbData), output.cbData);
        return plaintext;
    }

    std::string Hash(const std::string& value) {
        // TODO:
        return value;
    }
} // namespace

void EncryptedStorage::Write(const std::string& key, const std::string& value) {
    m_baseStorage->Write(Hash(key), Encrypt(value, key));
}

std::string EncryptedStorage::Read(const std::string& key) const {
    return Decrypt(m_baseStorage->Read(Hash(key)), key);
}
