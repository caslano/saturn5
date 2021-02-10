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
OQ1jTLNmbfi0CndWUCnvunz6oNGNF8whzOGT/nQ2GdJv4eWsH0xkMOL5b/sqQUYkulNprf2LMhYiz/vz0a90cHLIGdKoLz9o3YPg0O4yPuqFAn8/vhU4f3jM5l8hXnfM5QJ9u3es49qUVxPtsIcDbymnGPhDL0/kh5h/7D4q3bBng0Zif34VXp6PJlf9s/lgOJ5NWe0BRlz3cvBvvRfPeyeHbubZf81QNtHxc2MXDWf7RsCNia4x9v8ZXo0v+0EvWwa0E8sy/qn5Lu9j6Of2Tc3BIT8q451bEhZ+a7N/wu1Sp3mNqD9iusGoiL7S6dKJiDDLgz+V8SH9R17MuHc1Lvk/yZ3jx/4NBQeHD20ZU4D48fhYVnzTCFe4sGNZFa3e/+Kv3RRjMM7qgjfiYfPaJ/wtHFyGbweXXK1hE3GhS4T9ae+k99nxRDjvQXJcjDtRv0/hZTTqBL23k89UUweIgontg89uzHlk9jf3RSTb7cH/AFBLAwQKAAAACAAtZ0pSsAb4NRgDAACFBgAAJwAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9jdXJsX3ZlcnNpb24uM1VUBQABtkgkYK1U0W7bOBB811fMqS92ochpg6LtXVDUTXyN0MQ2LOcCAwYEWqIi3lGkQFJJ
*/