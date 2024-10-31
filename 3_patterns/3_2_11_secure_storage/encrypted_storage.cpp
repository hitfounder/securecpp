#include "encrypted_storage.h"

#include <absl/cleanup/cleanup.h>
#include <sha256.h>

#include <windows.h>

#include <stdexcept>

namespace
{
    inline DATA_BLOB ToDataBlob(const std::string& str) {
        DATA_BLOB blob;
        blob.pbData = const_cast<BYTE*>(reinterpret_cast<const BYTE*>(str.data()));
        blob.cbData = static_cast<DWORD>(str.length());
        return blob;
    }
    
    std::string Encrypt(const std::string& plaintext, const std::string& key) {
        DATA_BLOB input{ToDataBlob(plaintext)};
        DATA_BLOB entropy{ToDataBlob(key)};
        DATA_BLOB output;
        const BOOL result = ::CryptProtectData(
            /*pDataIn=*/&input,
            /*szDataDescr=*/
            L"This is the description string.",
            /*pOptionalEntropy=*/&entropy,
            /*pvReserved=*/nullptr,
            /*pPromptStruct=*/nullptr,
            /*dwFlags=*/CRYPTPROTECT_AUDIT,
            /*pDataOut=*/&output);

        if (!result) {
            throw std::runtime_error("Failed to encrypt");
        }

        const absl::Cleanup cleanup = [data=output.pbData] { LocalFree(data); };

        std::string ciphertext;
        ciphertext.assign(reinterpret_cast<std::string::value_type*>(output.pbData), output.cbData);
        return ciphertext;
    }

    std::string Decrypt(const std::string& ciphertext, const std::string& key) {
        DATA_BLOB input{ToDataBlob(ciphertext)};
        DATA_BLOB entropy{ToDataBlob(key)};
        DATA_BLOB output;
        const BOOL result = CryptUnprotectData(
            /*pDataIn=*/&input,
            /*szDataDescr=*/nullptr,
            /*pOptionalEntropy=*/&entropy,
            /*pvReserved=*/nullptr,
            /*pPromptStruct=*/nullptr,
            /*dwFlags=*/0,
            /*pDataOut=*/&output);

        if (!result) {
            throw std::runtime_error("Failed to decrypt");
        }

        const absl::Cleanup cleanup = [data=output.pbData] { LocalFree(data); };

        std::string plaintext;
        plaintext.assign(reinterpret_cast<char*>(output.pbData), output.cbData);
        return plaintext;
    }

    std::string Hash(const std::string& value) {
        static const char salt[] = {"my_super_salt"};
        SHA256 sha256;
        return sha256(value + salt);
    }
} // namespace

void EncryptedStorage::Write(const std::string& key, const std::string& value) {
    m_baseStorage->Write(Hash(key), Encrypt(value, key));
}

std::string EncryptedStorage::Read(const std::string& key) const {
    return Decrypt(m_baseStorage->Read(Hash(key)), key);
}
