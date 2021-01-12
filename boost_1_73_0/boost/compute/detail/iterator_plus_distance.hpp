//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_ITERATOR_PLUS_DISTANCE_HPP
#define BOOST_COMPUTE_DETAIL_ITERATOR_PLUS_DISTANCE_HPP

#include <iterator>

namespace boost {
namespace compute {
namespace detail {

template<class Iterator, class Distance, class Tag>
inline Iterator iterator_plus_distance(Iterator i, Distance n, Tag)
{
    while(n--){ i++; }

    return i;
}

template<class Iterator, class Distance>
inline Iterator iterator_plus_distance(Iterator i,
                                       Distance n,
                                       std::random_access_iterator_tag)
{
    typedef typename
        std::iterator_traits<Iterator>::difference_type difference_type;

    return i + static_cast<difference_type>(n);
}

// similar to std::advance() except returns the advanced iterator and
// also works with iterators that don't define difference_type
template<class Iterator, class Distance>
inline Iterator iterator_plus_distance(Iterator i, Distance n)
{
    typedef typename std::iterator_traits<Iterator>::iterator_category tag;

    return iterator_plus_distance(i, n, tag());
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_ITERATOR_PLUS_DISTANCE_HPP

/* iterator_plus_distance.hpp
ry/U62XwZrgS3gKvg7fCB+Ftrt7gdngQ3u7qyRvU92vwDldPcAc8Cu+EX8O7YFMf9RTsBO+Bp8JfwGHwXkidJP6Mhw/AqfCXsAI+5OoN7oY/82n+wsfgLvhbN9/gfvik3n8O9oJvwEHwSzgY/h2Ohh39QXvd4Cg3fH/QfKyaT4Lj4Qx4uhsPOAEuhFPgEjgVLoNnwA3q7mY4Hd4Nz4J74dlwP8xx4wVnuvmo9l+BufBzNf9K
*/