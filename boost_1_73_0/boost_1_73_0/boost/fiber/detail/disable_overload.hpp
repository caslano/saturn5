
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBER_DETAIL_DISABLE_OVERLOAD_H
#define BOOST_FIBER_DETAIL_DISABLE_OVERLOAD_H

#include <type_traits>

#include <boost/config.hpp>
#include <boost/context/detail/disable_overload.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

template< typename X, typename Y >
using disable_overload = boost::context::detail::disable_overload< X, Y >;

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBER_DETAIL_DISABLE_OVERLOAD_H

/* disable_overload.hpp
mX7FnR454Ce83Qp2VykYTQ7g5N27X+AITo9Pjx24IA2jNSSKNksq7hw4L8zOHxW5v3clfe8AVUBqd89hWjEJkpdqQwQFfK9ZThtJCyASCipzwZb4gzWgKgolqylMwmgxDT45sKlYXg1+trwDWfGuLqAiawqC5pStezctEQp4iR7Qf8GkQp+dYrxxMTwFRcVKDm50EqSWHMiasJosMRxRUCnVyl/H47wTNd5kXPBcjvMdFW6lVt/caoHZrMgWeKtAcegkdUDbO7DiBSv1ihThZtstayYr5zEtDNgUYy5A0roe3CGUUdlfgUIysOVoS2gxe6b0InkjdbRNxVd7hkjr4KjsRIPhkBa0KzgS70DXFFQYe0PELsrAsqH8hZI95l4AbzArsL0EpokNSyKZdOBmml6G8xRuvDj2gnQB4UfwgsXg72oaXKA2GEYVQO9bQSVmIYCt2prRYi/4D+10y00vYTKPZ2GUZlEcfllkSTK78hfpIvLhDOyTtxDwNer75K0Nds2WWgDws/vm1D3GDf0ro0RuM0mVLjV+UFUSHSeXEHjXvvVd77dHWGAUx7alO8Zbwe+3+M3WBFXwlW4N98ZXsgjCKJkm1k+syeuuoHCug/eCrN5bJk7Ocf/bnEb6BA4rlEqNivlePijPigg4
*/