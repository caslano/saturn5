
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
3f5JdWw+C/Pg87AVfBH2gfthX/gKHA0PwMnwIJwCD8Hl8D2o9xH9/oMxisd9ZLimdySMdey1XY7R9jgW9nL8wlPg6XAcnKL5c9TWbyb024ytmjfvanvYqPlzPWwAb4C58EbYBP4U9oQ/g4PhFjgc3gJHwl/AifBWOBfeDhfAzHhrRQW8G/P58F54CXwQboQPwRvU3a3wMcyPwyfg03AXfB0+peWyW+/Lf4QN4YuwG3wJDoYv
*/