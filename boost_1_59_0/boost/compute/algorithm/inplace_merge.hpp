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
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
*/