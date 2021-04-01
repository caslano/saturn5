
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
tDhlaYoaJQuXt8w6JJ8xOQSesS2jPdKXoSjoQ1IzeJ7pp3Ls5Hi7oWFsPWwkTCAlxHGT10bzJtaWKMrucn0NNxghaVYAp+HDgeabGruRNZfR8+McTfK4Cl9t1N5MmmcX10wtcWDvAnyq4SC6IJsjsx31NFe4ZknZHwT/kok5q4w4lXFf3Z6vDS3cyDSUZdOgxIGMQbloCqFg8SrZLwGl4hAgvG43eHaRp0Aw1Nn1AqdegQqC33arX6OogWl8D0k9caPFgacVFAQEoA9kqAN7HPNPZdbKBPdkBdwQBYOznnR704ho/Gacl0apirPOoCiRB2hEy8/m5bu0ejP7QW/Y2gpOxme3jWdqyGotsB+bvxiJsTp8KNdVvzhmljKhkeaqVoQ3EoPGh8MhSOL0drFgDek1x5i8gUhFleu2kYB8/Y0px5xiw8RfyQaz7kclOPmp6it82FnBKQzb7937yFQJgsf6dFHySmjENDliEMhLSShOibuBraAOIt4Wg6BXxFz0yFWOnre8z7HRhkIwP4QudDOl06EjCEr6PGsyv2g5T8X1r7eBY9Re2bXlGA==
*/