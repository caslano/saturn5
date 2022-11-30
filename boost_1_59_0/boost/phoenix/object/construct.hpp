/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OBJECT_CONSTRUCT_HPP
#define BOOST_PHOENIX_OBJECT_CONSTRUCT_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/object/detail/target.hpp>
#include <boost/phoenix/support/iterate.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#ifdef BOOST_PHOENIX_NO_VARIADIC_EXPRESSION
#   include <boost/phoenix/object/detail/cpp03/construct_expr.hpp>
#else
BOOST_PHOENIX_DEFINE_EXPRESSION_VARARG(
    (boost)(phoenix)(construct)
  , (proto::terminal<detail::target<proto::_> >)
    (meta_grammar)
  , _
)
#endif

namespace boost { namespace phoenix
{
    struct construct_eval
    {
        template <typename Sig>
        struct result;

#if defined(BOOST_PHOENIX_NO_VARIADIC_OBJECT)
        template <typename This, typename A0, typename Context>
        struct result<This(A0, Context)>
            : detail::result_of::target<A0>
        {
        };

        template <typename Target, typename Context>
        typename detail::result_of::target<Target>::type
        operator()(Target, Context const &) const
        {
            return typename detail::result_of::target<Target>::type();
        }

        // Bring in the rest
        #include <boost/phoenix/object/detail/cpp03/construct_eval.hpp>
#else
        // TODO:
#endif
    };

    template <typename Dummy>
    struct default_actions::when<rule::construct, Dummy>
        : call<construct_eval, Dummy>
    {};

#if defined(BOOST_PHOENIX_NO_VARIADIC_OBJECT)
    template <typename T>
    inline
    typename expression::construct<detail::target<T> >::type const
    construct()
    {
        return
            expression::
                construct<detail::target<T> >::
                    make(detail::target<T>());
    }

    // Bring in the rest
    #include <boost/phoenix/object/detail/cpp03/construct.hpp>
#else
    // TODO:
#endif
}}

#endif


/* construct.hpp
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
*/