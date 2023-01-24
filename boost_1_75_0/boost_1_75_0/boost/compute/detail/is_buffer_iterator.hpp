//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_IS_BUFFER_ITERATOR_HPP
#define BOOST_COMPUTE_DETAIL_IS_BUFFER_ITERATOR_HPP

#include <boost/config.hpp>
#include <boost/type_traits.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost {
namespace compute {
namespace detail {

// default = false
template<class Iterator, class Enable = void>
struct is_buffer_iterator : public boost::false_type {};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_IS_BUFFER_ITERATOR_HPP

/* is_buffer_iterator.hpp
UnF5bBke3gGGqeNjRh0v8TReZD0bL8+qw2S/Soq/RI2X5842XpZX4JtC7fYbJP4GBTOHnmW8tC7V+Ml0nI8X5NYgDrXwAEjxii96LdNQbSuzCDY/gO8PokMFVLF2KR84scCQwR0ozp7X+P07xkVPLOVclAykYiLPr7Km24O3Z2P4m8MAbjjGGR65mokzzvAFyPCL8enSiKdT8WkZPl0bydq/Cd6Bz7ZoQyOfDY2c4C0M2E+WRACL/Roczhj9N8LygexqkfDU0wh1G2fs+Ule8TPfK0CuYCsuDE5oDP8tFlP4rasI2lkY3MMY9Q9sCFi8YgsQdWIj8kTwAzYMnIuwux3I/jnI/mkq+/+OfbtFZf+nCAxcbD4Ej7MY70OV34b+Cverv8R7Ae7bQy/7Pr4szO0v4gCwc0beU8kYORVYIHS5pcOvd17vWxvJwbM4Byf4cHcW5UBIoOmO6osFtD4lvo70rBMl49swxdH5yao5tA8r2qWtoGmjUzpux9Vedgb350C55Ptz13+rKDuC89uUc9rgHNLtvex/W6RBYuCb2ALD57QTfl9b9E744D0nPje01Eztvgvu+x8/WHo2M9vZ/QXdR5Ltnv7pmNbQ5ED7z7T0FHtmi0MYv3e2XRoyAjVtR+7eY/MHllmWfa1rd3hf1rXDKrPeQI9dP9ol+FpCC4f7k+RjdcqIphLcJvqQfr30u5R+n6DfUvotot+J
*/