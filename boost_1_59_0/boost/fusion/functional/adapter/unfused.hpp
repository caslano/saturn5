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
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
*/