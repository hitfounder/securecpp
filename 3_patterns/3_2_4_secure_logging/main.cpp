#include "absl/strings/escaping.h"
#include "absl/strings/str_replace.h"

#include "spdlog/pattern_formatter.h"
#include "spdlog/spdlog.h"

class sanitazing_log_formatter : public spdlog::custom_flag_formatter {
public:
    void format(const spdlog::details::log_msg &msg,
                const std::tm &,
                spdlog::memory_buf_t &dest) override {
        std::string sanitized{
            absl::CEscape(std::string_view(msg.payload.data(), msg.payload.size()))
        };
        absl::StrReplaceAll({
            {"&",  "&amp;"},
            {"<",  "&lt;"},
            {">",  "&gt;"},
            {"\"", "&quot;"},
            {"'",  "&apos;"}}, &sanitized);
        dest.append(sanitized.data(), sanitized.data() + sanitized.size());
    }

    std::unique_ptr<custom_flag_formatter> clone() const override {
        return spdlog::details::make_unique<sanitazing_log_formatter>();
    }
};

int main() {
    const std::string vulnLog{"Test\b\b\t\013\014<script>alert(\"Hello, world!\");</script>"};

    spdlog::set_formatter(std::make_unique<spdlog::pattern_formatter>("[%c] [%l] %v"));
    // Fake entry
    spdlog::info("Text\n[Mon Apr 15 18:22:59 2024] [info] Fake log entry");
    // XSS atack
    spdlog::info("<script>alert(\"Hello, world!\");</script>");
    // Remove log entry
    spdlog::info("Some usefull text \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b                             ");

    auto formatter = std::make_unique<spdlog::pattern_formatter>();
    formatter->add_flag<sanitazing_log_formatter>('v').set_pattern("[%c] [%^%l%$] %v");
    spdlog::set_formatter(std::move(formatter));
    spdlog::info(vulnLog);
    return 0;
}