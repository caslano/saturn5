
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_AUX_FULL_LAMBDA_HPP_INCLUDED
#define BOOST_MPL_AUX_FULL_LAMBDA_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/lambda_fwd.hpp>
#   include <boost/mpl/bind_fwd.hpp>
#   include <boost/mpl/protect.hpp>
#   include <boost/mpl/quote.hpp>
#   include <boost/mpl/arg.hpp>
#   include <boost/mpl/bool.hpp>
#   include <boost/mpl/int_fwd.hpp>
#   include <boost/mpl/aux_/template_arity.hpp>
#   include <boost/mpl/aux_/na_spec.hpp>
#   include <boost/mpl/aux_/config/ttp.hpp>
#   if defined(BOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING)
#       include <boost/mpl/if.hpp>
#   endif
#endif

#include <boost/mpl/aux_/lambda_arity_param.hpp>
#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER full_lambda.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/arity.hpp>
#   include <boost/mpl/aux_/preprocessor/default_params.hpp>
#   include <boost/mpl/aux_/preprocessor/params.hpp>
#   include <boost/mpl/aux_/preprocessor/enum.hpp>
#   include <boost/mpl/aux_/preprocessor/repeat.hpp>
#   include <boost/mpl/aux_/config/dmc_ambiguous_ctps.hpp>

#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/comma_if.hpp>
#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>

