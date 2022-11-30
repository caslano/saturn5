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
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
*/