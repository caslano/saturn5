
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
bCh/oWT72DMQJUYFPTcCP+rBikgmbbjz43E4j+HOnc3cIF5A+AncYNHh3fjBCLXB0GsN9KGqqcQoamDrijOaHTj/oZ1uOfEYhvPZJJzGySiIknnkJZ8n4bU7SYbucOzBOfTOLuD3ptQa/7kHPc5WWgRw4ZxfOKe4oVcJJfIxkVTpcuMXlSURPBpD4N561nc9LE+AllpnA2TR6O2eixXhgKchJWlBDVC0CMJp5EfWT6xMeZNRuNKeW0UWHy3jJBW4/zygI/0GjgvUCkfJfC8Y2/r/4cBFed9F2v9gQhp50XDmT2M/DKwxdlkpUF5lqrMHiVFSJOndW+fUgZHAl0p3wRvLmhKsLjF4Dvit1pa530Iv8ylsCG+MrM5sQGErbANpsuo6CY33FFmGIgTBLt0yzkE29Qb7HlZUbSktQTMBbfKQ1pSY4pjGySinZuW0isYm0VGqAk9lJ5LkphPboWGgD3xvSM10xI5lLfNrFHaAzfJex28MWhXoLFL0wLDDdG+spECf1MEhKSrEY8gpU7jcMpUWIDa0tkyS+oUmRhamxUrszJyk+kkqjO4NRNSwtqtmNHZn3tF5X/vHoDEk3+jA2CesZKp96XSV++TOJ7F1albTWRiHw3ASWa4eOLjj/eHeTiee5ZS51arH0P/r
*/