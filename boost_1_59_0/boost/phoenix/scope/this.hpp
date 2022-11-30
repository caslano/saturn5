/*=============================================================================
    Copyright (c) 2005-2011 Joel de Guzman
    Copyright (c) 2011 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_SCOPE_THIS_HPP
#define BOOST_PHOENIX_SCOPE_THIS_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/actor.hpp>
#include <boost/phoenix/core/environment.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/terminal.hpp>
#include <boost/phoenix/scope/lambda.hpp>
#include <boost/type_traits/remove_pointer.hpp>

BOOST_PHOENIX_DEFINE_EXPRESSION_VARARG(
    (boost)(phoenix)(this_)
  , (meta_grammar)(meta_grammar)
  , BOOST_PHOENIX_LIMIT
)

namespace boost { namespace phoenix {
    namespace detail
    {
      /*  
        struct infinite_recursion_detected {};

        struct last_non_this_actor
            : proto::or_<
                proto::when<
                    proto::nary_expr<
                        proto::_
                      , proto::_
                      , proto::_
                    >
                  , proto::_child_c<1>
                >
              , proto::when<
                    proto::nary_expr<
                        proto::_
                      , proto::_
                      , proto::_
                      , proto::_
                    >
                  , proto::_child_c<2>
                >
            >
        {};
        */
    }
    struct this_eval
    {
        BOOST_PROTO_CALLABLE()

        template <typename Sig>
        struct result;

        template <typename This, typename A0, typename Context>
        struct result<This(A0, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename result_of::env<
                        Context
                    >::type
                >::type
            outer_env_type;

            typedef
                typename remove_pointer<
                    typename remove_reference<
                        typename fusion::result_of::at_c<
                            outer_env_type
                          , 0
                        >::type
                    >::type
                >::type
            actor_type;

            typedef
                typename result_of::eval<
                    A0 const &
                  , Context const &
                >::type
            a0_type;

            typedef
                vector2<actor_type const *, a0_type>
            inner_env_type;

            typedef
                scoped_environment<
                    inner_env_type
                  , outer_env_type
                  , vector0<>
                  , detail::map_local_index_to_tuple<>
                >
            env_type;

            typedef
                typename result_of::eval<
                    actor_type const &
                  , typename result_of::context<
                        inner_env_type
                      , typename result_of::actions<
                            Context
                        >::type
                    >::type
                >::type
            type;
        };

        template <typename A0, typename Context>
        typename result<this_eval(A0 const&, Context const &)>::type
        operator()(A0 const & a0, Context const & ctx) const
        {

            //std::cout << typeid(checker).name() << "\n";
            //std::cout << typeid(checker).name() << "\n";
            typedef
                typename proto::detail::uncvref<
                    typename result_of::env<
                        Context
                    >::type
                >::type
            outer_env_type;

            typedef
                typename remove_pointer<
                    typename remove_reference<
                        typename fusion::result_of::at_c<
                            outer_env_type
                          , 0
                        >::type
                     >::type
                >::type
            actor_type;

            typedef
                typename result_of::eval<
                    A0 const &
                  , Context const &
                >::type
            a0_type;

            typedef
                vector2<actor_type const *, a0_type>
            inner_env_type;

            typedef
                scoped_environment<
                    inner_env_type
                  , outer_env_type
                  , vector0<>
                  , detail::map_local_index_to_tuple<>
                >
            env_type;

            inner_env_type inner_env = {fusion::at_c<0>(phoenix::env(ctx)), phoenix::eval(a0, ctx)};
            vector0<> locals;
            env_type env(inner_env, phoenix::env(ctx), locals);

            return phoenix::eval(*fusion::at_c<0>(phoenix::env(ctx)), phoenix::context(inner_env, phoenix::actions(ctx)));
            //return (*fusion::at_c<0>(phoenix::env(ctx)))(eval(a0, ctx));
        }
    };

    template <typename Dummy>
    struct default_actions::when<rule::this_, Dummy>
        : call<this_eval>
    {};
    
    template <typename Dummy>
    struct is_nullary::when<rule::this_, Dummy>
        : proto::make<mpl::false_()>
    {};
    
    template <typename A0>
    typename expression::this_<A0>::type const
    this_(A0 const & a0)
    {
        return expression::this_<A0>::make(a0);
    }
    
}}

#endif

/* this.hpp
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
*/