//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_FOR_EACH_N_HPP
#define BOOST_COMPUTE_ALGORITHM_FOR_EACH_N_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/algorithm/for_each.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Calls \p function on each element in the range [\p first, \p first
/// \c + \p count).
///
/// Space complexity: \Omega(1)
///
/// \see for_each()
template<class InputIterator, class Size, class UnaryFunction>
inline UnaryFunction for_each_n(InputIterator first,
                                Size count,
                                UnaryFunction function,
                                command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return ::boost::compute::for_each(first, first + count, function, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_FOR_EACH_N_HPP

/* for_each_n.hpp
9KVmzfYfMQqhRSN9OKxdbzyU121gHSMj5y+nhc1rBlqC73FU0irbnDQLx/moevcEDIx/veAKYVtueOnreiRytyje6CG2CAtcb3kc5ZKBx421C9SLdtDW+6aLVfGw0Czu//6MlvKukKjx9btAQJXWG7UyorFKgV9PgWQRdhKzBQNwR4iaT2xSjEoq/ZDNYEjWzjYs/G+O0ZJlrpzN45A18Lwjll6axnkbkO8mIcmLB0wzdV5glX1k1BlXC1khh3I0fhwfU/9p7f0epOofkEXYoc0oorUtq/zeuwF+YIlutSEAc1UWZm8sR6LZ8KSLHHWiQS3d7TjmyFjSHqM9kwSH//UIS3MMi912lYA2avtnxamOc3qlqFMUdqAl+YyzwAmrCqxQzZ0LDdCGw7nHr7EotykSURFpp7gZ4fXzuc9vII0AzdxR+bLnIxIqbvIr3Bo0DbaqtI4vcoQgyKlBHv28pzIwzy9nYkXhhfJkBv+nJP0xASxEXocPoZ4AT8Pr5fbhzj1lseNGNzhLJkLgHlfR0nqHSuYZXsa75vKtX4c5Ao4KgTedcpGXPW+bXQ==
*/