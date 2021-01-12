
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_COROUTINE_CONTEXT_H
#define BOOST_COROUTINES_DETAIL_COROUTINE_CONTEXT_H

#include <cstddef>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/context/detail/fcontext.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/detail/preallocated.hpp>
#include <boost/coroutine/stack_context.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

// class hold stack-context and coroutines execution-context
class BOOST_COROUTINES_DECL coroutine_context
{
private:
    template< typename Coro >
    friend void trampoline( context::detail::transfer_t);
    template< typename Coro >
    friend void trampoline_void( context::detail::transfer_t);
    template< typename Coro >
    friend void trampoline_pull( context::detail::transfer_t);
    template< typename Coro >
    friend void trampoline_push( context::detail::transfer_t);
    template< typename Coro >
    friend void trampoline_push_void( context::detail::transfer_t);

    preallocated            palloc_;
    context::detail::fcontext_t     ctx_;

public:
    typedef void( * ctx_fn)( context::detail::transfer_t);

    // default ctor represents the current execution-context
    coroutine_context();

    // ctor creates a new execution-context running coroutine-fn `fn`
    // `ctx_` will be allocated on top of the stack managed by parameter
    // `stack_ctx`
    coroutine_context( ctx_fn fn, preallocated const& palloc);

    coroutine_context( coroutine_context const&);

    coroutine_context& operator=( coroutine_context const&);

    void * jump( coroutine_context &, void * = 0);

    stack_context & stack_ctx()
    { return palloc_.sctx; }
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_COROUTINE_CONTEXT_H

/* coroutine_context.hpp
I2YXpml32k73uI62/Xn8ovv/sxSltKS4YH/oAHDW+g9taJk9Ugt13D4IY2M6Yb7JpL1yozFr/UvNsk4zl/p+psg1lHq/s05/rVoZXg3PNjJ9J8uaxX3LzUS/LzrxNdT4vHu8btRmPFOf78s1/Uti059fOL18SjmLDKy902++7S8XPwXWoe5ejhpOB29esDPyGKpz31GEUBHzrf11cdPVhLNOzkeYeWjLI6eVztl9cj29prl7
*/