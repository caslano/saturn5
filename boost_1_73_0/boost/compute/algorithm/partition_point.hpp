//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_PARTITION_POINT_HPP
#define BOOST_COMPUTE_ALGORITHM_PARTITION_POINT_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/detail/binary_find.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

///
/// \brief Partition point algorithm
///
/// Finds the end of true values in the partitioned range [first, last)
/// \return Iterator pointing to end of true values
///
/// \param first Iterator pointing to start of range
/// \param last Iterator pointing to end of range
/// \param predicate Unary predicate to be applied on each element
/// \param queue Queue on which to execute
///
/// Space complexity: \Omega(1)
///
/// \see partition() and stable_partition()
///
template<class InputIterator, class UnaryPredicate>
inline InputIterator partition_point(InputIterator first,
                                     InputIterator last,
                                     UnaryPredicate predicate,
                                     command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return detail::binary_find(first, last, not1(predicate), queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_PARTITION_POINT_HPP

/* partition_point.hpp
BOQFuwP32BzgD8Uhf0uZ4e3JkWQGUK4/2WVabgNv6zqwzLBojZQZIu1JZHVhmWHeIjqHuATM6qieQ1xA5xA9Ip5DBB7GFL4n8PMmygupPMctGk97SS12Kl+IcfaPE8kdLmvp/OftpDdwbvhYfFBmqEd9CjppMsPD1Zf6AzuQoaXMsJ7PGNNFdbwqM1SDkVMQn2WG6kvl2UKTZQaPE0HjmiEzlDRTZhg6iWQAKTP4y+isSrGS
*/