#include "args.hpp"

#include <algorithm>
#include <array>
#include <cstddef>
#include <string_view>

namespace mycache {
namespace {

bool is_source_file(std::string_view arg) {
    constexpr std::array<std::string_view, 5> extensions{".c", ".cc", ".cpp", ".cxx", ".c++"};
    return std::ranges::any_of(extensions, [arg](std::string_view ext) { return arg.ends_with(ext); });
}

}  // namespace

bool is_cacheable_compile(std::span<const std::string> args) {
    bool has_compile_flag = false;
    std::size_t source_count = 0;

    for (std::size_t i = 0; i < args.size(); ++i) {
        const std::string& arg = args[i];
        if (arg == "-c") {
            has_compile_flag = true;
        } else if (arg == "-o") {
            ++i;  // The next argument is the output path, whatever its name.
        } else if (!arg.starts_with('-') && is_source_file(arg)) {
            ++source_count;
        }
    }

    return has_compile_flag && source_count == 1;
}

}  // namespace mycache
