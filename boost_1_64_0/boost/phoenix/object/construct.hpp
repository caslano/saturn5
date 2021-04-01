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
O+x3/G4nMKXa7iKSDkSaNkBPQwTO8ctQSS8bLxD8znt5BB9LBK/t/DrRW6bAjXRuRYxwFVxenr5BgnRxs6RbVnu4Ci3a0h6nUPKChCi/CaBVlLfiMDNit8PfcqmXam8wlgaxclilBxByzw8rxldKj//+Je7vkpfu3SLbbAI11iAadDHP2dUMjPVGnwU6mmMX7wxjBSZoyi9L+AmKUUx52+vxNsHSO/prsEXvw9PA3COhbRfxxKn4etAIyJC5Km9+5o1a8V+4zP+LrfQlKfW8IDQlyKDU7RNKjFix3RnVx3LhwSL6cP0luMxZ5swC3vVbswwg3I83O9p6yi/5Lp1fRVd35OSnfDEQi4wU2LvRMdg3d4vYp/fcDFG31cM3qidpfDjfOGZ87zMna71VBPUOavZU2OxO9TRtZgeNL8E9RqbPUMG3vNjHAuxeznqDECV6N8UBjtMk3NhCSrQTNp1UKNPI+lUy1n4E7x0F/iw8bzvwlnK0fwV12g7vi49d1p30ZZt3hWp0GEnd4uyXdupJLb72YMOQha8XNWWlRjeDRImx9TzFp/mIcQaCpQ==
*/