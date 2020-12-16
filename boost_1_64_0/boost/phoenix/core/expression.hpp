/*=============================================================================
    Copyright (c) 2016 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_EXPRESSION_HPP
#define BOOST_PHOENIX_CORE_EXPRESSION_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/phoenix/core/as_actor.hpp>
#include <boost/phoenix/core/detail/expression.hpp>
#include <boost/phoenix/core/domain.hpp>
#include <boost/proto/domain.hpp>
#include <boost/proto/make_expr.hpp>
#include <boost/proto/transform/pass_through.hpp>

namespace boost { namespace phoenix
{
    template <typename Expr> struct actor;

#ifdef BOOST_PHOENIX_NO_VARIADIC_EXPRESSION
    #include <boost/phoenix/core/detail/cpp03/expression.hpp>
#else
    template <template <typename> class Actor, typename Tag, typename... A>
    struct expr_ext;

    // This filter cuts arguments of a template pack after a first void.
    // It is necessary because the interface can be used in C++03 style.
    template <typename Tag, typename... A>
    struct expr_impl;

    // Helper template. Used to store filtered argument types.
    template <typename... A>
    struct expr_arg_types {};

    template <typename Tag, typename... A>
    struct expr_impl<Tag, expr_arg_types<A...>> : expr_ext<actor, Tag, A...> {};

    template <typename Tag, typename... A, typename... T>
    struct expr_impl<Tag, expr_arg_types<A...>, void, T...> : expr_ext<actor, Tag, A...> {};

    template <typename Tag, typename... A, typename H, typename... T>
    struct expr_impl<Tag, expr_arg_types<A...>, H, T...> : expr_impl<Tag, expr_arg_types<A..., H>, T...> {};

    template <typename Tag, typename... A>
    struct expr : expr_impl<Tag, expr_arg_types<>, A...> {};

    template <template <typename> class Actor, typename Tag, typename... A>
    struct expr_ext
        : proto::transform<expr_ext<Actor, Tag, A...>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain //proto::basic_default_domain
              , typename proto::detail::uncvref<A>::type...
            >::type
        base_type;

        typedef Actor<base_type> type;

        typedef typename proto::nary_expr<Tag, A...>::proto_grammar proto_grammar;

        static type make(A const&... a)
        { //?? actor or Actor??
            //Actor<base_type> const e =
            actor<base_type> const e =
            {
                proto::make_expr<Tag, phoenix_default_domain>(a...)
            };
            return e;
        }

        template<typename Expr, typename State, typename Data>
        struct impl
            : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};

        typedef Tag proto_tag;
    };
#endif
}}

#endif

/* expression.hpp
EvvMrxnWe/27udcAU3QNMPv/n2shjFkYa8NYe8a6MNaTsb6MDWRsGGM2xsYxNomxaYzNYWwBY4sYW85YEmMbGNvK2C7GUhk7wNgRxk4wls7YJcauMXaLsXuMPWLsGWPPGRP38jY3xrwYK8ZYacYqMlaVsZqMmRlrwFhTxloyFsZYR8YiGOvNWDRjgxgbwVgcYxMYm8LYDMbmMZbI2BLGVjK2jrFNjG1nLIWxfYylMXaMsZOMnWMsg7EbjN1m7AFj2Yz9wdhLxpT7eZsHY4UZK85YWcZMjFVjrDZjQYw1YiyUsdaMhTNmZaw7Y5GM9WdsCGOxjI1hbCJjCYzNYuwDxj5hbBljqxlbz9gWxpIZ+4qx/YwdYuw4Y6cZu8DYVcYyGfuFsSzGnjD2F2OvGXN5kLd5MubNWEnGyjNWmbHqjAUwVp+xEMYsjLVhrD1jXRjryVhfxgYyNowxG2PjGJvE2DTG5jC2gLFFjC1nLImxDYxtZWwXY6mMHWDsCGMnGEtn7BJj1xi7xdg9xh4x9oyx54yJh3mbG2NejBVjrDRjFRmrylhNxsyMNWCsKWMtGQtjrCNjEYz1ZiyasUGMjWAsjrEJjE1hbAZj8xhLZGwJYysZW8fYJsa2M5bC2D7G0hg7xthJxs4xlsHYDcZuM/aAsWzG/mDsJWNKVt7mwVhhxoozVpYxE2PVGKvNWBBjjRgLZaw1Y+GMWRnrzlgkY/0ZG8JYLGNjGJvIWAJjsxj7gLFPGFvG2GrG1jO2hbFkxr5ibD9jhxg7zthpxi4wdpWxTMZ+YSyLsSeM/cXYa8Zcfs3bPBnzZqwkY+UZq8xYdcYCGKvPWAhjFsbaMNaesS6M9WSsL2MDGRvGmI2xcYxNYmwaY3MYW8DYIsaWM5bE2AbGtjK2i7FUxg4wdoSxE4ylM3aJsWuM3WLsHmOPGHvG2HPGxKO8zY0xL8aKMVaasYqMVWWsJmNmxhow1pSxloyFMdaRsQjGejMWzdggxkYwFvcPvu4FLse7jQP4owOVRx4VQoiKEEImhBAa2UIIjcypbVgIOYcQYjmMEMveTLN4c9oyIcRCrHcabcs55BxiIbwX6/491/N/367PZ++7zz7fz/++/9f/uv6H+356SrBIweYKFi3YMsHiBFsnWIJg3wqWLNguwfYJ9rNgGYKdFCxbsN8EyxPssmAFgt0VrEiw54KVCmb2qHyzEsxWMAfBagvmLFgjwTwEay2Yt2CdBfMTrLdggYINEixEsE8FCxNsomARgs0ULEqwxYLFCrZasHjBtgiWJNgOwVIF+1GwdMGOCZYl2DnBcgX7U7Crgt0S7L5gTwQrEeyNYBZF5ZuNYAbBagjmJFhDwdwFayGYl2AdBPMVrKdgAYL1FyxYsOGCjRbsc8HCBZsm2GzBFggWI9hKwdYKtlGwRMG+EyxFsD2CpQl2WLBMwU4LliPYBcHyBbsuWKFgDwUrFuylYLrH5VtFwfSC2QnmKJgzWfN3pgsMba3OW7J/fj+7IbQl2a5zLQZrFk4WVtaulbqWk31T4Z92zcj+Sv+tN2IvNtd5lbXzVNp1JXMvu58XWa2kvWGaTSF7xax6w7klqOtn5jo9s9wOQ15qdpAsh9moGsn4fcZH6JeY1ahgtMWLquD3v9QuKftOKFkXstOvzX7VbD7ZS2Yue7b4a3bghbluCbNV4/++r9nIl+a6Umarn7x5oFnCK3NdU2YbFj0IwXwgs2bW75HvOM3+InNhtmDWiF6opVJzXUKZtSXbsTh9nWanyBqWmS/ZxJ4D6mn2tNQ4np3JCgLroZ9mr01t1RLL6ZpVI6tYZj5kdmbFxZrVFKwuWV1mC2rdvo6aIHMos25kvifvjtU=
*/