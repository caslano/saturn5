/*=============================================================================
    Copyright (c) 2006-2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_FUNCTIONAL_ADAPTER_UNFUSED_TYPED_HPP_INCLUDED)
#if !defined(BOOST_PP_IS_ITERATING)

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>

#include <boost/config.hpp>

#include <boost/utility/result_of.hpp>

#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/fusion/container/vector/convert.hpp>

#include <boost/fusion/functional/adapter/limits.hpp>
#include <boost/fusion/functional/adapter/detail/access.hpp>

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning (disable: 4512) // assignment operator could not be generated.
#endif


namespace boost { namespace fusion
{

    template <class Function, class Sequence> class unfused_typed;

    //----- ---- --- -- - -  -   -

    namespace detail
    {
        template <class Derived, class Function, 
            class Sequence, long Arity>
        struct unfused_typed_impl;
    }

    template <class Function, class Sequence>
    class unfused_typed
        : public detail::unfused_typed_impl
          < unfused_typed<Function,Sequence>, Function, Sequence, 
            result_of::size<Sequence>::value > 
    {
        Function fnc_transformed;

        template <class D, class F, class S, long A>
        friend struct detail::unfused_typed_impl;

        typedef typename detail::call_param<Function>::type func_const_fwd_t;

    public:

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline explicit unfused_typed(func_const_fwd_t f = Function())
            : fnc_transformed(f)
        { }
    }; 

    #define  BOOST_PP_FILENAME_1 <boost/fusion/functional/adapter/unfused_typed.hpp>
    #define  BOOST_PP_ITERATION_LIMITS (0,BOOST_FUSION_UNFUSED_TYPED_MAX_ARITY)
    #include BOOST_PP_ITERATE() 

}}

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

namespace boost 
{
#if !defined(BOOST_RESULT_OF_USE_DECLTYPE) || defined(BOOST_NO_CXX11_DECLTYPE)
    template<class F, class Seq>
    struct result_of< boost::fusion::unfused_typed<F,Seq> const () >
        : boost::fusion::unfused_typed<F,Seq>::template result< 
            boost::fusion::unfused_typed<F,Seq> const () >
    { };
    template<class F, class Seq>
    struct result_of< boost::fusion::unfused_typed<F,Seq>() >
        : boost::fusion::unfused_typed<F,Seq>::template result< 
            boost::fusion::unfused_typed<F,Seq> () >
    { };
#endif
    template<class F, class Seq>
    struct tr1_result_of< boost::fusion::unfused_typed<F,Seq> const () >
        : boost::fusion::unfused_typed<F,Seq>::template result< 
            boost::fusion::unfused_typed<F,Seq> const () >
    { };
    template<class F, class Seq>
    struct tr1_result_of< boost::fusion::unfused_typed<F,Seq>() >
        : boost::fusion::unfused_typed<F,Seq>::template result< 
            boost::fusion::unfused_typed<F,Seq> () >
    { };
}


#define BOOST_FUSION_FUNCTIONAL_ADAPTER_UNFUSED_TYPED_HPP_INCLUDED
#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////
#define N BOOST_PP_ITERATION()

    namespace detail
    {

        template <class Derived, class Function, class Sequence>
        struct unfused_typed_impl<Derived,Function,Sequence,N>
        {
            typedef typename detail::qf_c<Function>::type function_c;
            typedef typename detail::qf<Function>::type function;
            typedef typename result_of::as_vector<Sequence>::type arg_vector_t;

        public:

#define M(z,i,s)                                                                \
    typename call_param<typename result_of::value_at_c<s,i>::type>::type a##i

            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            inline typename boost::result_of<
                function_c(arg_vector_t &) >::type
            operator()(BOOST_PP_ENUM(N,M,arg_vector_t)) const
            {
#if N > 0
                arg_vector_t arg(BOOST_PP_ENUM_PARAMS(N,a));
#else
                arg_vector_t arg;
#endif
                return static_cast<Derived const *>(this)->fnc_transformed(arg);
            }

            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            inline typename boost::result_of<
                function(arg_vector_t &) >::type 
            operator()(BOOST_PP_ENUM(N,M,arg_vector_t)) 
            {
#if N > 0
                arg_vector_t arg(BOOST_PP_ENUM_PARAMS(N,a));
#else
                arg_vector_t arg;
#endif
                return static_cast<Derived *>(this)->fnc_transformed(arg);
            }

#undef M

            template <typename Sig> struct result { typedef void type; };

            template <class Self BOOST_PP_ENUM_TRAILING_PARAMS(N,typename T)>
            struct result< Self const (BOOST_PP_ENUM_PARAMS(N,T)) >
                : boost::result_of< function_c(arg_vector_t &) > 
            { };

            template <class Self BOOST_PP_ENUM_TRAILING_PARAMS(N,typename T)>
            struct result< Self (BOOST_PP_ENUM_PARAMS(N,T)) >
                : boost::result_of< function(arg_vector_t &) >
            { };
        };

    } // namespace detail

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)
#endif


/* unfused_typed.hpp
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
*/