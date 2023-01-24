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
uIgJGBgOUszrNPo7yu/Fg0r7Cj9QVYl5x2KFzRbS8E77Fodsv/kYEov1jirb6Abmsq7se8AkFIWud7SV27E1vh22MDPivu2tdjL7cwaJpgfaa/wCpQfHvzEJaoVjXPrCbhnj0jF23V5lcglhsjRR6rf5C+wC7INt31Dw7RTohFohFu5V7WtORfRiRhoC1y8GU2VSqdEBHb+R2bl0mMU50rxmeABSZH6URx7AX1fHrUEtLQUTwhgN2UxXcR/MCZonouwBURz7iQlDBfaTJoqMDZhMTRklkDksqwnrv+MBzUZ7nRb/YBZbW41MRIN95vZ/Pd/U58sQ34Gd9A/4IyFetKg33xO7t5XQl7QHGJnen8fyoD/qX1V1DXsYwx8WKwcLzzCvhgLNnMsP/e4VCSZKp0gkZ6oxN2QkSWp2JIkqO8Jwm6aysPIbLpgoGHE9D1uKu/0J6F+4GJmieV4MlP4/a2w8b2wXxi/FltDsHfMYNiFPJLEMV7Drbwo2mfw34p8r8Y8N/6Tgn4TgWVOg71aUH4V7bbXiJWlrDGl1tqK5Stic1cIxIqq09e8S8bvuK/bgIgh3tm36rlM4Bv7GQ1mFlR2il+2CZXu6ZM814Z7OjSh/Dnd1bkQXhHCsk1zAXV322NZb/wabuYhFZq32sIi+u5qQW0XUzi3ZuJ+FZrjXAzfJZJ7AhkK33DOjo9AtM/ny6vEGY8u7vKHFes7n
*/