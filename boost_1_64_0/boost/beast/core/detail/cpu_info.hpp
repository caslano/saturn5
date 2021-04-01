//
// Copyright (c) 2017 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_CPU_INFO_HPP
#define BOOST_BEAST_DETAIL_CPU_INFO_HPP

#include <boost/config.hpp>

#ifndef BOOST_BEAST_NO_INTRINSICS
# if defined(BOOST_MSVC) || ((defined(BOOST_GCC) || defined(BOOST_CLANG)) && defined(__SSE4_2__))
#  define BOOST_BEAST_NO_INTRINSICS 0
# else
#  define BOOST_BEAST_NO_INTRINSICS 1
# endif
#endif

#if ! BOOST_BEAST_NO_INTRINSICS

#ifdef BOOST_MSVC
#include <intrin.h> // __cpuid
#else
#include <cpuid.h>  // __get_cpuid
#endif

namespace boost {
namespace beast {
namespace detail {

/*  Portions from Boost,
    Copyright Andrey Semashev 2007 - 2015.
*/
template<class = void>
void
cpuid(
    std::uint32_t id,
    std::uint32_t& eax,
    std::uint32_t& ebx,
    std::uint32_t& ecx,
    std::uint32_t& edx)
{
#ifdef BOOST_MSVC
    int regs[4];
    __cpuid(regs, id);
    eax = regs[0];
    ebx = regs[1];
    ecx = regs[2];
    edx = regs[3];
#else
    __get_cpuid(id, &eax, &ebx, &ecx, &edx);
#endif
}

struct cpu_info
{
    bool sse42 = false;

    cpu_info();
};

inline
cpu_info::
cpu_info()
{
    constexpr std::uint32_t SSE42 = 1 << 20;

    std::uint32_t eax = 0;
    std::uint32_t ebx = 0;
    std::uint32_t ecx = 0;
    std::uint32_t edx = 0;

    cpuid(0, eax, ebx, ecx, edx);
    if(eax >= 1)
    {
        cpuid(1, eax, ebx, ecx, edx);
        sse42 = (ecx & SSE42) != 0;
    }
}

template<class = void>
cpu_info const&
get_cpu_info()
{
    static cpu_info const ci;
    return ci;
}

} // detail
} // beast
} // boost

#endif

#endif

/* cpu_info.hpp
MVnZkNEVo0XaCZ8xe7efHtwisq5kvry7EpN75vKZVjTN9L48oMQvp8wje+7WOSMY5Bes+bAZj92uk8YwEqTAS8Saqsh42n7/4aaLpxuNcxClyX38tR7EfE9yMeEa5/0UHmaXO+G+sV5saO7kwKxu2AaQ6bmr1tjHYmUlvAWE0Hq0HTm9mgQihHeiZ4ZInaiHuEe4YJhQp8AJSC7RuVkdcWydszLGmdIpdUdO28LdDePGU/eS9MUDplMSPIdetI9V0KBBwLc1CNZ9Nc2j5khL+MhHc478wA4KSyiOkhKu729t2sARaOFsqhMob+4DA30BgoOj2aZMx3PzqE1je8HGo/JhOHTlklNWh4qDRig6i/9tKt8PZdFiKOZKaaXeUDJAwXWtJoc3CwbzYml7OujhEgFbwxrm3/v6ys0+gQDz0/G9+V8t3Nq3Xp9Q3g5SK2QtPIItwtYfP7Ee9dENbXN0VkUnnGpylkwT8rMqVaKamzdg1c9GomStbBE2SPFSnTvlZbqnrm0qgQUBSfDWYYQXdA+b9EUQY5svTiiIzU5Lk33JE5PYwfw7guayDQ==
*/