namespace boost { namespace mpl {

// local macros, #undef-ined at the end of the header
#   define AUX778076_LAMBDA_PARAMS(i_, param) \
    BOOST_MPL_PP_PARAMS(i_, param) \
    /**/

#   define AUX778076_BIND_PARAMS(param) \
    BOOST_MPL_PP_PARAMS( \
          BOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        , param \
        ) \
    /**/

#   define AUX778076_BIND_N_PARAMS(i_, param) \
    BOOST_PP_COMMA_IF(i_) \
    BOOST_MPL_PP_PARAMS(i_, param) \
    /**/

#   define AUX778076_ARITY_PARAM(param) \
    BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(param) \
    /**/


#define n_ BOOST_MPL_LIMIT_METAFUNCTION_ARITY
namespace aux {

template<
      BOOST_MPL_PP_DEFAULT_PARAMS(n_,bool C,false)
    >
struct lambda_or
    : true_
{
};

template<>
struct lambda_or< BOOST_MPL_PP_ENUM(n_,false) >
    : false_
{
};

} // namespace aux
#undef n_

template<
      typename T
    , typename Tag
    AUX778076_ARITY_PARAM(typename Arity)
    >
struct lambda
{
    typedef false_ is_le;
    typedef T result_;
    typedef T type;
};

template<
      typename T
    >
struct is_lambda_expression
    : lambda<T>::is_le
{
};


template< int N, typename Tag >
struct lambda< arg<N>,Tag AUX778076_ARITY_PARAM(int_<-1>) >
{
    typedef true_ is_le;
    typedef mpl::arg<N> result_; // qualified for the sake of MIPSpro 7.41
    typedef mpl::protect<result_> type; 
};


#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, <boost/mpl/aux_/full_lambda.hpp>))
#include BOOST_PP_ITERATE()

/// special case for 'protect'
template< typename T, typename Tag >
struct lambda< mpl::protect<T>,Tag AUX778076_ARITY_PARAM(int_<1>) >
{
    typedef false_ is_le;
    typedef mpl::protect<T> result_;
    typedef result_ type;
};

/// specializations for the main 'bind' form
template<
      typename F, AUX778076_BIND_PARAMS(typename T)
    , typename Tag
    >
struct lambda<
          bind<F,AUX778076_BIND_PARAMS(T)>
        , Tag
        AUX778076_ARITY_PARAM(int_<BOOST_PP_INC(BOOST_MPL_LIMIT_METAFUNCTION_ARITY)>)
        >
{
    typedef false_ is_le;
    typedef bind<F, AUX778076_BIND_PARAMS(T)> result_;
    typedef result_ type;
};


#if defined(BOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING)

template<
      typename F
    , typename Tag1
    , typename Tag2
    , typename Arity
    >
struct lambda<
          lambda<F,Tag1,Arity>
        , Tag2
        , int_<3>
        >
{
    typedef lambda< F,Tag2 > l1;
    typedef lambda< Tag1,Tag2 > l2;

    typedef typename l1::is_le is_le;
    typedef bind1< quote1<aux::template_arity>, typename l1::result_ > arity_;
    typedef lambda< typename if_<is_le,arity_,Arity>::type,Tag2 > l3;
    
    typedef aux::le_result3<is_le, Tag2, mpl::lambda, l1, l2, l3> le_result_;
    typedef typename le_result_::result_ result_;
    typedef typename le_result_::type type;
};

#elif !defined(BOOST_MPL_CFG_DMC_AMBIGUOUS_CTPS)

/// workaround for MWCW 8.3+/EDG < 303, leads to ambiguity on Digital Mars
template<
      typename F, typename Tag1, typename Tag2
    >
struct lambda<
          lambda< F,Tag1 >
        , Tag2
        >
{
    typedef lambda< F,Tag2 > l1;
    typedef lambda< Tag1,Tag2 > l2;
    
    typedef typename l1::is_le is_le;
    typedef aux::le_result2<is_le, Tag2, mpl::lambda, l1, l2> le_result_;
    typedef typename le_result_::result_ result_;
    typedef typename le_result_::type type;
};

#endif

#   undef AUX778076_ARITY_PARAM
#   undef AUX778076_BIND_N_PARAMS
#   undef AUX778076_BIND_PARAMS
#   undef AUX778076_LAMBDA_PARAMS

#if !defined(BOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING)
BOOST_MPL_AUX_NA_SPEC(2, lambda)
#else
BOOST_MPL_AUX_NA_SPEC2(2, 3, lambda)
#endif

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_AUX_FULL_LAMBDA_HPP_INCLUDED

///// iteration, depth == 1

// For gcc 4.4 compatability, we must include the
// BOOST_PP_ITERATION_DEPTH test inside an #else clause.
#else // BOOST_PP_IS_ITERATING
#if BOOST_PP_ITERATION_DEPTH() == 1
#define i_ BOOST_PP_FRAME_ITERATION(1)

#if i_ > 0

namespace aux {

#   define AUX778076_RESULT(unused, i_, T) \
    BOOST_PP_COMMA_IF(i_) \
    typename BOOST_PP_CAT(T, BOOST_PP_INC(i_))::result_ \
    /**/

#   define AUX778076_TYPE(unused, i_, T) \
    BOOST_PP_COMMA_IF(i_) \
    typename BOOST_PP_CAT(T, BOOST_PP_INC(i_))::type \
    /**/

template<
      typename IsLE, typename Tag
    , template< AUX778076_LAMBDA_PARAMS(i_, typename P) > class F
    , AUX778076_LAMBDA_PARAMS(i_, typename L)
    >
struct BOOST_PP_CAT(le_result,i_)
{
    typedef F<
          BOOST_MPL_PP_REPEAT(i_, AUX778076_TYPE, L)
        > result_;
    
    typedef result_ type;
};

template<
      typename Tag
    , template< AUX778076_LAMBDA_PARAMS(i_, typename P) > class F
    , AUX778076_LAMBDA_PARAMS(i_, typename L)
    >
struct BOOST_PP_CAT(le_result,i_)< true_,Tag,F,AUX778076_LAMBDA_PARAMS(i_, L) >
{
    typedef BOOST_PP_CAT(bind,i_)<
          BOOST_PP_CAT(quote,i_)<F,Tag>
        , BOOST_MPL_PP_REPEAT(i_, AUX778076_RESULT, L)
        > result_;

