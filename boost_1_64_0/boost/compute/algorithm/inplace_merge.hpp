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
6ffFiOBXnZdTP2DBAwe7ruXw7peOPvJCgK6jCvL7PSHvSjRgXYwWdzWOK1fnVXClPRWwXomB6Rahz/qVjeO+cwcCynfXYeKHnX8mXz6RFr3VHxjmViN+o97O9Y2owzLfp3RAcs4LxU2WuKEV45EE6ICSOxc7HKkODnaRqRqJnUdlTzLnRSL/dOc5H7qo1ZsDtlQb6/rrPcRLppN6LaI2ZPZo750mQ+hc/D2/LQ5JAP1Cr7J+Z5ufnhkaW3SfTCPkXKacIWQBjnqcCoYVN35KN4uPo0Tk8F43uhfdNy2N/dLarVDyZkzpoY3G/gxdj8ZXLtdi9hxZRMBgn+El7HPr7j4i7ypfHwoCRU0GQbigO34rWy5FsHD6ZA0e4yMXrLp1vxe2TVz8bAd8pnWWOALLCwTlZS5NfsY6Tj2kFsvKq8H+PP+U5UPSf/c1Vo8PFAzUFWQQya9W7ivswXXRxcYrcXV5GyeItY/pgfSWe0uUT6uH6KIHi0sNt/JUdVTVyDKS14WyYvIhyUuIIcnwSOzHDzPSS7OlY/U/WJNHMd3GIQWg/wvxVgMYIBVLRQ==
*/