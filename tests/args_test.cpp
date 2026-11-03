#include "args.hpp"

#include <gtest/gtest.h>

#include <string>
#include <vector>

using Args = std::vector<std::string>;

TEST(IsCacheableCompile, AcceptsSingleSourceCompile) {
    EXPECT_TRUE(mycache::is_cacheable_compile(Args{"-c", "main.cpp", "-o", "main.o"}));
    EXPECT_TRUE(mycache::is_cacheable_compile(Args{"-O2", "-Wall", "-c", "a/b.cc"}));
}

TEST(IsCacheableCompile, RejectsLinkStep) {
    EXPECT_FALSE(mycache::is_cacheable_compile(Args{"main.cpp", "-o", "app"}));
    EXPECT_FALSE(mycache::is_cacheable_compile(Args{"main.o", "-o", "app"}));
}

TEST(IsCacheableCompile, RejectsMultipleSources) {
    EXPECT_FALSE(mycache::is_cacheable_compile(Args{"-c", "a.cpp", "b.cpp"}));
}

TEST(IsCacheableCompile, IgnoresOutputPathWhenCountingSources) {
    EXPECT_FALSE(mycache::is_cacheable_compile(Args{"-c", "-o", "out.cpp"}));
}
