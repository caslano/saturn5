
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
tDvsRK0a+q+h74N1PX+LBusc1sDYlV2vJe5uajsR8T8kzrZ+6DdTKiP7KHhnL19x9vJJ1fArlf8QPH2QOuXqJUtcu0l30Sjn1KQ713+uWNcI4PoZ21AquX+n5WFZJvMVo/9C5QcNpncXje/OerxM03u2E3ypNtUIBwLsKTiI1obMWOf0b2Bj/653mQ+76Q51b3Sj2PpJtiPD+3ZMv3N0peme6I+y4bLtkciQwCILI7cjCSOD+6a3jkwtnOycfOraW+ta21qbWrtaGz4Mxzs3UjIPjJzuSgroKifP7Cq21WSxAlKAu/HO3cJq1Sl8w5m7VZduHqUsKX9TmCpeVPcud2DoSDAmM0z/wliZpK2tw8Rsw3zMPJccTTw8c+PLEfZUhlWItY1FiBUcPP376LOFiZ2JT357bV1tW21TbVdtQx5s/Vlh+OmbR5a86ofU4YpdeY+qTmrVjJtisLozY1OS0TDLNatFKnqqswKdwl3xVPFFcXjxb3Vra9fy+sbmxm5Nw+UvywbLestGy7oEI/G7B862At2r3VlflNlKU2ZG0ne7d08uN5ztPcwFQMLtwt3CdQZf2Fhr2HRSFlIWUitGKEYyR/RHVkaERkwZ6gkMw6vAOss6BMxDybPyngwNARlUBkNVUYP3VDVqfzKZ9ZlXmIWYF9twcv0L8Bglseo+d04ayRIlBGvSGg4S3f+19Psrrc4bxh2swuCL35L5
*/