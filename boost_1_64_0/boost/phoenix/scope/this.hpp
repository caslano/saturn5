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
aDwcMALIAY4A3gj4POC3gJbnIl8AfYAk4ADg5YAPAW4G/BGw8GijsRbwCMATADNHgQP4JOA7R8EHcM7zGo1VgIcAHgmIAbKAw4A3AD4J+B7gTsDy5yO/AAOAJwKeA7gR8GnArYDTgKYXNBr3BWwDjAKSgEOAY4D3AL4CuB3QfEOjsRrQCdgDmARcDXgu4E2AjwJuAZwGNLyw0bgY0P5C4AOGAY8D7AX8i72rj2+qOsPnljaUUjDABQqiVq2KiJjv5qtJgRZbLNCVgsUxQ2lCWyhtaVIoiFqVCTLmOqwIrmrnUFERURFRETvHEBlz3URFx1xVhqioHaKiMt3znpvT3DQJI93+2G/rhafPPe857/n+TnLO9UArsBt4E/gESF6H/ANswFXAD4EFwE3AT4B7gK3A88DLwJ+BT4Avgf53oR4D44Bs4AfALKASWAKsBR4BngL2AQeBTqDPeqQb0AM5wEygFlgFbAC2AbuBt4FPgeQNGjYKGAtMBK4BaoGVwK+AF4A3gW+AwXdrWDqgA6YD1wI1wI+BO4HHgD3AIeAzIPEXSD9gBiYAM4BS4DpgLbAV2AO8BfwdkFpQn4ArgGygELgWqAJuAtYBm4EXgd8DfwO+AQbeo2EZgAkYD0wBKoGlwErgDuA+YBvwEvA28B7wMfAVwO7VMC0wFsgBZgILgVuAdcBGYBewH3gb+BD4Ghh4H/IaGAe4gCKgErgRuBfYDOwBPgT6taLeAhlANlAEVADXAxuBbUA7cAw4BQz5pYZdDBiAAqAM8AO3A5uA3wDvAseB/vdr2CWAHSgC5gMNwEqgBXgS2AX8DvgU+B4Y+iuUJWAErgLKgKVAM/A48BvgEPAtIG9EGgE7UAjMAsqAeqARWAtsAp4Bfg+8DxwHkh9A3QIuBbKAKQB9QJKATz4T8ekmemt8TtmPpeDTzVR8vD6QnYUP9wbhc/UhTMYXK4YFP34fyc5mo/BB8LnsPP5rjgvYhSyDXcQuZpew0exSNoZdxsayy/FbkCuYjumZgRmZiZmZhWUyK7MxO3MwJ3b/XMyNz2PHswlsIsthufhe65Usj+WzyewqVsCmsKlsGj6r/QErYtNZMb7xOhPffi1hs9g17If43cmP2LXMw+awUjaXlTEv87F5rByfI1Wy+WwBq2ILWTX/BcsiVsf8+Ly4ni3Gb1Aa2FK2jF3HlrPr2Q3sRnxWexO7md3CVrAfs1vZSraK3cZWs5+wNeyn7Hb2M9bEfs7WsjtYM7uTrWN3sfVsA7ub/YK1sHvYvew+1sp+ye5nv2Ib2QPsQfYQ28QeZo+wR9lm9hjbwh5nW9kT7En2FNvGnmbb2TNsB3uWPceeZzvZC2wXexGfLf+avcR+w3az37I97GW2l73C9rHfsf3s9+xV9gfWzv7I/sReYwfY6+wN9iY7yN5ib7M/s0PsL+wd9lfWwd5l77H32WH2N3aEfcCOsg/ZR+xjdgyfRn+KT5w72d/ZcfY5O8G+YF+yr9hJ9jX7hn3LTrF/sO/Y9/QjJXx/og++RZEkaaS+UrLUT0qR+kup0gBpoHSWpJUGSYOlIZIsDZWGScOlNGmENFI6WxolnSOdK50npUvnSxdIF0oZ0kXSxdIl0mjpUmmMdJk0VrpcGiddIekkvWSQjJJJMksWKVOySjbJLjkkp5QluSS3lC2NlyZIE6UcKVeaJF0p5Un50mTpKqlAmiJNlaZJhdIPpCJpulQszZBmSldLJdIs6Rrph9Js6UfStZJHmiOVSnOlMskr+aR5UrlUIVVK86UFUpW0UKqWaqRaaZFUJ/mlgFQvLZaWSA3SUmmZdJ20XLpeukG6UWqUbpJulm6RVkg/lm6VVkqrpNuk1dI=
*/