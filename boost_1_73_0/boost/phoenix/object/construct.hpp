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
m0H2CyfCuMa89z3G+k9roNyhkB3zxuwo89G8KHdktL0jlL7LM5nwuTXfev+q8CEWdLcf7F6zt2UH1VhY3Ky7Z8r9nEEbb0PQ91QYLwunVZlD4CfmQH+rdr5R8/q60MkZ42BsdQV1Xx8D++iH3XbDttEPr4wXleO2deBfGxi7M5vwfiVzUfm5MxaAHEspG6D5Hfp5eRvIm9Jsann4/C0wDyv7uwKyrwp9T7MC/BD812Izgn/Y
*/