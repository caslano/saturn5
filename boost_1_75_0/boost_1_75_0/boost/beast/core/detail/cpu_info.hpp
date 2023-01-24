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
sxgnHrb5hasF7wfTBSDhSLhpe4w6dHItL0djNPrXWiNr4TFqEH5mM7Co60c5445zs3ZmLpLiUkRGMc1SRmlEXEVcRkb2+KTV0FGE1JFhZUZw2WunZlXnctQRu07XRofa3eLLOe54n4gz0FNi6fd57O9zetCKiVGE/6Y9vW6WScLrL6v7tQKedQOBkyNddyblGh21XxQnWYqvsB6Kr6+w34IAH+joY1EqrohqZ149XmfHR8Q2Tz2NkKOVIPeKkvcPoMklbyco0GWigOOmO+hBsvF9PPtzxLlAyOt1/64kU7nFRMT/h9fOHrbnYefTBajGuN31+DHTxCXwqFShLQDNm+w0qKLqD75QzbbtBb9X1bvlSBHySYeKMf+Wv/1M3zK5N1mr71Hp57cZ45fd9AYnIxbSgM+hagYcyH2UDMT98KOOw8kIJML/7D1RwEfrERSie/skE6V7WXYEXVEYLy9pZNIZw/yPYeyzi1388uGOthGfKDuKcfm0we16RPVU5shfEExjn258AIjjWzS/EeVonnNy82uxXLdvVNITdolQjRF45ku4qe/5CAB+v8txGoFsmjYqTk2NK+hVWgOhRHg6i45P+cZQK9h1jOu4d2sOqFqhdLh4ibs2rw/YieyrBfpQUiOMlaQimDd7HIcu13LhrgIr1e0OUwhwrF4v107PyiENAWep9P2caa1w954ySd7XKvdOTkY1W4Kv17ky
*/