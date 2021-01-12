
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_SYMMETRIC_COROUTINE_H
#define BOOST_COROUTINES_SYMMETRIC_COROUTINE_H

#include <boost/config.hpp>

#include <boost/coroutine/detail/symmetric_coroutine_call.hpp>
#include <boost/coroutine/detail/symmetric_coroutine_yield.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {

template< typename T >
struct symmetric_coroutine
{
    typedef detail::symmetric_coroutine_call< T >   call_type;
    typedef detail::symmetric_coroutine_yield< T >  yield_type;
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_SYMMETRIC_COROUTINE_H

/* symmetric_coroutine.hpp
t8GX4Hb4srbP1+Df4evQ6fdvwHT4FuwCt8Nuet5Xz/vBL2B/uAkOhpvhKPgePEndjVN34+GnMEftix17jb+3rd/A9bv7Mn3mOUjrBR1ncl+/EybBVbAjvA/2gF/DPvBBOAA+BIeq/Sj4V5gPH4PF8Ak4Bz4NF8G18Ae1JxFy/jBcB1fD9fA5+Bx8Gb4IGwYoR5gNN8Ar4avwWvgGfAzugM/Cd+ALev6pnjcN8nwFW8L3YUf4
*/