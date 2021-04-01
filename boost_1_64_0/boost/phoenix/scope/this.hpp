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
dMIcYxVtd9PVsnjJECwlvv0CUkH5jrUxIyrMF1o0+LyiWAgx/RUY3j+pO/0IyIGy9NYzwAuR++WvXrsM45lsTWmZ/7yISe5TFa/9nKZTu1o02tkHv8/lh9ijHm70OVsg3RGJC1bHmGvoiCW+rXXieRnxh4lJc7Z7dCJ/Ig2mXPDXYAJzaKWNg5E+EtHSVsZkjBFk9E84w+tMvHOVWVvIbLpYjyP/Fyp9b5GSlx1dHUM5tAHu62DjCO9hrMEXt++pLLIbo6sJ53ccLzvb0kr3Ie7Bxb/g8fGhPYXVL7X73CeUjV+LRywURpaz1Y18hC29AQOpa6YIKxzUhQGi5hJ2WzXicRVingpMoyasMfPWZotal6fuQ/E5lWBE2v9+ZpSKllzZ2VXS12JEkBo74alYfe2FQeC1wxPgyPk+MDP9mHb/MWBaPOO/S4BEXLDqp2zo6HRXmQZFDFWFysbfoeDLaB15Q1LozV+Y6EnCGzAvIjW5ZjWcgBrGR529NkHRMS2JefcydpGw/hsN0ETktBLNCvJFrb3Ynq85gK9eRS0cC6VsHiIB7o7TUOwn9w==
*/