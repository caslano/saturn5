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