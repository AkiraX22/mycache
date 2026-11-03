#pragma once

#include <span>
#include <string>

namespace mycache {

// True if the compiler arguments (without the compiler name) describe a
// compilation this first version can cache: `-c` with exactly one source file.
// Anything else must be passed straight to the real compiler.
[[nodiscard]] bool is_cacheable_compile(std::span<const std::string> args);

}  // namespace mycache
