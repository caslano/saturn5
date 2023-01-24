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
OE+TWWqTNEU8MO2MNnXMmBaeXqZM+9XELKHmd136K4hJjo84sHGnHOnpysodNr+f6E2cIUr2ZhZCLlmpCwXxEPy6ZoWxQMd/KA1VN8mQc0ET257i80oGkgA3PN+LCGVNiOdp4vHzNdG7ZD4f5Cnnh5wmsyG/9AJ53gU18f70C4C8SB0BUYw8kwBA220w7bmwujPwubD6MvXt8Iy799mzzlDnI2/y+YDksmHV7Wc07aqKXdO0ssPc0QtrX8DI+mnABbE2Z6Ak1iTGdAq6VoX1C+OzYaXP8lZYWbsRweKUsq0KU+3t1b1MtHOQUjUsV+Y5ifVN0Xnm2u5KCWOUaeepdtXZq41SSjbc0qGxwietYbYouahDyVMZqZYdi3eI8vvbyQcbnVz5NDTV3oEikdTu66Qw5dKk8GQ9kF1TxZOndqjXMBHnBed/or0TlwXWY5HqZyIfYWSh4BPPhEH7uYhApqJ3sedU5h8rw33o+XMv3DuX+uSF8/fJlGnnZWDMmhYcx1qkMZW9MgxJ3W/pGlsK/j/sfQtATdn3/0EIoQh5h5CRhJDn9NQtvRBCKBVFpUkIISqiIoSYEEKIyWukCRkNeU6eE2JifEeZxoSYPPufs/fn3HvPcW/3NmMev/k7M/nsvc5+rL322o+1zj7nVuwgYe7NxuKGculnrJBxO2WFPLduhNtNnO6QrnZRwe3WEUq5dVO8Lqrc5kiKUhur
*/