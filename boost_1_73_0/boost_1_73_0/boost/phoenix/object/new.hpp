/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OBJECT_NEW_HPP
#define BOOST_PHOENIX_OBJECT_NEW_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/object/detail/target.hpp>
#include <boost/phoenix/support/iterate.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#ifdef BOOST_PHOENIX_NO_VARIADIC_EXPRESSION
#   include <boost/phoenix/object/detail/cpp03/new_expr.hpp>
#else
BOOST_PHOENIX_DEFINE_EXPRESSION_VARARG(
    (boost)(phoenix)(new_)
  , (proto::terminal<detail::target<proto::_> >)
    (meta_grammar)
  , _
)
#endif

namespace boost { namespace phoenix
{
    struct new_eval
    {
        template <typename Sig>
        struct result;

#if defined(BOOST_PHOENIX_NO_VARIADIC_OBJECT)
        template <typename This, typename A0, typename Context>
        struct result<This(A0, Context)>
        {
            typedef typename detail::result_of::target<A0> target_type;
            typedef typename target_type::type * type;
        };

        template <typename Target, typename Context>
        typename detail::result_of::target<Target>::type *
        operator()(Target, Context const &) const
        {
            return new typename detail::result_of::target<Target>::type;
        }

        // Bring in the rest
        #include <boost/phoenix/object/detail/cpp03/new_eval.hpp>
#else
        // TODO:
#endif
    };

    template <typename Dummy>
    struct default_actions::when<rule::new_, Dummy>
        : call<new_eval, Dummy>
    {};

#if defined(BOOST_PHOENIX_NO_VARIADIC_OBJECT)
    template <typename T>
    inline
    typename expression::new_<detail::target<T> >::type const
    new_()
    {
        return
            expression::
                new_<detail::target<T> >::
                    make(detail::target<T>());
    }

    // Bring in the rest
    #include <boost/phoenix/object/detail/cpp03/new.hpp>
#else
    // TODO:
#endif
}}

#endif


/* new.hpp
ZAi80ETrGcou8MIJzCj60pkBhonDvVsi8f4pw5n62mwJGESPosb5LO/J2NhlRBy7FNDbFW+AesnEDWYGeuPpi24i8EejhYBa3NMagro+QaZaRA610KmPRq5VhQ7QzMQgX1lNNSVMEuXp9BKzRI1WAYrV66v5S/pAvhJWtmKpQa2ge9bjl8/MlJC0q78JU/duLaak+B6DKSZ0VmDq3j0CU2VPi0hWaal61Ey25WlSwAp7Ph4b1Jw1ZFNK1SiUtUhx8qZELix+BGKsfFfRiLV0PTqcHCsRCIsfgUem4VfhkpmEenyyRFsJJ11ViRe4cB+Z0w7tCCMU4rfNTmdTDE9E79Po5/5wNDjqjdCTBAv6aXDWPy43726qzFK5ancTI+WzYe9jf+e0d37+68lZBoA861VkYlmoYaGSS7Be9nTmrcRGeViPWEjdsQbHnJOxHr8srVbCMINUgR3/5p+ziR8mEk0ctvtaNKow1FzeOXln4rmxYWjExqnwZcD2lqqnbupedHc7HTJSuo1XjsWeRylG2QzNBEnPQy5GMDaAW28KYQbG2GiVAxx1RkqBDSk2hzlA3SyMHY+Dce81oCaePRMONX4LhU0o3drS5F8kgcpb4agtgonWs7N7B8SEogvvUhtxGn/rjdjl74Rm9pUG
*/