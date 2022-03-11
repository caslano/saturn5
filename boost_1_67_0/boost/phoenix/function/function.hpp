/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Eric Niebler
    Copyright (c) 2015 John Fletcher

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_FUNCTION_FUNCTION_HPP
#define BOOST_PHOENIX_FUNCTION_FUNCTION_HPP

#include <boost/phoenix/config.hpp>
#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/detail/function_eval.hpp>
#include <boost/utility/result_of.hpp>

namespace boost { namespace phoenix
{
    /////////////////////////////////////////////////////////////////////////////
    // Functions
    /////////////////////////////////////////////////////////////////////////////

    namespace expression
    {
#if defined(BOOST_PHOENIX_NO_VARIADIC_FUNCTION)
        template <typename F, BOOST_PHOENIX_typename_A_void(BOOST_PHOENIX_ACTOR_LIMIT)>
        struct function
            : detail::expression::function_eval<F, BOOST_PHOENIX_A(BOOST_PHOENIX_ACTOR_LIMIT)>
        {};
#else
      // TODO:
#endif
    }

    // functor which returns our lazy function call extension
    template<typename F>
    struct function
    {
        BOOST_CONSTEXPR function()
          : f()
        {}

        BOOST_CONSTEXPR function(F f_)
          : f(f_)
        {}

        template <typename Sig>
        struct result;

#if defined(BOOST_PHOENIX_NO_VARIADIC_FUNCTION)
        typename detail::expression::function_eval<F>::type const
        operator()() const
        {
            return detail::expression::function_eval<F>::make(f);
        }

        // Bring in the rest
        #include <boost/phoenix/function/detail/cpp03/function_operator.hpp>

      // Solves the result problem for F(X)
        template <typename This, typename A0>
        struct result<This(A0)>
          : detail::expression::function_eval<F,
            typename boost::remove_reference<A0>::type>
        {};
      // Solves the result problem for F(X,Y)
        template <typename This, typename A0, typename A1>
        struct result<This(A0,A1)>
          : detail::expression::function_eval<F,
            typename boost::remove_reference<A0>::type,
            typename boost::remove_reference<A1>::type>
        {};
      // Solves the result problem for F(X,Y,Z)
        template <typename This, typename A0, typename A1, typename A2>
        struct result<This(A0,A1,A2)>
          : detail::expression::function_eval<F,
            typename boost::remove_reference<A0>::type,
            typename boost::remove_reference<A1>::type,
            typename boost::remove_reference<A2>::type>
        {};

      // Solves the result problem for F(W,X,Y,Z)
      template <typename This, typename A0, typename A1,
                               typename A2, typename A3>
      struct result<This(A0,A1,A2,A3)>
          : detail::expression::function_eval<F,
            typename boost::remove_reference<A0>::type,
            typename boost::remove_reference<A1>::type,
            typename boost::remove_reference<A2>::type,
            typename boost::remove_reference<A3>::type>
         {};

      // Solves the result problem for F(V,W,X,Y,Z)
      template <typename This, typename A0, typename A1,
                typename A2, typename A3,typename A4>
      struct result<This(A0,A1,A2,A3,A4)>
          : detail::expression::function_eval<F,
            typename boost::remove_reference<A0>::type,
            typename boost::remove_reference<A1>::type,
            typename boost::remove_reference<A2>::type,
            typename boost::remove_reference<A3>::type,
            typename boost::remove_reference<A4>::type>
       {};

      // Solves the result problem for F(U,V,W,X,Y,Z)
      template <typename This, typename A0, typename A1,
                typename A2, typename A3,typename A4,
                typename A5>
      struct result<This(A0,A1,A2,A3,A4,A5)>
          : detail::expression::function_eval<F,
            typename boost::remove_reference<A0>::type,
            typename boost::remove_reference<A1>::type,
            typename boost::remove_reference<A2>::type,
            typename boost::remove_reference<A3>::type,
            typename boost::remove_reference<A4>::type,
            typename boost::remove_reference<A5>::type>
       {};

      // Solves the result problem for F(T,U,V,W,X,Y,Z)
      template <typename This, typename A0, typename A1,
                typename A2, typename A3,typename A4,
                typename A5, typename A6>
      struct result<This(A0,A1,A2,A3,A4,A5,A6)>
          : detail::expression::function_eval<F,
            typename boost::remove_reference<A0>::type,
            typename boost::remove_reference<A1>::type,
            typename boost::remove_reference<A2>::type,
            typename boost::remove_reference<A3>::type,
            typename boost::remove_reference<A4>::type,
            typename boost::remove_reference<A5>::type,
            typename boost::remove_reference<A6>::type>
       {};
#else
      // TODO:
#endif

        F f;
    };
}

    template<typename F>
    struct result_of<phoenix::function<F>()>
      : phoenix::detail::expression::function_eval<F>
    {};

}

#endif


/* function.hpp
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
*/