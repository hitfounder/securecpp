#include "encrypted_storage.h"
#include "json_storage.h"

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/flags/usage.h"

#include <iostream>

ABSL_FLAG(std::string, op, "", "Storage operation: read or write");
ABSL_FLAG(std::string, key, "", "Key of the secret");
ABSL_FLAG(std::string, value, "", "Value of the secret");

bool CheckOptions(std::string_view operation, std::string_view key, std::string_view value) {
    if (operation != "read" && operation != "write") {
        std::cerr << "Only 'read' and 'write' operations are supported" << std::endl;
        return false;
    }
    if (key.empty()) {
        std::cerr << "Please specify 'key' parameter" << std::endl;
        return false;
    }
    return true;
}

int main(int argc, char** argv) {
    absl::SetProgramUsageMessage("Secure storage demo application. Usage: \n\
        For writing secret: --op=write --key=key -- value=value \n\
        For reading secret: --op=read --key=key");
    absl::ParseCommandLine(argc, argv);

    std::unique_ptr<Storage> storage{std::make_unique<EncryptedStorage>(std::make_unique<JsonStorage>())};

    const auto& operation{absl::GetFlag(FLAGS_op)};
    const auto& key{absl::GetFlag(FLAGS_key)};
    const auto& value{absl::GetFlag(FLAGS_value)};

    if (!CheckOptions(operation, key, value)) {
        std::cout << absl::ProgramUsageMessage();
        return 1;
    }

    try
    {
        if (operation == "read") {
            std::cout << "Reading secret for a key '" << key << "': " << storage->Read(key) << std::endl;
        } else if (operation == "write") {
            storage->Write(key, value);
            std::cout << "Secret for a key '"<< key << "' has been written" << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}