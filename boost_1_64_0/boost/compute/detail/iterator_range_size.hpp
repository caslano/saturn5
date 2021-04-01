//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_ITERATOR_RANGE_SIZE_H
#define BOOST_COMPUTE_DETAIL_ITERATOR_RANGE_SIZE_H

#include <cstddef>
#include <algorithm>
#include <iterator>

namespace boost {
namespace compute {
namespace detail {

// This is a convenience function which returns the size of a range
// bounded by two iterators. This function has two differences from
// the std::distance() function: 1) the return type (size_t) is
// unsigned, and 2) the return value is always positive.
template<class Iterator>
inline size_t iterator_range_size(Iterator first, Iterator last)
{
    typedef typename
        std::iterator_traits<Iterator>::difference_type
        difference_type;

    difference_type difference = std::distance(first, last);

    return static_cast<size_t>(
        (std::max)(difference, static_cast<difference_type>(0))
    );
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_ITERATOR_RANGE_SIZE_H

/* iterator_range_size.hpp
6htegqIZOgchs49WOTboPPJliQ1y/O5qmOCXD2ppyGJSHH6iZ+nSngpgcYdHnPXO8RP/bcFQqyDKbVR60Qq2KZ7pGpPkpvaijEjNQH9NxnIdlOGyWY6xecePm+Y3CdN4QCdpwIgqc0cfmcFNu89frvK4LTkp+f/EF4PKv2iPfG9/xB7NTBrc46D8YCV4SaOy2kNhsYuE4dkc8re4+1LcRXqQof+ADY0gXpUPEllSkl7JLvtWjN86eLVKPtl7zJSs2QTLuS6GNtqAjsasmwyVfI6XAsso9bMpsi+XZk+KHw8QyQlBca7zBc3Ee0WT+kAk2maLRMF0AZ/r5cslBTySRSX4ytzMeSA71Ulro9IC4uhyHkJgXjlGmse/mMcLSiaSkUEoG55OQ1Mq7LJWR6+wesjz3bL+MctUH2ZYT6cAvH+uXGC3G7buj2LwkYftqcbww3SdSx4ERUEBpdx6cTQTDkOUBFgW/Oahhc8ATQMS+RY3MBvMyWNvCnbq+9KrcN2y0TcBb5mGZ0sPo/XLmOGWsQBNUJ4O2CYcTm7ckxmCb9eeNOiUABT4ehyILw==
*/