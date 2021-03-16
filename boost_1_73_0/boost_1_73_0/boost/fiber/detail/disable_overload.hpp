
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
eR+tzz5gPENlXyyYpFDeV4VIATPtEdmXD6b0Ed4XhvbeABPcQa6XeWAyO/C+LEQumGFh8vjOBJMexvsKEFvATO0oj+8eMPkdeR+tVyVgKsLl/uvRCetGJ95nwTcKzKjOvC8csQdMeQ3nNPjKEfUfdVpXH+XbOxwR0sVpvdultp/d+aKR33Ywd7ry49sM8dcIp/XHH3c+F3yTwc3uxreXfKe7yT66f3UJnMdjvI/++sDTj+l8Y8HN6sH7piAKwTw=
*/