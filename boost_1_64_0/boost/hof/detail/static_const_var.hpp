/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    static_const_var.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_STATIC_CONST_H
#define BOOST_HOF_GUARD_STATIC_CONST_H

#include <boost/hof/detail/intrinsics.hpp>

namespace boost { namespace hof { namespace detail {

template<class T>
struct static_const_storage
{
    static constexpr T value = T();
};

template<class T>
constexpr T static_const_storage<T>::value;

struct static_const_var_factory
{
    constexpr static_const_var_factory()
    {}

    template<class T>
    constexpr const T& operator=(const T&) const
    {
        static_assert(BOOST_HOF_IS_DEFAULT_CONSTRUCTIBLE(T), "Static const variable must be default constructible");
        return static_const_storage<T>::value;
    }
};
}

template<class T>
constexpr const T& static_const_var()
{
    return detail::static_const_storage<T>::value;
}


}} // namespace boost::hof

#if BOOST_HOF_HAS_RELAXED_CONSTEXPR || defined(_MSC_VER)
#define BOOST_HOF_STATIC_CONSTEXPR const constexpr
#else
#define BOOST_HOF_STATIC_CONSTEXPR static constexpr
#endif

#if defined(__GNUC__) && !defined (__clang__) && __GNUC__ == 4 && __GNUC_MINOR__ < 7
#define BOOST_HOF_STATIC_AUTO_REF extern __attribute__((weak)) constexpr auto
#else
#define BOOST_HOF_STATIC_AUTO_REF static constexpr auto&
#endif

// On gcc 4.6 use weak variables
#if defined(__GNUC__) && !defined (__clang__) && __GNUC__ == 4 && __GNUC_MINOR__ < 7
#define BOOST_HOF_STATIC_CONST_VAR(name) extern __attribute__((weak)) constexpr auto name
#else
#define BOOST_HOF_STATIC_CONST_VAR(name) static constexpr auto& name = boost::hof::detail::static_const_var_factory()
#endif

#define BOOST_HOF_DECLARE_STATIC_VAR(name, ...) BOOST_HOF_STATIC_CONST_VAR(name) = __VA_ARGS__{}

#endif

/* static_const_var.hpp
l0VH2Mv5Se9Yk7pp7Bbm11TN0q20GzmNNUvHN5JmqZ3d43m/yCEHoXApTf1jWmusCtMtneUUk3Zza/ia6NpKVUbS+ra6fYcZh/R7ZziVA3W9qJVSqZV+jmGaY0Y7yPOPeuR/1COfR5EHd2k7iYtV/c96Xh5HpHanmpqyOk6v5Zlv68xBeCk++pOW0F/CBNezkKVdny7FJWq8WduqT9zVt9bFy77MuD1LzH1rbwhejx2W3B3zj95Eyq9+9AknbWa4aTBVt8oyJf9+Zyj5O/Xk1+nJ30LJ99kV3aX1yrrlL1wF6XqX3vQcWm69Ft4tbuGBOyMi68pbagMgX6To1WcwvG8MhRnGYdiwBn0WpLcy7K3/SiFUGITqMeuPWj1eodfj7RW3OcVLO7VmjC6Hpp9Fe9HR9lSoXbPLXCH+YozvxaDqWOzGQ7rY/or63fyEVIVy+LtJ3Rz6bl6E6rWmkV0QyuiSP2gZHRn21dzuFJfuDOtvmtGSv77JnbuBWIP8FfhqFw73DCG7ORf6Ogs8Nl9npfeaOksVTjXRSrjOTE/301McPQXoyUpPi2jWbFrUuhJReCrJCHS5UxkfpgCV8kTUB/j2o1o+b9bzOZfyeRc4ZZL9wp6P7H2FGziPkRk/9YbMeF13JI9T+Un4qUVPHEfjuzNcH3xmqG5m6WneGtIHpzS7Np9Tc2vS41GaW0+t5/E9MjsVanYqTCHjv7pS+FWhHBz5vZaDypBSOOWg5iXOgajYEgy2LcDFCyyJNtOoKA3WhFTCM3SV8P7KHWEq4beL/pukSvhAiiQHu7ZY8rDV7pObSC48Z0Dg4yWFfYK1C4OwUVZjzhpVY+1DvgKbdorcjkqytZPqZxmbrnM8OLBF5c1//Hr7f6mW2fkDWXSiTU3YucQO0PybA9eT5YlJLuXRxl50J8cefYoNFzRc8zut0S4zR5zanOMUzS9yu8krIugPRyWg+O8Sd/EkZT//uVWzBwLN18db1PP/CxNVGwPqTSj3aw53ZdKNVEthqiwHX3AZFoA7INTGEZc973N+yNwrjJTNgH9ppOwV9QKTz3fVHU5nRfIjojsmcRb49cYxpvqgaqYgySV+voqTYiNXW89RaoTfcTAUfooM7+JKdsnwMPS6722qv1H8bpnSOmF5e/Cc9cWGAwNbHhy0KbDXtfPjrBNsHBHmQB21ZUHMm7G1N6CvX1tjvnZUTUlM7rH57Wzi0S3mvsr8j7xA/ZwG71rTUbvh78+/Hvme9afId9vbke8H34h8v3JL5PsdkfFR7mktaKZlIywbjostD8RAv7UcVfRhaRmNAYOerzDthB0hWNYvc0uZ4zIMWqTY6M0M9VnfKq3PfktfnC+s+AGOZLM0ju+OwxJUGReSMfzpNX0pFz5kDddjKg2JCCimV57XxPMUFe+LuUJZ4tCFilvfrBJZz+lTgJVjfvO3WswTIvN4Z0TM6E6fUy36vCE60ooYZR5tkjx3QJ6+GDgfb+HusdL9Ic29Kso9Trov1NwXR7mbpftUzb0myj1eul+nud8T5Z4g3Qdo7kuj3BOle3C/6r4syt0i3d/U3B+Icu+ill9zXx7l3lUtv+a+Isq9m1p+zf3hKHerWn7N/dEo9yS1/Jr7Y1Hu3dXya+6ro9xtavn3qe5/i3K3q+XX3Oui3Huo5dfc10e591TLr7nXR7n3UsuvuW+Ock9Wy6+5N0W5p6jl19y3R7n3VsuvuTdHufdRy/+a6r47yt2hll9z3xvl3lctv+Z+INxdu+/zGeddMCDCI627TJm3Qp0OFQft9aUgazZ7fB2ogaQWwh3lKw/iFx+0rYfZS57g3gQKvWbg9Zjtrvi9eC+3vWr25oDgt3oL8FM=
*/