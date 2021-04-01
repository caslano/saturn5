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
pU6eq5i4bRGtVqApukznrjo/WRm0b3lA9R2OqGxIQV9mdxRZrWUqBfHsAD4rbA8PaFCTHbKRIGAvqRLI21odizB7NC0JVtM3MQlaTFoD8FsE1Kt2dtdx1p94SlKlToLLK4WC0xWrRQP/5QCvNSwed/NMCLXz+ssc3vntS2a73i9CSvczuNlQmrkb6b/Cj1JASi8nXulr4hAB2jTNA7sYyN4slsJKNIqiwJhhRkJlShPLyJjjYcQT8Cj+/1NIVccim6+H7AYaRrn8OfUfCPUflP4QLpA4vMSYt1OyU8hN4KS/O+qEIBe9XbzUOur9klK1VelFle34KQEOqXz1+4Zo9J27Kb6ZkoTD1FDTVM+bzWz0uOnMOr6TJ6QFh/7+AHaYRBl7qDVn3zI5yG4qQwmiiMynI1hBRM+RKqvH3HbJp1VsoQIk0PUjq43ZUd6WuSZQTfnl5enFe6Lzack9ySqU+nOob06vAD0CSTg9m73M6k6atn04vl/8oGpis6woWDf4O6B2zcaSJOJPY1MxNzSeWVpAj9y3cKdaravSV/A8DwuWlKYN/LbQq9x3Gw==
*/