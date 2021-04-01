#ifndef BOOST_ARCHIVE_WCSLEN_HPP
#define BOOST_ARCHIVE_WCSLEN_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// wcslen.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <cstddef> // size_t
#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
} // namespace std
#endif

#ifndef BOOST_NO_CWCHAR

// a couple of libraries which include wchar_t don't include
// wcslen

#if defined(BOOST_DINKUMWARE_STDLIB) && BOOST_DINKUMWARE_STDLIB < 306 \
|| defined(__LIBCOMO__)

namespace std {
inline std::size_t wcslen(const wchar_t * ws)
{
    const wchar_t * eows = ws;
    while(* eows != 0)
        ++eows;
    return eows - ws;
}
} // namespace std

#else

#ifndef BOOST_NO_CWCHAR
#include <cwchar>
#endif
#ifdef BOOST_NO_STDC_NAMESPACE
namespace std{ using ::wcslen; }
#endif

#endif // wcslen

#endif //BOOST_NO_CWCHAR

#endif //BOOST_ARCHIVE_WCSLEN_HPP

/* wcslen.hpp
ozR0nK7trUe8Ax2DcMyY4ZXHWYV5XU4d0R7KO8orcYqpHkIh84Kv3X4LciY/eKm45zYNFZNuL4E0fPC+OryhCb8o3PrIC3SFyOKr9MC8BuQXnjoPnACXYEeIpGRYsl8qoxOKspEPqzBY/mA4iJ/G77axZPuqvfpe+N4SKc7224dIHp3uTx3s5SXNDAClsXQ21OCBPiInF2+nD0jFrgMK0xDdzNISly8ojMV5f09sTMi7FRdVtnRW/69X2Q+gVdbu7QwCxmZHZgdhU85cgyKw260DLDTlMxtPz2fMaiHuJzyRdH5XaH+sGm4qdiiWLP1sbbdn0F00vpfd7BTzY3qRu/p2Kdy2ZVktRj3qyI12t3D7te0y1+xQQY0l5eIr6wAgEiUASjyTZ6VgAzI0H+x1w+AA7diYAgnoHm38pTOpPllWBlRPFs/S2dGbpJ+PyMBodDwezdOGr3ZI+GczFlSfoIBnkYrw0uAuJ2Pwp7Xnk5aKzZxStPrfZKON1Y6vF3pBaPLCEcdYy7dvyiaJpoOfrxxzTYRxiyLB1riU2uedsmcuLXag9TW1xJCoww==
*/