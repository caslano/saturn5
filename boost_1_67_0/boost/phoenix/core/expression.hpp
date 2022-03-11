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