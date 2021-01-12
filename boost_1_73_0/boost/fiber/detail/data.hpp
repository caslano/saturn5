
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_DETAIL_DATA_H
#define BOOST_FIBERS_DETAIL_DATA_H

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/detail/spinlock.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

class context;

namespace detail {

struct data_t {
    spinlock_lock   *   lk{ nullptr };
    context         *   ctx{ nullptr };
    context         *   from;

    explicit data_t( context * from_) noexcept :
        from{ from_ } {
    }

    explicit data_t( spinlock_lock * lk_,
                     context * from_) noexcept :
        lk{ lk_ },
        from{ from_ } {
    }

    explicit data_t( context * ctx_,
                     context * from_) noexcept :
        ctx{ ctx_ },
        from{ from_ } {
    }
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_DETAIL_DATA_H

/* data.hpp
bxw1XU2Rj0K6AWMIH/4aJsAHYRA+BNPgozALHtJ6+jhsAZ+AHeBO2AU+CU+Av4VT4O+1fu2GC+EeuAo+A1fDP8Gr4PPwp/AleB98Ge6B++Eh+Ap02uNfYC78KzwZHoDj4KuwGL4GfwjfgFfBt+B6eEjrZ3PHj7bL4bpXfgskU/uzo2StH34Gk+AXMB0eg+3g1/BJSFxkT3w//AsMwINwEjwMY2ASYcbCNOjY58F42ErN+TAZ
*/