    typedef mpl::protect<result_> type;
};

#   undef AUX778076_TYPE
#   undef AUX778076_RESULT

} // namespace aux


#   define AUX778076_LAMBDA_TYPEDEF(unused, i_, T) \
    typedef lambda< BOOST_PP_CAT(T, BOOST_PP_INC(i_)), Tag > \
        BOOST_PP_CAT(l,BOOST_PP_INC(i_)); \
/**/

#   define AUX778076_IS_LE_TYPEDEF(unused, i_, unused2) \
    typedef typename BOOST_PP_CAT(l,BOOST_PP_INC(i_))::is_le \
        BOOST_PP_CAT(is_le,BOOST_PP_INC(i_)); \
/**/

#   define AUX778076_IS_LAMBDA_EXPR(unused, i_, unused2) \
    BOOST_PP_COMMA_IF(i_) \
    BOOST_PP_CAT(is_le,BOOST_PP_INC(i_))::value \
/**/

template<
      template< AUX778076_LAMBDA_PARAMS(i_, typename P) > class F
    , AUX778076_LAMBDA_PARAMS(i_, typename T)
    , typename Tag
    >
struct lambda< 
          F<AUX778076_LAMBDA_PARAMS(i_, T)>
        , Tag
        AUX778076_ARITY_PARAM(int_<i_>)
        >
{
    BOOST_MPL_PP_REPEAT(i_, AUX778076_LAMBDA_TYPEDEF, T)
    BOOST_MPL_PP_REPEAT(i_, AUX778076_IS_LE_TYPEDEF, unused)

    typedef typename aux::lambda_or<
          BOOST_MPL_PP_REPEAT(i_, AUX778076_IS_LAMBDA_EXPR, unused)
        >::type is_le;

    typedef aux::BOOST_PP_CAT(le_result,i_)<
          is_le, Tag, F, AUX778076_LAMBDA_PARAMS(i_, l)
        > le_result_;
    
    typedef typename le_result_::result_ result_;
    typedef typename le_result_::type type;
};


#   undef AUX778076_IS_LAMBDA_EXPR
#   undef AUX778076_IS_LE_TYPEDEF
#   undef AUX778076_LAMBDA_TYPEDEF

#endif // i_ > 0

template<
      typename F AUX778076_BIND_N_PARAMS(i_, typename T)
    , typename Tag
    >
struct lambda<
          BOOST_PP_CAT(bind,i_)<F AUX778076_BIND_N_PARAMS(i_, T)>
        , Tag
        AUX778076_ARITY_PARAM(int_<BOOST_PP_INC(i_)>)
        >
{
    typedef false_ is_le;
    typedef BOOST_PP_CAT(bind,i_)<
          F
        AUX778076_BIND_N_PARAMS(i_, T)
        > result_;
        
    typedef result_ type;
};

#undef i_
#endif // BOOST_PP_ITERATION_DEPTH()
#endif // BOOST_PP_IS_ITERATING

/* full_lambda.hpp
AtbJfGWwar7Sz9ktlh2kIsJrKnWnHyb5rh3g4xtbTW1oEb5hKr7ABlzCTHxaRSGGVrJnSGbnf5y87hNMXswkxtO8yyss511dzvn8jzN5oSJYSSXFe+KA5bwX9/PxDmbz4sp74ncVFK/Net5gTt53jzF5oZp+NM27qNxy3pR9fLy1R5m8dsybc4DiLdtvOe/RvZz+HzYvFHi7U07xPtpnOe/TMs717xEmLxTCm0TzzrOeN56T98BhJi8Uytuwn+Ldttdy3pI9fLw/HmLyQjnEa/so3rtllvN+V8oZ/8/mBbfHSJp3qvW80Zy8Ow4yeaHg3uq9FO8neyznzSnhnP9WMXmhQOXFMor3RqkJXr74/92c8f8ENw3hvgOZCh1i87UQ3F7nsWuYnHNhx259p0d87T1cmM4dhU4qlU8aLp/kwKkMxGU2mpynyQulUzXulPhO1Xie+J9izvifSpB3HpL3N5K8X16VRAmXRRkiyfsmqTZrmHIy2Jcc5vgnc/JnVXjzTST+gTJ/hMz/Aq7EQwqrFrzDFiFxN+NRPMfzeGsXnzynDxBPXoPU+66OVL3Ecs1p1xtiAaR+av1KGGLrsfy65/mT+q4F5DzcEuvh53rn9Sd1V9esVIZ2s+55/UhV27iV7KHtV2z9/Qwp4sx/KdeMj/9e0Rsf0n38KJU9Pqbvsl6euYWc+S/7NfKM0ZVHet4VK9jypBZZL8+anXzytO3TyLP4sp480rj823K2PHmF1stTWsAZ/7lXI0/GJT15pPfHn0Oepp3Wy3N9B58847Ty1LTpySOZul+9zZbnPwXWy/Msn0+e5DKNPPdb9eTpTeoWv/cWW56In0GeyZzyZO0h9uKhZC/ue+3FgFY9Oy7ZwdwULJd9czlsbon/bDGwLakpim2pazGwLbNTFNuytcXAtjhSFNvyxxYD2/LvZWzbUpHv696b9X/kcfo/Spn1G27S9Rv65rPqN3D6vzj53CVMvrXFFN+7n1nDt2E75/7HbiZfoqr+RZ41fHe2ce5/sPnWFlF8Y5l8fPZ/G6f9Lwa8MIQXLCyJDEoUTyXYcEFc5Y3I386oZ8LFc2wrH49/sZQx1+2aJcWTTVOFo4xR1ZuzY7/7ql7iws/stpx0nAjx4+Uwb4TZrW2+I8xMrn9yOdc/u9TrH4i/pvnH6fJvzQN+YvOm0yIM9iWCSf3PyZ9V9Fz8HdsJP0Q8rL1E8Sdt9c3PHf+Zw47/LOyRv3ujj5K/u9kjxPSx59P5uw25PPm73PE/W9jxP4VUQGcPPpxf3BPwJSagmfxnNl/uTiM+Pw3fxzkcfCbGZ65gND6DlIjNBwXA+SfEmQbzkjrIhH+87o05dZBYHrcUKYETz4LxWJ2tfBsufTsUf5uHvhXmLXPeRDfent8kND0ciOZhqg/0J2bZW9Rj+f9+k8OFHC0AgENLrD0NeFNFtjdNSgME0pRS+rCwES4uSF0rYT/LtvD4KVC0YFoqRbciKGiIiiDJUqX8pinES7AiKCiC8PYp+IN1RQVBKYJAFQVZPhbEp7iiDga1iGJZsHnnnJl7c9P0J/WD7xt6M3fuzJkzZ86cc2bmnCjBrA3jseHRVsejYVUjeq6SWqLnH5UrSc+G1uGbtKoRvejga4qex7UKYFvuvwRav/+ysiX4Yul5y6NXlp7fXRofPadxOL0A56woei4RFHsLUuypS0TPI7S3KeJtB3z7HrwlitWTMAWUxBM627Dnhpb9ulQHWtc44h6fi2z3kuYczgp/C/tZzyeEGRc9pafhWUjuceEP/CQkvzS3ajeFd1LHqEOg9ftoccF3devwzV8RA99zrcHnXtoKfG04fz+/Mr7z98ceF8elL3iuFet1r6j1GqOKctSKI/h79dLFW0uaFZDaeN74I3985437cIBzAeBsIQ9nRcnDvaLv41K8ErqSG5ztge8TOfhcWK6vbN6u30b/z/44/T9XxYPvpTp8n96nw/foytbxHRe8kyrig/fNx+KBt0pPH+/r4H3Kf6Xo4xVffPSR+Fgb6WNZI/p4X0cfxyuuFH38sDg+fI9aHg++V+vwnbdHh+8/Vlwh+hgSJ7xPBqPcs1iadM+yeJOAV8SKArCV3ay/Xsyf4Yvj/nYb1s/5i+LTV44t08lJHP4uUfAnMmOlzvfXvsXNwdlW/X9hnPr/slb1/+GVev1/8ZXR/xfGJ388qejcuerljwIhYeShhDH5fCd+1F1921O8TcO3w88LedpfY12P0nOKkEXU300LHTmLWhQ62nr+YUFL40FXvjLo/MOj1OFB0OE/U4ioak2kquYilRO69OBPQqTympWeSj177JbOMf775i5s7fxnvP6/5rfu/zJAUPcEqLvjfUCbsgJ1cEfNoGFlbnRw75Z0J5C/XNCEG0sNn1eP1OGzbzQ+syP3n+bpGEg64DMD8Tk0xsXRrQFuMO5p4MFX07RQbRR8FT4xkNugUjkZg+P45lLk1UPs/z7qxG8XHWJH4DFYKtsBz/+6iSKvJisjynalUvy+RE9XDHNaMqhc7ustVIplGUOtekbjNZl8ihcKophpTp+w7F/py5cctaHuFAsw1GU7BUC1bEe7eyhxO54KwCViN9t4zsYb8WBYqzIM2kpt3EJtjAGqkH1l6ZLnv3GlwTYOR9rYFGcbQ87bqPMCFxRQCn7S8AyfT4ST3WiKB8dIxxbnS59C+hISg/QjpL9Ai0MgjYRUAGm8Lz/a3+K5PN14ZkWP59CI/89y3fywA2gyjmd+rP/PJXw8veJK5AMG9UKGGM98A+GtlK7m9afx7KN8zDod7MQDgX3MEg7SePaF8UwaQ+OZCiRgJ1QnetIQ1VN85XJWqvd2GM9MGk+nkqReUkgvUpwIjp2EawzSByhl8xpMEmM/2MghF3sQf93+I/3KcNT0P+Axj/EmBYdhRNEaNgyL8YHtBa1Z/WuQlLBFq385D/CZiSMswn12U4oQVxmcR9CTaDkVWzZiWzPqqK109stv8OtUnYDjW/iFkVk7sGcTEiV24JwodUjL92N+1k/NQPrUj0Qm+QLFgkzyefyPciKToc0cWmnTfD7RyN9ZOqQMGvcm/J2lw6hkRPk7q3tYRzzNMoM9LN/Piee4IJ7DTTADpAa8YnsSmMF8EYb5cG0nNQzz+7UaM/hgVGfce0pXRpXt4MzAyCdq4SCgLu/NnBlYJM8wjFbqwTHz1XzvCEO5OT1hrk5cCnM1HOpCB65Cll00VxPpOBPeW7nZmEKXfUUTGHuZas+i2q/lbMAsgf7XTRnuoXAtB1jlZRN9PClk47BhBfhxMv+4mD4eh8FVfQ8PlTx5+o/X4Mfzy5KVem/3nHcx7KgnxW2ASWe/2FliJztZCR6oHvjq4P/YoqGz8QZmUQP38QbyJM8U3sA6DEmKzfhqvkJuxTHgWkrcqgvnVhbOrRK3CwwAm/o1bONBUA+xgjv5PYKc9ViVp72jttDJlhhSmmVjcx9uko19U5kvfQfpHKR6SGxJvnQW0nlI/1kSiXH3u/z1ncw577mhkZ++AMZgL8ULWM3668uaE6N8wBdZUQvZssW0xBZAC/nI+Kdyl1Y5l7zJZEep8ThOsrdO2KRQP1+4g0cWQ0X3zGEIn4U3gEWkD+eE4IjhbO3nOkXklrIrfb/3jr+pXeI33T3ipntTOtVri3TRfaBr9/Ou+cPUtVTetdyvoWu9sGvo6D41OMrD+n1NfeoFfVIOYMbE07o+zZ3TYp8i/ZmqiwePoSMj9xUx3GT0fcXJidp9RcGxlBOCZyWjn0YS/pvgWckw5qlRY57rjRUIK2RXouYGIFnIhHvY4ws52/pcbHofwwJ4W4699bYNb6XhV7TsAQYTARHIu524xLE00N4wICWFV/2Qr1gVMvbSbQhO8kAtfQO+TPipLMdpVTQ+AG2yulSMU8pO/JWmXA+kr5xKmnY2R62jptCpnGeWBmIA6fvpc8LIOLxFuvIXk/4WqcvdAzq74PQ1sI759prQD/LiTZIW9pL6i9cgC1nObpskMEDjt8NLl/sJ41FX6XBUHAdZweWxUoz/888e110+XapdPn0/MLJuQkmUkW3nbG3OvXH/b+HwPv9M+F+Tbf3l8MsZDHrgD9JopwV8DE5KXI78Jw8xO3wo6clBLK3Ua76zDK6f8KIoZWvusxKCwTL6LQoZXfVUqExfyKS0cw+AsaFPC4Or8CUIHEMpBJdrVg8EbSGCxi69IOEH7dQKinkFZrVVutwZXEjPeHFSeQP7AiwBb5sblXln2eaPbBJ51qJS7KbNkuZba4insYg+ts7xETv+Hw3nbfT//VCc/r/n6S4yFssW3yNlicrH3iTWoyEcDiWyaySdj+M1s1tQ6jX4XsrTze+JRv38dhobz2+XUZvfF3FeslWzdKxZyKUV8kyjNk0jbOy7ck4iiomTiM8UJZryrwy0YJaSI4OItvHgbk3bmLpbk06nDxHSKUmm1ooB6AqrQM4iqRTWWqvvYqq3A8qnVn+aEQWQdtaKt8iTceQliJH+/6E8q9X/Gnrs+InfYU5nAf+vQLQCMDOnRpz+syBf5LZX0pAc9cEInK6bkQqXySa8w8s8/yupfesYuRgrcjpFLs/CB2eJI4pLvF4rMCIcDpRh7/yHTUOQKMh2PC9JZ66jbiVYK45wActaUUsPSdaKGnpI5mdGQf+x+iUo7PqX2ruXKnS9s7reU3v3RIXWu2To3VQKhcFdwDhdy/VdW/N3rWspMV1LjbNrWy/Edu0U4OxMUQKNZgYbfikcPpOHd9w9ci4z7U1RyyeOD66U6zDEM5vxoZbbThnhUZxmqNudiFwB6FjCqvYFy+HzX+Bz5RBQMg4XG42/lslHcegqZDLrrZRR+g0sk08ZJBVyqOIzzFwpnzao/di18r3N2Bmrn+6dV8gYaNsJH9RRvPkHwyoSk2DtzYOWT+6JgBjYScVZEr97PZON+8qGDx72PizRAMpC8u/yFT1X0P2T01SgjMlf00M5e+ZreouuSZj1G3rG4OzsCXh21LKznSJ4UvG6KYIlA8ze3DM/IOhbOSyht7WXCeNFPwrZtO+1XKNvj0fZozSwcztw+YMuY+Bxdjf8ihrhXVVvvETDPBMHTG3bckGryAQY4fhi1+yIVK+cR5jYeUsK9gVDM7MbT1G/DuLzS1/S82F8Xs/zj+Jzly+pv5ctEfDVNtn3uv5ylIufeoWN5xDHvHcGranE5aLWVOSEsKbW/xzL31/w6fjn6ih/DlUx/hw2Rfw5XGS33a/jnTLwzr7IO6sTNN4pVFrgnVvmcN7Z3sh5pwFZ3Ujz4BXoncF/mC+2mpuad6cKDwX96zTXBdXk6UGd/ZrrguoELYC7rqDRta9DI/cLmG1CbqDq+ZlFE1zYPMCZ52TB5yS1VLtIPHiRY9bxAnKsQOvtWhmxhbvNsEp4EpTP0QH6Gwds0pkUyB+MEd6t/i3YpVJuQxgD71TujArmmQW/hlGoFK10cH0kCR52iL+xizcdQUh8OdmqKhd2p1sqLCpxvSOp0B9ar0HfKYqTVQv/BxktQL8PYP+CZewHwG+DCTH4ahqT58WYqLZ3DfUAeBaAp9SJ6m0qru0sfQGxXsxNQVRPcHKL/aFCF1YKSM8rYr0jsKZGIBM5aU1iGsRQLtcgk4NSAPB+1v9VABhFzcG5PTRMt1OqxObGEW0dBIAXzNcBnO46pwJ873wN4P9yfWtEn1YTnCWuXI0s/rZOA/aqGGB7xA/s55tt6lfcm9Y7gAUxWWjmvuKOeJfYFONdoop7lxh0bqwUcx50lF4kXh0l/1TFyD+bjDpvZWtcjb2V9QUdLhPBisg/WZqt/rvZfA6vFGrKMn42N3kbyvjKAXJjj9ayOR5UbJWP0Y/JAC7P2RP4X9lut0ts2FGbVDK+BMhhaJFygP377ynoIwzbhFaOfmBDDA3U3Il1w9owh21+MUUot7sOcXQKTjiQbXmePIdVq4xw0nRihJtiGGEVZ4Q//hilXGj6hfnxKHt5U+byu++9FN5ATG9klLV8bF0h+c+tRPWUvfNQOKwK25+4ooTtFuNJ7NYp35Ym7PXs9D2RwwNs38iz+sMDwFGDY82FbOhDfKSWCmVmIZ/L3A3hPLOjVqnzNRjR1ypb5bZKvgaDN2UCqLqH2PNF8HNBmdXrDOVCEW93tzU4qgFeBMULz4384F2oN5lfG9p5rhFn5aGQixcyoFkJz9CrZ/X03gn23ttsPENOzxl7dCiwR9sfsiL7X9N0CodYe/LkbP3Ckx5ch3oEatjXz+IIyRWGwYEGWn58NRd99R2tS/rAT+ubVWefyZfC8qrj8Ee4IksMjhbK9iQLe/F1m+SbZ5H2V+YmcvXf6sdz6spoO14ocz0Ouc5w17I526UzqD763sVykrViH58oqcFxlkL2s8UqasB/Z16E/8azMOhnZ9bTN076xr+CW4ZX4O6QZhIml0mo7pdxw2Y6KfyvJ8CszSbDsXIwMFWWAQjnALJ35hpRHfHt90CJXDZmg03Clc/OixVFipno/fSNZA3ONuiWEMRphPEhimkUG6aRapbVaPPJLFX9++l8aR2kjoDFNEhvQJIMJvEvwajS+wbn89ukCRiYcX6/4FQZt8D65NTNu3pDAeQrlmr0W2jCQ/bhw1R0VE5d+clJ0EK468/Xb9TiX27RzVdz7Gx58250j0hkMvbsvpF16mxRDMqtZmWovShCmP2nRRFms+evvqnRyUunpMYcFsVOTUK68e7YUwcVcr0U7QuSJKRlMziJzhEbWQ+qLhOf8FuR1+FHBpjEK4oNJK7jTQcnMdl0skQdUXbKZJQBTkoM2mvyn/SY4T3ariVHTYBL5bAq7UVmDzNGSKnwmAWPm/jjRHh8mT864RG1MEct/Bgo5FjHEWDyZcBJd/JCmQqHxXEhUCoXB4rl8rdpMSmQsx21+TtMfGEpDWwlPSA4PwG0kKW8wGRIBcGHEnL2zOkXlv071+VL8L0cknFKh3qiUBlKx1UDp0SoM9Qvh7BDMo4XNItOJn01DaAtzvkDfH+Yf58bSoN6c0PJKI2HOkAtuSETfJur0DoG6CbL2cszNLRKyofslQqrJIaGqKHH3bSA0GjG7JOlQUsZkHpB6gtpAKRSkSbo0l0iuSBp9PNcjX6/TF2sYTia3jq7yH6aHGuiiGydJWsUdNP9nIJ2Cq6/lbOddDey5sEPgPh4HF3No7rH1k3WuQ3lOyq0t+av9TygegxNU4rMSr1rQwa1k8n9dR9QhlmMw0xr+r+n1CnDzEbDJw3w/Ek9GUg9KA41GfHQbXAt7SJJJW7jeLIGOtnBM3mSb28G7T6xV6dcCoeSQAr95j5rZAdqzZTYHShQe2D5zmKNl+/I/Dw1vHX79Qn27J0tnQeKbCn94uZIfVogdYUQizOEWKzUb0A7MbryVfJpHXAnF4a7srLtEkjqySVF7J/TrBL7EzY3uEpvHyO/abShDkKrqO4IIDUJrYHA1gMz87CIxFbgWKGDM6gfllWo3YK1d1GGT8X2ogLY3DO5Vf+j8Z3/m9TS+R2LtmtxbLpw93MhKpCSU1mcriLoEJvSALKQatTbe+cViE97QjEqzonuBPJReRc7fEerg0mG9r7To05V6o9xZarHuAJzs1n1SAKYo7TLnS37J/qsan3r8orjJG4TsT/eESO1QH626hXQjmK2zyU2MYWYTcoxdMv3Lj9J2ys4ykPKy9vjOvPleoe6DaUk+x75WfL2p63GQVTe24cXz2CXnrNhq9kdv6Cikq/sZ8mTBBV0M4QS8Q+t7ljVhT0JHpvvq9/I22Kp5gtPiFcX9hjwbQPCEHm7sBwq8PRwh90m10qUwruWXrdRwq3AdiBnKrsjoUJGPGOLyBFv3tGUHBFFr4vbgN/9f20dv73v5fh9UuB3OWeTGb5diK8E7zUg8xHCPlhvaxK/ICt180Yw1ggnGU3j5MmmcZKq3brJfNomAQPsM9Iawc7q0uawo8PPn6p0+t/CKP2vLEb/q9L0P8dJ5RxuQrInbtfhjHvlDKyVUZEkrq8eXDo7jaMtCC9yLlkr/Ea+unC0Gbz9ONrsrHdBZ1xYsQINc1mxmOMlmiCoLD3yribkrWoSedyKpF77gZmfyb5dbYt2eLnayM1DGVE5xiiDEeaYXHkT9E4x3eX8eSC2eYF9sWa4pAw1g6x6lyMcfIZEyw8hD1aEpajC58w0W4MvoJV2qElJzV70nqufJBXxVrA6VSWBGjOw9pxI7aN8+y1sAdQFdZS/SOu1eFuWGQNHCZQbBG0tx0AwjjAbLWDIVGHoLWCwZC/ajTAURmBg3Xkj1mCDIQJoQAAqa4Da9YDqmud2syZfUR92rObVL7sHpTPsh64EroW4eJUUuUzJC1Fbqt69GfcoC+TScNezN2gDkcgNm7qhacehw5zXk5ZyynSXcoPL8etQ1pg/UDs/A8RTF6nM7OS1oT9T8WVEteHVfnbVRokftQBuSJ5Clbpw19NQR2BmJvdKOjmLW/2vLSS9iZCQB93qS+2sxV0UqHwtnw9ZbPzTtkagFw9o3D1djok3wm5oTJ3FMRSsy5EiblnFTOL234kktVbFmD3KhAAKLPXT/fdzLjcJHer3++efNCHO899TdOGv0sQlBlx0PbJFqUc7WTjsbQ+rwjzAWsjGWeEsZIX72adP6w74Bktaj3falvMLz94a33nwXyZTB4qhA05xfjY/6vzsXxoJEmt158HVzj23JtK5lWuoc7+t0R1lqJ7QBv9Artdbt4+cYO8Ut2QfsYv+7WFdJ3O2/r2wjHyNA+S1+BoM1gqyL8+W2aLeJmk8u2oITOsR2RTKKVMYdZQRufR7oPhNtaKFoQiR7VSOsT/3MeH8SifvvN2UFbkUGzkPVQAUcnUr8zE2HctiOchUukGBxXlqO8vp/lQlmRzpTYH6phLNkcqb5CGewsRPVN9gLxI8XdAIhT6BgedczhCHlBpMuvyw6zct3xhV3txDzU+Mym+v5beLyu+g5SdF1W/R8s1R5TuJfGWeGfT1xEFz7R7XfnKfaiDhxNM9Z7bd056O+p3twu3/JewfKVYpdB0Q5CSKPv4xs6VaSSeZKSZXRPu6320gRPz6xVXh3g28avwXmGvXhAxHcTOmHGrWC82Gan6H/6+imOMvJKNlRZ32fOoOTn0dDVyoMKp2ucu4Ib4EY2CAYl/waj6dxZioRliyVnwq0eZq6nh2dJw=
*/