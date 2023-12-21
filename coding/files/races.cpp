#include <filesystem>
#include <fstream>
#include <llfio/llfio.hpp>

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

void CheckAndUse(const std::filesystem::path& p) {
    if (std::filesystem::is_regular_file(p)) {
        std::fstream f(p.string(), std::ios_base::in | std::ios_base::out);
        std::string data;
        f >> data;
        std::cout << data << std::endl;
    }
}

void CheckAndUseNoRace(const std::filesystem::path& p) {
    namespace llfio = LLFIO_V2_NAMESPACE;

    llfio::file_handle fh = llfio::file(
        {},        // path_handle to base directory
        p.string() // path_view to path fragment relative to base directory
                   // default mode is read only
                   // default creation is open existing
                   // default caching is all
                   // default flags is none
        ).value(); // If failed, throw a filesystem_error exception

    llfio::stat_t fhstat;
        fhstat.fill(
            fh      // file handle from which to fill stat_t
                    // default stat_t::want is all
        ).value();
    
    if (fhstat.st_type == std::filesystem::file_type::regular) {
        std::vector<llfio::byte> buffer(fh.maximum_extent().value());
        // Synchronous scatter read from file
        llfio::file_handle::size_type bytesread = llfio::read(
            fh,                                 // handle to read from
            0,                                  // offset
            {{ buffer.data(), buffer.size() }}  // Single scatter buffer of the vector 
                                                // default deadline is infinite
        ).value();                              // If failed, throw a filesystem_error exception
        buffer.resize(bytesread);
        for (const auto& c: buffer)
            std::cout << static_cast<char>(c);
    }
}

int main(int argc, char** argv) {
    CheckAndCreate("/tmp/file");
    std::filesystem::remove("/tmp/file");

    CheckAndCreateNoRace("/tmp/file");
    std::filesystem::remove("/tmp/file");

    const std::string fileToUse{argc > 1 ? argv[1] : ""};
    CheckAndUse(fileToUse);
    CheckAndUseNoRace(fileToUse);
    return 0;
}