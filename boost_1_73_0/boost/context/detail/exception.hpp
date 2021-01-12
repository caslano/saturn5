
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_DETAIL_EXCEPTION_H
#define BOOST_CONTEXT_DETAIL_EXCEPTION_H

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/context/detail/fcontext.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {
namespace detail {

struct forced_unwind {
    fcontext_t  fctx{ nullptr };
#ifndef BOOST_ASSERT_IS_VOID
    bool        caught{ false };
#endif

    forced_unwind() = default;

    forced_unwind( fcontext_t fctx_) :
        fctx( fctx_) {
    }

#ifndef BOOST_ASSERT_IS_VOID
    ~forced_unwind() {
        BOOST_ASSERT( caught);
    }
#endif
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_DETAIL_EXCEPTION_H

/* exception.hpp
XVzRxdVVrKtr239OzrszLwyI7dt1vzy+y597bpnb5s7cdgZGocw3wvkwT/vBAu3/WsJL4G5wOWwFV8NC+DDsDJ+AJXAD7Ak3wt3hJtgfboYD4OdwD2jblAdMhkNhc7gfbAW7wK6wK+yl8gGwDdwPtoOHwvZwsrqXw46wXu0nwGHwZDgcngv3hhepu1Oul8XeqeCFWk/pmMVaT09ou3gGJsI/wxz4ImwDX4Lt1N5N7T3gX2BP
*/