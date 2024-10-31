#include <filesystem>
#include <gtest/gtest.h>
#include <iostream>

void CheckAndRemove(const std::filesystem::path& p) {
    std::cout << "Path is: " <<  p << std::endl;
    if (p.parent_path().string().starts_with("/etc")) {
        throw std::runtime_error("Etc file");
    }
    std::filesystem::remove(p);
}

void CanonizeCheckAndRemove(const std::filesystem::path& p) {
    auto canonicalPath{std::filesystem::canonical(p)};
    std::cout << "Canonical path is: " <<  canonicalPath << std::endl;
    if (canonicalPath.parent_path().string().starts_with("/etc")) {
        throw std::runtime_error("Etc file");
    }
    std::filesystem::remove(p);
}

int main() {
    std::filesystem::current_path("/tmp");
    std::filesystem::create_symlink("/etc/passwd", "/tmp/file");

    EXPECT_THROW(CheckAndRemove("/etc/passwd"), std::runtime_error);
    EXPECT_THROW(CheckAndRemove("../etc/passwd"), std::filesystem::filesystem_error);
    EXPECT_THROW(CheckAndRemove("/./etc/passwd"), std::filesystem::filesystem_error);

    EXPECT_THROW(CanonizeCheckAndRemove("/etc/passwd"), std::runtime_error);
    EXPECT_THROW(CanonizeCheckAndRemove("../etc/passwd"), std::runtime_error);
    EXPECT_THROW(CanonizeCheckAndRemove("/./etc/passwd"), std::runtime_error);
    EXPECT_THROW(CanonizeCheckAndRemove("/tmp/file"), std::runtime_error);
    
    std::filesystem::remove("/tmp/file");
    return 0;
}