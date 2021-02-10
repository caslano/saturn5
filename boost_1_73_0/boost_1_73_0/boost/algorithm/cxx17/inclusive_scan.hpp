/*
   Copyright (c) Marshall Clow 2017.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  transform_reduce.hpp
/// \brief Combine the (transformed) elements of a sequence (or two) into a single value.
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_TRANSFORM_REDUCE_HPP
#define BOOST_ALGORITHM_TRANSFORM_REDUCE_HPP

#include <functional>     // for std::plus
#include <iterator>       // for std::iterator_traits

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

namespace boost { namespace algorithm {

template<class InputIterator, class OutputIterator, class T, class BinaryOperation>
OutputIterator inclusive_scan(InputIterator first, InputIterator last,
                              OutputIterator result, BinaryOperation bOp, T init)
{
    for (; first != last; ++first, (void) ++result) {
        init = bOp(init, *first);
        *result = init;
        }
    return result;
}


template<class InputIterator, class OutputIterator, class BinaryOperation>
OutputIterator inclusive_scan(InputIterator first, InputIterator last,
                              OutputIterator result, BinaryOperation bOp)
{
    if (first != last) {
        typename std::iterator_traits<InputIterator>::value_type init = *first;
        *result++ = init;
        if (++first != last)
            return boost::algorithm::inclusive_scan(first, last, result, bOp, init);
        }

    return result;
}

template<class InputIterator, class OutputIterator>
OutputIterator inclusive_scan(InputIterator first, InputIterator last,
                   OutputIterator result)
{
    typedef typename std::iterator_traits<InputIterator>::value_type VT;
    return boost::algorithm::inclusive_scan(first, last, result, std::plus<VT>());
}

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_TRANSFORM_REDUCE_HPP

/* inclusive_scan.hpp
AQbN8IDaSCkRMQnDHvVWWa5mp7KEojXVHHtqa7BdlUHLZ8i4/ZSNmonoiCkmhBsYYhTtx0dZ45HlCNySRqvrqTgI7pN5qEy0smGqYMhgVOHfaZw5dlTi4XsivN6lMi7DM+lCMLodE4JeIljQj3CepVz554wN2j0tXuWsl994+8sj9aZSPiLxMPe1KvhM2iu002GCZds8+yhZJyeice6vdozna/4+jpB/mco6B/xfEpdOIbSKrGfbHkdPm2ElEQKvxcZSPcOxpb7Qd++ztMKTb4QsMfKblWlIHlkvBXUaTS0ycgnvx8PVlaK4OVvjEq3QhjU27eFTVS17KQviphTEpFvhz6vRWP82STimCh2Vfe4UaBUyvdCUi9gfrL/Ciga+edu26yFUTjNxh37R+7KJJmgqFZw9o47tJ8QoZFn0cOCvrBGFk6iHGfh4rEPKFmUYtLdRv+x4uC81CCRVL+wJKBXrEMjzI4zEHX+HC6kswjLYtbDQwJ1bgELZL4BsmdICYhsh2znVPcr9GnGVek8qrc4eAUFiee/UvMYepvSqOXpS6+Q7tzV/DTGn9dKjQPnb7JGFNHtQPVyFalFTJHsKKuhABHTzir61VfZy0j9nph3Iol6XZnPfAfoP6/jt/Sf+lfC+QCTRgWbFJ1jq
*/