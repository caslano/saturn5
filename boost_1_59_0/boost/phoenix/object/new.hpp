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
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
*/