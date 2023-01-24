
// Copyright 2005-2009 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  Based on Peter Dimov's proposal
//  http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2005/n1756.pdf
//  issue 6.18. 

#if !defined(BOOST_FUNCTIONAL_HASH_FWD_HPP)
#define BOOST_FUNCTIONAL_HASH_FWD_HPP

#include <boost/config/workaround.hpp>
#include <cstddef>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#pragma once
#endif


namespace boost
{
    template <class T> struct hash;

    template <class T> void hash_combine(std::size_t& seed, T const& v);

    template <class It> std::size_t hash_range(It, It);
    template <class It> void hash_range(std::size_t&, It, It);

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x551))
    template <class T> inline std::size_t hash_range(T*, T*);
    template <class T> inline void hash_range(std::size_t&, T*, T*);
#endif
}

#endif

/* hash_fwd.hpp
999ZCcwNB2VBCdSIQIEEy++cih2CogtQOWwawl9h/GJNrtX/14I1UwxqztdvJcy09lND9jVwQZqP2QhzDb+Zk+T4/kX/Pv5Wi+5J83IsfZb5OgBrJTQDLaecObVMlqX4vUlz2sUIQFmWB5rrxIKoZ375l3/5lnPCbrVqBNBcj6AAvmfCPxgM1N7engwGg7k73uv11N7enly9ekU+8vf/0R1Xrh3/u0srS3eNJls8u/pPGB7/Bp0sRyeabq9DL89Ce3jvGQ8tUg6Z6hFCyLnOtCYvNEUaBltGLhqlFD2V0DEwtRrUCQZ+xKY8w0q+xGr3KKnuYb1GqSUynZPoFG0UWpnIi4QQallpHFPW8yEPdAd8fW+IHXQQo1Be4fExyKhC6q7UeRcaFcOsYV9pfOWQsUWGFUxcNHQq5uCoSIwrtBJcnROgwvPWOoxO0dUmJKFsWJV9phcGDJbH9O9/jjy9gfeakYSJPEXiGZgOIzuC7dvYH+bcdcqyrHOyn7mKf/ICj1e3UV62NH5/7VfPKQFosugOEIOzl5XyAf7bWWMQax02DgkxWoWZowtmevb37MSqboaqoA79zZqE6EPeOztHA+fbvEA7gWiOWDzMHWg9dziCD81dGxIwNAL1bszKcrC7h0UAwlSpg8NA6uxA4OOHX+2VV40A6jPW+OmgyvsrWnt7e5w4cWLu2hsbGwrg4sWL/kO/+uvdm9eP/GqW
*/