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
viAsVUk4n14txpOvMdaFygvW2JgGrjBNKVGIFcFSTmq1laiF9TBLZrO2VM6zXuOV0QO2JniylWOJYC5KZyBWQpUiYxvhUXhfu5MkyRtbcueJNLlL8setDwpf7Xax4A4qsYGpPbxB4yhGwMWojFTLkHkUXKybrFSuiJ9aYSMtE2PhqOSDGmiK3LZlwmw3mTigwlmulA/JGe2C07ow1TMgj5BFlo3VbMMjYIw0POAYjZZkW2y76UeH3TTb0f7nkzz1KmE0d4LOaIbxrINMOOVi3Izn36Y/5rgZXV+PJvMFpl8wmixY6/t4csHfW7GTBd3Xlhw7W6iqLhXJ1vDlIop48rgcX34+OfkkHB0f4de6Rzo3ktKsLfRPo6ja4HXWLE8jPkAl9SwJ2ZvNL8aTuK3HOB4evH3X7+N3FP6DAGcNvMczpV7AslyA1FZpj06AdU6jP9FfUEsDBAoAAAAIAC1nSlKogaKduAMAAFgIAAAjAAkAY3VybC1tYXN0ZXIvdGVzdHMvc2VydmVyL2Rpc2FibGVkLmNVVAUAAbZIJGCtVW2P2jgQ/p5fMaI6HWwD2euna3dbHQW2oN0FBKF7qFtFIXGwb4Md2Q4v6va/d8a8daUefGkQOHGel5nx2AQXv+/y4ALOXpH7Rnjh6BhD
*/