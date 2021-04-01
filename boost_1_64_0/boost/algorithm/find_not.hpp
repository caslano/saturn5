/*
   Copyright (c) T. Zachary Laine 2018.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALGORITHM_FIND_NOT_HPP
#define BOOST_ALGORITHM_FIND_NOT_HPP

#include <utility>

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

template<typename InputIter, typename Sentinel, typename T>        
BOOST_CXX14_CONSTEXPR
InputIter find_not(InputIter first, Sentinel last, const T & x)
{
    for (; first != last; ++first) {
        if (*first != x)
            break;
    }
    return first;
}

template<typename Range, typename T>
BOOST_CXX14_CONSTEXPR
typename boost::range_iterator<Range>::type find_not(Range & r, const T & x)
{
    return ::boost::algorithm::find_not(boost::begin(r), boost::end(r), x);
}

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_FIND_NOT_HPP

/* find_not.hpp
bquEvqL6p/OpgAmm5i0U4C6zTp6ZFaHKorOnYSsiiZtQ4Zp2hiAK+5T03dfTOJareSY03bY4GvKtC/iavPzhYGcAq4lAgeZfCklS2GZOrJKmz/K562Oi9lei488P2zxeiuWLU8Hk08TdgB3aEq90F9i1xzLRe2GGUKPz6H4i/C2nrkepkIdEPHOU7qEFkxjPMBGDEErQlafTek6VmF9TjXw1hCIvvFrJyzsOINDvpGo26D+R3EKA0S3S/cNmj2cxGbk5nz81yJ0/I8T0xOYbDLVr/aJedevpvm8XaV75b42cY+Esv0SBdarTLOgqq1J51UKQt0B4Wh0+pJnynJ5fS9nEbwHvkJTCTPF/BQE2ytv4qH+A+fF7qvNhbrIIJ/nZJtzpvtMoxI3w4MAHO5yBZtljeSkE7itVcz7YEIVdogAn2CR5I88YTnp4msvzJjugYagF97vfSl/VsQIbXs53eHX2y17ZHX4j/xTT3Uwblhd5G7pO7nS4fO1hxQMHHy0jHIxA8+Iwg9YkuV2B8ryYlv+o5TCXEGkO2rm7uf9ENWtmBa2WaMfobYqqgA==
*/