
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBER_DETAIL_DECAY_COPY_H
#define BOOST_FIBER_DETAIL_DECAY_COPY_H

#include <type_traits>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

template< typename T >
typename std::decay< T >::type
decay_copy( T && t) {
    return std::forward< T >( t);
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBER_DETAIL_DECAY_COPY_H

/* decay_copy.hpp
joIpcAFMh2XwdHgRbAiX+jDDZXASvAR2gqvUfgPMh7+E/eCd6u4heCo8AE+Dh+Eo+CUcD+P9uINp0DE3VrP2L/rNlHzP9Y3+5Rxb2yNsBAthHpwFW8DZMB8WwZ5wHuwL58PT1XwGrIIFsBTOhWVwgdqXwsWwXM1HYHtLvzuCDTRePpcekcWUs8MlWt7DLf3WB16p7mOR/ur+lLhq9wNhYzgFNoVnwzx4Jmwu5nC73aHh/dCj
*/