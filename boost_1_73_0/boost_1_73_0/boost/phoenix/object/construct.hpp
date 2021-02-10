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
yuBKxtct8XpKJf89d+/u2ol82xIyFa7fVqBGcy8RSThLb91YCvjb9yYySORUuImYymQSe1fwxQtEOpdi5vlSHJ2c/j4Yvm+J27k3mSOQ+3Apknm49Kdi7t5IEcuJ9G4YRuTGqQhn0B2AT70kBYDL1AuDNowtRSrjRYIwcHjXT0Lh3rie717BQG4q5mkaJYc7O5Nl7AP2O9NwkuxM9PTb83RhZvI7ILFw70UYpSINxTKRLYEtW2IRTr0Z/gaCQGG0vPK9ZN7KsIGhgulOGItE+j7Cgn6eTBhtKc4VeVrYTESAsZfiryQMEhzqdh4ucg2BjghltowDGAjoAI2mIZC5JZbBVMbUmGauh1A0JQLXLk2G71SEASAjGr1zMThviCs38ZKW+HUw+vnk00j82js76w1Hv4uTd6I3/B2B/X0wPIal92CwWMi7KJYJDB4LbxH5npyqMb/fZ2fjBy+Y+MupFI1ExjcyHicyXUbteSOreZ2kU9+7as/fbmzsPBfvlsEEOUPNvzeZyChNhCtGR6ewJEEgqZrmLibLJAWyRyGwlzM4vdnD2cDvg2Yb5IPa0uK4COoauBE6Taex2OIuV+7ks4TVdNI5sBkQd3gyArqksTtB8s7CmJd0AtQJ0k1az1j+uZRJ2mTO1RB4diAr
*/