
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
mdCQ99F5aDaYWZ42Z+o/8hWCKffkfQXkBJN/j5xfg0ZOy7+RnF84mPaN5fxmgFnWmPc1Qh1kg8n1kn31mjitlk14H83L9mCO13D1GN91MA1cvI/2Iz8wJS65//yaOq3wprIvCoynt+yLAhPnzfvo/ngSmPhmcv/lgjneTPadB1PYXPYF3uu0Iu7lfUWIQWCCfOT2jgQz2Yf30XybB2ZoC9m3BEx2C9m3H8wcX9l3GEyxL+/LRFwFk3qfXH97wOQ=
*/