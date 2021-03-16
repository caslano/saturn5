
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_FLAGS_H
#define BOOST_COROUTINES_DETAIL_FLAGS_H

#include <boost/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

enum flag_t
{
    flag_started        = 1 << 1,
    flag_running        = 1 << 2,
    flag_complete       = 1 << 3,
    flag_unwind_stack   = 1 << 4,
    flag_force_unwind   = 1 << 5
};

struct unwind_t
{
    enum flag_t
    { force_unwind = 1 };
};

struct synthesized_t
{
    enum flag_t
    { syntesized = 1 };
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_FLAGS_H

/* flags.hpp
XT9OfgjWOw8n+5H3vFZugPXmIzRfFONH7mceAsZ/lObjjpfcQt0EzKc5Lm79TB6rUvQY9MfjNF+c4Cds4ri7NyX7vQx+24FZ/GSyH5m/xU/BWvspmo/rD/Jk/xpgrn+a5uParwzS509zaMvnRx5M8D1wJ2+m+bj5S34zNG1zul8l+F0B3Npnk/1ESEeAGfAczccdL/ETgZn0fLIfuQHfDEyfF2g+rj/mkPYD5tn/oPmk6+XZv+fQFjffzgOuy38=
*/