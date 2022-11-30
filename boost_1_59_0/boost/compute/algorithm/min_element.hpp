//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_MIN_ELEMENT_HPP
#define BOOST_COMPUTE_ALGORITHM_MIN_ELEMENT_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/algorithm/detail/find_extrema.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns an iterator pointing to the element in range
/// [\p first, \p last) with the minimum value.
///
/// \param first first element in the input range
/// \param last last element in the input range
/// \param compare comparison function object which returns true if the first
///        argument is less than (i.e. is ordered before) the second.
/// \param queue command queue to perform the operation
///
/// For example, to find \c int2 value with minimum first component in given vector:
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
/// boost::compute::vector<uint2_>::iterator min =
///     boost::compute::min_element(data.begin(), data.end(), compare_first, queue);
/// \endcode
///
/// Space complexity on CPUs: \Omega(1)<br>
/// Space complexity on GPUs: \Omega(N)
///
/// \see max_element()
template<class InputIterator, class Compare>
inline InputIterator
min_element(InputIterator first,
            InputIterator last,
            Compare compare,
            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return detail::find_extrema(first, last, compare, true, queue);
}

///\overload
template<class InputIterator>
inline InputIterator
min_element(InputIterator first,
            InputIterator last,
            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    return ::boost::compute::min_element(
            first, last, ::boost::compute::less<value_type>(), queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_MIN_ELEMENT_HPP

/* min_element.hpp
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
*/