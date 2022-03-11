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