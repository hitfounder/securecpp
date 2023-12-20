#include <filesystem>
#include <fstream>

void CheckAndCreate(const std::filesystem::path& p) {
    if (!std::filesystem::exists(p)) {
        std::fstream f(p.string(), std::ios_base::in | std::ios_base::out);
        f << "data" << std::endl;
    }
}

void CheckAndCreateNoRace(const std::filesystem::path& p) {
#if __cpp_lib_ios_noreplace >= 202207L
    std::fstream f(p.string(), std::ios_base::in | std::ios_base::out | std::ios_base::noreplace);
    f << "data" << std::endl;
#else
    struct FileCloser {
        void operator()(std::FILE* fp) const { std::fclose(fp); }
    };
    std::unique_ptr<std::FILE, FileCloser> fp(std::fopen(p.string().c_str(), "wx"));
    if (!fp) {
        throw std::runtime_error("Could not open file in exclusive mode");
    }
    std::string_view str{"data"};
    std::fwrite(str.data(), 1, str.size(), fp.get());
#endif
}

int main() {
    CheckAndCreate("/tmp/file");
    std::filesystem::remove("/tmp/file");

    CheckAndCreateNoRace("/tmp/file");
    std::filesystem::remove("/tmp/file");
    return 0;
}