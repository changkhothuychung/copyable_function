// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <beman/copyable_function/copyable_function.hpp>
#include "common.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <functional>
#include <iostream>
#include <type_traits>

TEST(CallTest, CallTestWithLambdaWithoutCVRef) {
    beman::copyable_function<int()> f(Callable{});
    int                             x = f();
    EXPECT_EQ(x, 42);
}

TEST(CallTest, CallTestWithLambdaWithConst) {
    beman::copyable_function<int() const> f(Callable{});
    int                                   x = f();
    EXPECT_EQ(x, 43);
}

TEST(CallTest, CallTestWithLambdaWithNoexcept) {
    beman::copyable_function<int() const noexcept(true)> f(Callable{});
    int                                                  x = f();
    EXPECT_EQ(x, 43);
}

TEST(CallTest, CallTestUsingLvalueReference) {
    beman::copyable_function<int() const>  f(Callable{});
    beman::copyable_function<int() const>& f2 = f;
    int                                    x  = f2();
    EXPECT_EQ(x, 43);
}

TEST(CallTest, CallTestUsingRvalueReference) {
    beman::copyable_function<int()>&& f2 = []() { return 42; };
    int                               x  = f2();
    EXPECT_EQ(x, 42);
}

TEST(CallTest, CallTestWithConstLvalueRef) {
    beman::copyable_function<int() const&> f(Callable{});
    int                                    x = f();
    EXPECT_EQ(x, 43);
}

TEST(CallTest, CallTestWithConstRvalueRef) {
    beman::copyable_function<int() &&> f(Callable{});
    int                                x = std::move(f)();
    EXPECT_EQ(x, 42);
}
