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
Z/LfZ8+uQnl29eFNFIYN+Kjv7F73qzGY+dTFdnI9YTi/v/OT78d1Sfl1azcdLYUJYycfG0xVV8tYlc0bMnV2n/gbyOT758/HxPe2yAxPKGUFh1Pp2GwV93fgJLSrGOhJjzDmPoG7N5qQC+qk4+paEwQzRGqdqdP/KAV1xtR1F+VcinjTeKPx1bG9Zcx5RveBsAma0FF192SO2utoFPwBUEsDBAoAAAAIAC1nSlL57XEpyQMAAJQHAAAZAAkAY3VybC1tYXN0ZXIvZG9jcy9IWVBFUi5tZFVUBQABtkgkYJVVbWscNxD+vr9ialNqG+8dcaC0oS64rVMb0mKcCxRCCTrt7O3UWknVy738+85Iuxe7BEqPY08rzcszj+aZO4W7g8fQNOUHKIKCiF4FlRDuVqsHMLQOKhxgFygltEAWHnNMC9A5GNDKwhohOdPxA3Lk9UCxmb2UBFwr/YS2GHSoDOwoDSX4omlOT+F2z6lpRJuU+WpGErP3LiRJVxIxMu1spA4DdnBxcfvHw+3j/W+3v69u3l1cQLaJDPQ5pIGdrUukcQH3qbGIXZTMjBL33pCmZA6AVq0NB1IJ1plM1yYGwHDeThE63KJxXkCBEug7VE9kN+B6LhAra8fC/g12R8Y0g/K+8sVf8RlVTOIU
*/