/*=============================================================================
    Copyright (c) 2006-2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_FUNCTIONAL_ADAPTER_UNFUSED_HPP_INCLUDED)
#if !defined(BOOST_PP_IS_ITERATING)

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>

#include <boost/utility/result_of.hpp>

#include <boost/config.hpp>

#include <boost/fusion/container/vector/vector.hpp>

#include <boost/fusion/functional/adapter/limits.hpp>
#include <boost/fusion/functional/adapter/detail/access.hpp>

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning (disable: 4512) // assignment operator could not be generated.
#endif

namespace boost { namespace fusion
{
    template <class Function, bool AllowNullary = true>
    class unfused;

    //----- ---- --- -- - -  -   -

    template <class Function> 
    class unfused<Function,true>
      : public unfused<Function,false>
    {
        typedef typename detail::qf_c<Function>::type function_c;
        typedef typename detail::qf<Function>::type function;
        typedef typename detail::call_param<Function>::type func_const_fwd_t;
      public:

        using unfused<Function,false>::operator();

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline explicit unfused(func_const_fwd_t f = function())
            : unfused<Function,false>(f)
        { }

        typedef typename boost::result_of<
            function_c(fusion::vector0<> &) >::type call_const_0_result;

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline call_const_0_result operator()() const
        {
            fusion::vector0<> arg;
            return this->fnc_transformed(arg);
        }

        typedef typename boost::result_of< 
            function(fusion::vector0<> &) >::type call_0_result;

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline call_0_result operator()()
        {
            fusion::vector0<> arg;
            return this->fnc_transformed(arg);
        }
    };

    template <class Function> class unfused<Function,false>
    {
      protected:
        Function fnc_transformed;
        typedef typename detail::qf_c<Function>::type function_c;
        typedef typename detail::qf<Function>::type function;
        typedef typename detail::call_param<Function>::type func_const_fwd_t;
      public:

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline explicit unfused(func_const_fwd_t f = function())
            : fnc_transformed(f)
        { }

        template <typename Sig>
        struct result;

        #define  BOOST_PP_FILENAME_1 \
            <boost/fusion/functional/adapter/unfused.hpp>
        #define  BOOST_PP_ITERATION_LIMITS \
            (1,BOOST_FUSION_UNFUSED_MAX_ARITY)
        #include BOOST_PP_ITERATE()
    };
}}

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

namespace boost 
{
#if !defined(BOOST_RESULT_OF_USE_DECLTYPE) || defined(BOOST_NO_CXX11_DECLTYPE)
    template<class F>
    struct result_of< boost::fusion::unfused<F> const () >
    {
        typedef typename boost::fusion::unfused<F>::call_const_0_result type;
    };
    template<class F>
    struct result_of< boost::fusion::unfused<F>() >
    {
        typedef typename boost::fusion::unfused<F>::call_0_result type;
    };
#endif
    template<class F>
    struct tr1_result_of< boost::fusion::unfused<F> const () >
    {
        typedef typename boost::fusion::unfused<F>::call_const_0_result type;
    };
    template<class F>
    struct tr1_result_of< boost::fusion::unfused<F>() >
    {
        typedef typename boost::fusion::unfused<F>::call_0_result type;
    };
}

#define BOOST_FUSION_FUNCTIONAL_ADAPTER_UNFUSED_HPP_INCLUDED
#else // defined(BOOST_PP_IS_ITERATING)
////////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
////////////////////////////////////////////////////////////////////////////////
#define N BOOST_PP_ITERATION()

        template <class Self, BOOST_PP_ENUM_PARAMS(N,typename T)>
        struct result< Self const (BOOST_PP_ENUM_PARAMS(N,T)) >
            : boost::result_of< function_c(
                BOOST_PP_CAT(fusion::vector,N)< BOOST_PP_ENUM_BINARY_PARAMS(N,
                    typename detail::mref<T,>::type BOOST_PP_INTERCEPT) > & )>
        { };

        template <class Self, BOOST_PP_ENUM_PARAMS(N,typename T)>
        struct result< Self(BOOST_PP_ENUM_PARAMS(N,T)) >
            : boost::result_of< function(
                BOOST_PP_CAT(fusion::vector,N)< BOOST_PP_ENUM_BINARY_PARAMS(N,
                    typename detail::mref<T,>::type BOOST_PP_INTERCEPT) > & )>
        { };

        template <BOOST_PP_ENUM_PARAMS(N,typename T)>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename boost::result_of<function_c(BOOST_PP_CAT(fusion::vector,N)
            <BOOST_PP_ENUM_BINARY_PARAMS(N,T,& BOOST_PP_INTERCEPT)> & )>::type
        operator()(BOOST_PP_ENUM_BINARY_PARAMS(N,T,& a)) const
        {
            BOOST_PP_CAT(fusion::vector,N)<
                  BOOST_PP_ENUM_BINARY_PARAMS(N,T,& BOOST_PP_INTERCEPT) >
                arg(BOOST_PP_ENUM_PARAMS(N,a));
            return this->fnc_transformed(arg);
        }

        template <BOOST_PP_ENUM_PARAMS(N,typename T)>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename boost::result_of<function(BOOST_PP_CAT(fusion::vector,N)
            <BOOST_PP_ENUM_BINARY_PARAMS(N,T,& BOOST_PP_INTERCEPT)> & )>::type
        operator()(BOOST_PP_ENUM_BINARY_PARAMS(N,T,& a)) 
        {
            BOOST_PP_CAT(fusion::vector,N)<
                  BOOST_PP_ENUM_BINARY_PARAMS(N,T,& BOOST_PP_INTERCEPT) >
                arg(BOOST_PP_ENUM_PARAMS(N,a));
            return this->fnc_transformed(arg);
        }
#undef N
#endif // defined(BOOST_PP_IS_ITERATING)
#endif


/* unfused.hpp
UibtD3kTj4iOF4AJZsnwSF96BgV9eEG8rWrHGaRTcFDPXELEp6gO7BI4E3XFrqmPSLlhzDCbhe38pdsArO2cfASWeog9/8j4h8BXHr5Cgq/05GITNOs666PRJvCVBLcEX0nQPakTKGMMu4TgK+TgYIO2MZQ7Nu8blu4NuBUpKpyOc5AHhnJVqM+tVw4M6WybOl0aKynDvo1xLHhkqA8zdPAWk2GfAd6SCQTZ4VfaQCGBFmzK1jZQmUmSHIcnMU0lIQ0N4NufBtL1EFy9B1Po7rOBwe2egcyOvGSQmWZXfzilZOhhaIk1jvhBhmFXnyF3roPDwdIjfEGXRgo6ssHT4kYhR66pimRiGDIE41kr5Ei3ycjDAI+cfTlaeBS/bQcTl58FFTgLX7RjMR30Yjrrxfx9VhZTfWPdimlFxcx5irL+orOW9d7OWtaNT8usS+uYdflllHU/ynqqnvV0PevmZ2TW3eqY9R2c9TEbZn2xnvUletYTTsqsv06vW9bRnPWzlPXGTlrWmztpWd/7u8z6wTpm/fallPUAyjpLz/oePetmx2TW7eqY9TDO+iSaHIU30LOO0bOuPi6z3jq4blmfaUdZv0BZv9tRy/qDjlrWi3+WWU+sY9aLOOuBlPUIPetb9Kw/qZZZN6lj1v046z+tmPW5DlrWvg5a1rf8KLNeMahuWXvbUtYvU9Yv6lkv0bP2/SSzHlXHrEs468GU
*/