//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_MAX_ELEMENT_HPP
#define BOOST_COMPUTE_ALGORITHM_MAX_ELEMENT_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/algorithm/detail/find_extrema.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns an iterator pointing to the element in the range
/// [\p first, \p last) with the maximum value.
///
/// \param first first element in the input range
/// \param last last element in the input range
/// \param compare comparison function object which returns true if the first
///        argument is less than (i.e. is ordered before) the second.
/// \param queue command queue to perform the operation
///
/// For example, to find \c int2 value with maximum first component in given vector:
/// \code
/// // comparison function object
/// BOOST_COMPUTE_FUNCTION(bool, compare_first, (const int2_ &a, const int2_ &b),
/// {
///     return a.x < b.x;
/// });
///
/// // create vector
/// boost::compute::vector<uint2_> data = ...
///
/// boost::compute::vector<uint2_>::iterator max =
///     boost::compute::max_element(data.begin(), data.end(), compare_first, queue);
/// \endcode
///
/// Space complexity on CPUs: \Omega(1)<br>
/// Space complexity on GPUs: \Omega(N)
///
/// \see min_element()
template<class InputIterator, class Compare>
inline InputIterator
max_element(InputIterator first,
            InputIterator last,
            Compare compare,
            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return detail::find_extrema(first, last, compare, false, queue);
}

///\overload
template<class InputIterator>
inline InputIterator
max_element(InputIterator first,
            InputIterator last,
            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    return ::boost::compute::max_element(
        first, last, ::boost::compute::less<value_type>(), queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_MAX_ELEMENT_HPP

/* max_element.hpp
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
*/