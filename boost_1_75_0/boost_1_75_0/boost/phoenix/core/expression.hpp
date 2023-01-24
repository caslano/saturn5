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
dX8N0R6SQvdoYookYQQvwpFIvFvEf0RHqZrlhPR8vTzIRD6yHKp5Ai1aCdwnQmFLoPhVYIoKoEnGKYbQJDBBMaWpjVMO9ApqpEowznLR1dfQwaWdFqBddAV+2pCX96Ixd8s0mUgrYCIYfBJIZFVSBJVWSSsMcy2lNKROgFAJ3CcBfxHoVg1aYOpyuKCadOOBSlJ6a8DyU1dCUIWODHaOQfFZoQfGIK4ENqUKotY0gNOcBTZYCnouAp2Xgwwn7d4C3RBogTyXwzCN3aiDupgGqgXrBMuhTMUgs5CQPa9vuOOiK/Pmn7XihaXz3mm7g2gtHGfUWKDkEDCbEY1CwOssPBcVRakn6RH2bDMSLnad2bwuRWchsesyDMgBd72Fj4qKXYZMsT37tQYuthujgDWK0taNYjczikyPMli0nBH+qNB1+ZSYzDiK8G3ddZNZzGQmZJzIWE4zrUaieV1tBBCNsetqKHGh0aKhnEaKLmZxyyhyEpM8DgsSuzbcoIntWRfbc05szwaINq9r11pIRlS4QcfH9myKMsb2XI2vEK/rYKk6UETPJjBPOqhpjGLy14F9jOlA5DUGajtGPifMoAUBm9JBCLPFtXqDxpihMRqxxHhHJTI0KYYY0CDKiP+SzT03QkyUEVLeauQAJSza0/VROsKDbXh9spZwyUYj0UICY7JRT7BIZl5vgvySDaBABqQEHo7yJKN0A1iB5kKg
*/