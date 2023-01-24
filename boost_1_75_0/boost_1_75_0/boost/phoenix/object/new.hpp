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
WOs9p7G2KE2LEhanCIpSMHFKgqJUQsVpdIFTAonR6RbHzZiwxDGlIV+0qTXauZpaps3Ycx41QVqEqIWNr73YLKTtLI1x07bRwNc6x2SBol1Ex0CRdDnRDZzM2x0I6w5jZukh9BGZJWnd5syCqilZPMe4mQVzLwmBm708pPPjLzS+fmiBWHua4StJwSsUgHidHhON4rU5YN1QklpfklpXnIqI/wtZV1ItbMz6Ncn6LY011b9uinGDAhbNFvUgOg2A1Uchlx75AqFnJW+0OgxRdbFlFF44mmXEXBfSmTML5l4czlziiLuzrC21nvlYWnihbXxQI1vf18Y6IzamMAOzjgSsgRpLUxtKUzF3oIbSNFLpUGVAGXQ1lmc2lAHEGeK4hSBql+c00nbkaKrKxVeXgBeYoDbVQQvzwSgMXk6CtgMDjTVcuYncuAC1sOG8FPZlIN69Ye2hQbCOcWcLsBaZvKvoLjDzqBeQOBXEReNxZtUFOnPInWiW0aupgebkPEYzckYT1/xz7sDdDdUVkvVzb0tzL3NTfP0RMOzyI1hneFualSG7xqxpSiOVDlWGlYHVVJ5JCRAXMuengaDfRN8Fkb6HUjVtz0M87haQOxzWwthNbkKOU/EKarIZPTd7w5Wb0Vk3x3hwgIZyYwibOcEa2TgtaUeJOq32IiqtIxH+nDM5Jye3iGYx0ZaFerMDN+nMu4G16YNH1tp63sCu
*/