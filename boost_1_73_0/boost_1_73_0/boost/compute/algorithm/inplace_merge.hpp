//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_INPLACE_MERGE_HPP
#define BOOST_COMPUTE_ALGORITHM_INPLACE_MERGE_HPP

#include <iterator>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/merge.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Merges the sorted values in the range [\p first, \p middle) with
/// the sorted values in the range [\p middle, \p last) in-place.
///
/// Space complexity: \Omega(n)
template<class Iterator>
inline void inplace_merge(Iterator first,
                          Iterator middle,
                          Iterator last,
                          command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator>::value);
    BOOST_ASSERT(first < middle && middle < last);

    typedef typename std::iterator_traits<Iterator>::value_type T;

    const context &context = queue.get_context();

    ptrdiff_t left_size = std::distance(first, middle);
    ptrdiff_t right_size = std::distance(middle, last);

    vector<T> left(left_size, context);
    vector<T> right(right_size, context);

    copy(first, middle, left.begin(), queue);
    copy(middle, last, right.begin(), queue);

    ::boost::compute::merge(
        left.begin(),
        left.end(),
        right.begin(),
        right.end(),
        first,
        queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_INPLACE_MERGE_HPP

/* inplace_merge.hpp
FKouqvFdQbN7ka5nJYryoipd6e4Xpk8jJwWyKB3NjCQJpJxenpx4XVqvPK4L7z5FDZiq/lgNqWUtA9BnGavTcI42C6ygFpkiscWN2K+2bN/0X5JOWRWGI7FoNG77wPeWVkm2bN0qzhffr6B3DUWU58zGMQaLEk6ZcaVl69sQe9x6aFexYqF84Czr9w041Doc3/NKCm2WvK3Ey8wLSWCDU2xarVOTbVr4LSxZrxZNiWn0iiaWIAmqe5uRQZ25YmFiUltwA69umhyByoIeGFmDmHv444FJN5xeQQPY3BZuxqHkTlXDJCpgGxuqhInEOZxVVokH3LtJxEseGSzvgtUt8Ell7tD1bTjQLLISPMpKwaHO8wp0MOmjqfzEIetonq1jEx4ygk9aVwMSX8GBigqTzUwmIA9nCHakEUvilEFZZATzJnNWOqc/gq0iN/mM94omx2ymUGBm9w4TBWTCgGq1clzxb0GiQzHnZgjdOB3gOD+KafhQZ4EjdRzdHCoBjNqVyA4lcxsrafKyuheb+3QhXDho932YSIRmBKB3y3RXhryAGjxWaSYsEhVrxEUAGuwXcgD+rCQ4Kl3UQAsWjLxXvnmEra5WVOhh4tjNJUOy+x5JjgNq9GXD9Mp7jicTpDrPouh+4v47hgSiniGJ
*/