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
8j7TcHIzgHcfP/4MZ3BxfnHuwC0rpcgh0qJciebegStuRn7N2OOjq8RnB4QGlrsHgHEmFahqrTesEYDPuUxFqQQHpoALlTZyhS+yBJ0JWMtcwM00XAST3x3YZDLNepxt1YLKqjbnkLEHAY1IhXzoYGrWaKjWiID4XCqNmK2WVeliegFaNIXqYYgEy1UF7IHJnK0wHdOQaV2rX4bDtG1yrGTIq1QN050UbqaLo6oWyKZgW6hqDbqCVgkHaL0DRcXlmu4oEQ7W7SqXKnNeaGHCkg+rBpTI8x4OQ6VQXQkCol4th1ZCjeylppuqSkXZNllVHCxEWXugdduUmA5lwXW8QuEdaEsuGrPeCLHL0qtsJP/Glr1w51CVyApsL4IgsmHFlFQOfA3iu+k8hq/ebOZN4gVMfwNvsujx/ggmt+gNiVkbEI91IxSyaEAWdS4FP0j+HU96fAe0n0khC5HIEjV8D/bFBXjtfas0mvrdBxvsXK5oFXxwf/zJPd8bGLOyZbltudEdTLyxbx2BnUHaCEbbCTSIrix5LszyaDGZhlEQWe41/CDLNG+5gCuK7xyWfbZcVeNsAPYzKtngIMPJzXw2wlEbBFPbpMMHe3CJnBg3iW796GYWhHEwnVjLdXAU/36wXIc9S4U0ewR0BoNS
*/