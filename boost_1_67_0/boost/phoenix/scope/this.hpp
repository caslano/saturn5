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