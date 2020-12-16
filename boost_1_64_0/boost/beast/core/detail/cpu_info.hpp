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
DVaxzrqu989EjLJ4ajF30sf5HNNt2iM8H8e7u8donyV6zfk5Ej6BbpwWJ+44ZdWVgr5oAzH+58/FwXWWPM0xbCfRFwS1EflWyLpRndj5t0Kr/JEGW/nndFD+M3SY6FOXo7nWfxHnFuaA9qBetIwyylEsmOru2RhXse6wH/uRyExSI3Q78MeTGKpMGZ6ky+KguKdgxBSprH4hCfXsEKhR2uK4uMgB1CvDsuL87TRddaWd/mSUvZ2+Lu5+EmdXbVHdq9tNaP3Opn6fo62+tbh3CnAFsAxtKT7TRb8wzOoruM6fgT75ifb5rSrqVYeP1nbspol7psc2z+XVz0DyZ+h+fqq4Z3sSwI+2j/9W4tZtqi4N2OCbLDxTPZwrYxxpypJZKzJ4T6BMwO4e+Qw73oF7SH8hAtp2t4MfOnC2dT2/kid8UzxB41X2FzMkPMdja+PsJ74sYQ8oecagThX0V+qUtOklul4Vsr36eerB847FEzlH87xFnkTy7PLHE9b4o7joFGdcmu8A+N4V2+FbJ8RF9dV8GwbZ73m0v78f2TrKrO+OMaWMJYvigaQSeeZ0brfS6lsKRtv7loIO+pZCcy6zSp9lHJjL9KIu0/Y3yhh+uh7p84zXij/rCv0bNL+uE7Z+K26QkuunHFd+GfhFtMu20Wa7wr268Z7qk80NMa5kuDGufF/cu0KNK8k/Xrepd8V9v+u48poxcgY9vn8v1O+G94rfa/C5JeTYctBYaecytgw1Rjxf4gnXfcFscdeGHB9GSfjObo8PrXb0AfNo1eu2Aaj/A/3jwxVx0YNcxofkax0YenyYTJ7CBP+YbrRtTHdAOmc9ppvulPfzrEzQY7qJXXlWnBpjf1YMEV0P0GM67md2vMN1fzz3YY7fcseGGL8NUXK9AEoiPon44rPM9lNne+476zn1RJlMlcg6kCvux9VM3O9mUIhnP+XwzsM2MEXcT6i51rcF5WGd595Pab987gjf1xF/LOLXticYX5r5XUaPFW+UsFLMA8VLHx+PBOQi4GqpD2OC+2/yrBns/15RGhcV7VJ/ydcIvhvkG8I1zj5e8+wBz3sZVh1tvM3Zv3MMyP66836a7+FBdSDfHIvQr0DXH9Gjbf3FPtaDkaB+rAtfwP3Tx0k9oDWAotK1LP/Py15cqzuuY/mTFzEwT6j/Xd+Hi/iQLolP0nUh62d+opKrmmm6DLQXIQVMl3x+LfInr6SqyvjAifxLGbcMgSzi+ael8wE5On2rWS4+N8IHdT7mNtcpPMG0TaHOskHnWe8+vrQ5PrYqvRbgOpT/6UGd25qV8SPvlT9UyTWN98qhHtLH814uH3bBInbx9yOdmZD/APmP7Qfb9mFxAyKVIz2sf52Vl1lnkoYFr9lZCmEv0yQHcpTRhoTjGy/rDHn1mh3Xb7WLHXzxUq7SJ5CvKPC8dfCizrj2O5UOPpS5cwwt/lnKNmaljEc5x898JtrGq+Tt8jok53e4ePt3OBkPJek2zHyTN92lvWe5jMlyHGMyszyPJuvzK/R1ISJpNMpTXuVt+vdiWqS63ihT8ocbZUpejllYpgE+lmmo8RP5Oi1P8nWrPBu7UZ6NXSzPRJYnv5dSPyxTl++oSYH++6yW5/4U9/JsMspTDgHppDybulieTV0sz6YulmfTGZRnUzfKs+l/rDwPjlBy3Q0awL2st1tngfjK0/p4UFJdJpOCnb7j+GQS9Debr/riwPoOT/D7AL9/hU8Aj2FrYuMQpSo41k1WK0TfD61VULZtflLXozfkHjGdjmmSOaZxGwebz8QZqUquRFA/0p1Id7Gks7FuQ9HCwqL5c5csmTd3/mJ5B6zeVFWlbGO80M+7dD6DA+tvD7s=
*/