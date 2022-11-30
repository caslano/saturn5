//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_IS_SORTED_HPP
#define BOOST_COMPUTE_ALGORITHM_IS_SORTED_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/functional/bind.hpp>
#include <boost/compute/functional/operator.hpp>
#include <boost/compute/algorithm/adjacent_find.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns \c true if the values in the range [\p first, \p last)
/// are in sorted order.
///
/// \param first first element in the range to check
/// \param last last element in the range to check
/// \param compare comparison function (by default \c less)
/// \param queue command queue to perform the operation
///
/// \return \c true if the range [\p first, \p last) is sorted
///
/// Space complexity: \Omega(1)
///
/// \see sort()
template<class InputIterator, class Compare>
inline bool is_sorted(InputIterator first,
                      InputIterator last,
                      Compare compare,
                      command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    using ::boost::compute::placeholders::_1;
    using ::boost::compute::placeholders::_2;

    return ::boost::compute::adjacent_find(
        first, last, ::boost::compute::bind(compare, _2, _1), queue
    ) == last;
}

/// \overload
template<class InputIterator>
inline bool is_sorted(InputIterator first,
                      InputIterator last,
                      command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    return ::boost::compute::is_sorted(
        first, last, ::boost::compute::less<value_type>(), queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_IS_SORTED_HPP

/* is_sorted.hpp
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
*/