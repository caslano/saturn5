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
6VJaHOx4D6Ki+Tiv3+ZwTuIZJnVpkNQlw01zPClxavb/WB22Om9r2w0q8z/5drYTLsV0pUNTvnjVPcju46+5HnB9WJkl/D9R8qumXxP/RxJ/GynfJ6R8036T+DkYR6QkRinFbM9xoqL5nK0/puTEKrk/PkhQ/vgyYQppyNHGF5M8Ts203fttbtn2sDkH9LK5ds/Nf1XNeYH41Nna+uCh7ATqWEb8Hkuisj9k3bakU20ytKPuaa9R5XsmBd+T2eRhpM3+MUqTzjWSTne5RqlNSFSOTb+b01noa5TP7LhGqV4td8FAOV50lnj9NfHKCfMPXIfJ8Uzi1rZZvSVxVyxCfrEsLibu9dZxy/WRPedQ7XsevH+SzDzNNlCbjW3GS6Q5WpaVdMpYftp61EYini7nxjTCUlf+929zWuXa6v77VgHHVdnXUzXHzU6P5C5YTO6f7xKWKdeulni5w/zj2yWvjtTQ7EtqPVPaN0PD5R6uDPJv0v4YqQwyabnHLmGer/62lOa3yQkmWYeLZr76XRw13uI68RptjjcXpByC5H2N7jKuqaGIvK9BPFbDPxZyGyT+4fFMrbfVqzVyI3hf6sgRgtLWYTKnMYXGDvvrh/baSTvuZHXtWKK67R8uOu0fpXTG4HQ3ryvcZNv22Im8KhPLqVNJwkrylFY0L09jjLEpUcrl532PS1U5hynXf+7qOSzSmGxUF1PnH2Z+fXW+2nai/IP2ul7SkSrPSsYQVitta+Z0pMYkj1APkIW6l8rd/pFRSRScHCe15aytm9rrf1d5T0Lut9zk3tW7mKRJvWgNjRprR3rkmK29f5UxcK9KPG7S3lod1fbf3HjMjb/2nNf/zLbWvPax/W6W/aCO7Af/JL05xSW9SpufclzPPWAmFSbdR2pq9gn5e7hNmiNigXnW5+fIWLA5B+fLl2b78uxSnX6UdvfvCev4wxkn63yoWbD7+Gudfj9L+iV/lnRp99/wcLBp0zQadfZ77bjmtQ3qNE+uhWdK/XQpaU5/QmJiVESycoy24/yqbccxyvVX/mO97FtyTIlOpuA19XmepCtarjmMhOHKNZk5XVFjTcb4yHs/S3HXPa/Jebzgb8O5y3t/Evdiidu/lDZu30LUyc/yjhea+yO1XqhteRnk19s9954nUo1HytJyDDe3xbWSMoqsIzEVI51wWxnrXH3Yok0nI9InRyXGG2MlvWPvk940m+PbLG16pTy1bZX+Nvt9gPx7vnosbZd+ZCysTm7bZaazdoxp27bLEJ22yzCdtssRum2Xljp1TMorTOr6YKnrWWWkvNR2xNDIwjyfkzqlvR571HKdXtLqmO9fVuJRPxFg3/G+unW9lXNgiNqXIT4mNjxeU2+zJN6eUm8DpN6azPGmqhWiMG0zErdevdW8g6r/DqHjHdSH/Q6q/ru+f/93U/85Vd2OXV87tGzWJeeZv7pcmbm1d4O8d1Clbw36KX+3ecftg2K88oc5WAOPoyuewKb4IV5Db8IZWU95WU8x9JD13OB3TvgzlsNfZLkAg/R9gQhZrgS2keUO8buyeBh98B3sj9k4CI/iMDxmtb40WV8vnfVdlvRfwXr4AzbBH7ENXsVu+JPV+q7eY33fyPrOyvrOyfq+lfV9J+s7by4n6ROCMTrltITfVcOlGInLZLlSRaQ/h/TzYDn1uveOLHe6CN9axDPogd+gJ55FfzyHAfgt9sYLOAEv4hT8HmfiJZyPl3EVXsFM/BEP4FV8H3/Cr/EaXsLreA1/xrv4CzqTzl+xEt5ET7yFffE3HIW3cQ7ewcX4O67Gf+N6LF6UMczRCXdiCcwtR+n7gT465Vif31XDBuiJDTGvvofJch116nsdfuc=
*/