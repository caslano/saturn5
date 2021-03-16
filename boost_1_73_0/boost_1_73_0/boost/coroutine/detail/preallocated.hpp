
//          Copyright Oliver Kowalke 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_PREALLOCATED_H
#define BOOST_COROUTINES_DETAIL_PREALLOCATED_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/stack_context.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

struct BOOST_COROUTINES_DECL preallocated {
    void        *   sp;
    std::size_t     size;
    stack_context   sctx;

    preallocated() BOOST_NOEXCEPT :
        sp( 0), size( 0), sctx() {
    }

    preallocated( void * sp_, std::size_t size_, stack_context sctx_) BOOST_NOEXCEPT :
        sp( sp_), size( size_), sctx( sctx_) {
    }
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_PREALLOCATED_H

/* preallocated.hpp
5u2m+aTjfRWY93an+x0F5sib6X4XvAV991ayH7nfagRm+p5kv/2QtgCz8o80HzffyDsZ9wMzfR/NnxTjRz5X34a14ts0H1c/0ryzgLlgP80n9cd8YFbsT/d7AJiZ76T7PQbMy+8k+5H22wfMgQM0H9d+5Ku6Mw9y3NKDOV2MH1lPPgHMjneT/cj7qk78M5S/T/N9YvzmwI6+BGbSxzR/eozf23ACWPgJx3mHk/1Ig1X/D6SvaPacGD/y/s0vjsI=
*/