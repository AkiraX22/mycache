#include <iostream>
#include <span>
#include <string_view>

int main(int argc, char* argv[]) {
    const std::span args(argv, static_cast<std::size_t>(argc));

    if (args.size() == 2 && std::string_view(args[1]) == "--version") {
        std::cout << "mycache " << MYCACHE_VERSION << '\n';
        return 0;
    }

    // The compiler wrapper arrives in step 2.
    std::cerr << "usage: mycache --version\n";
    return 2;
}
