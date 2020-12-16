
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

#if !defined(BOOST_PP_IS_ITERATING)

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#   include <boost/mpl/limits/unrolling.hpp>
#   include <boost/mpl/aux_/preprocessor/repeat.hpp>
#   include <boost/mpl/aux_/config/workaround.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   include <boost/mpl/aux_/nttp_decl.hpp>
#   include <boost/mpl/aux_/config/eti.hpp>

#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/dec.hpp>
#   include <boost/preprocessor/cat.hpp>

// local macros, #undef-ined at the end of the header

#   define AUX778076_ITER_FOLD_STEP(unused, i, unused2) \
    typedef typename apply2< \
          ForwardOp \
        , BOOST_PP_CAT(state,i) \
        , AUX778076_FOLD_IMPL_OP(BOOST_PP_CAT(iter,i)) \
        >::type BOOST_PP_CAT(state,BOOST_PP_INC(i)); \
    typedef typename mpl::next<BOOST_PP_CAT(iter,i)>::type \
        BOOST_PP_CAT(iter,BOOST_PP_INC(i)); \
    /**/

#   define AUX778076_FOLD_IMPL_NAME \
    BOOST_PP_CAT(AUX778076_FOLD_IMPL_NAME_PREFIX,_impl) \
    /**/

#   define AUX778076_FOLD_CHUNK_NAME \
    BOOST_PP_CAT(AUX778076_FOLD_IMPL_NAME_PREFIX,_chunk) \
    /**/

namespace boost { namespace mpl { namespace aux {

/// forward declaration
template<
      BOOST_MPL_AUX_NTTP_DECL(int, N)
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    > 
struct AUX778076_FOLD_IMPL_NAME;

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

#   if !BOOST_WORKAROUND(__BORLANDC__, < 0x600)

#   define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, BOOST_MPL_LIMIT_UNROLLING, <boost/mpl/aux_/fold_impl_body.hpp>))
#   include BOOST_PP_ITERATE()

// implementation for N that exceeds BOOST_MPL_LIMIT_UNROLLING
template<
      BOOST_MPL_AUX_NTTP_DECL(int, N)
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    > 
struct AUX778076_FOLD_IMPL_NAME
{
    typedef AUX778076_FOLD_IMPL_NAME<
          BOOST_MPL_LIMIT_UNROLLING
        , First
        , Last
        , State
        , ForwardOp
        > chunk_;

    typedef AUX778076_FOLD_IMPL_NAME<
          ( (N - BOOST_MPL_LIMIT_UNROLLING) < 0 ? 0 : N - BOOST_MPL_LIMIT_UNROLLING )
        , typename chunk_::iterator
        , Last
        , typename chunk_::state
        , ForwardOp
        > res_;
        
    typedef typename res_::state state;
    typedef typename res_::iterator iterator;
};

// fallback implementation for sequences of unknown size
template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    > 
struct AUX778076_FOLD_IMPL_NAME<-1,First,Last,State,ForwardOp>
    : AUX778076_FOLD_IMPL_NAME<
          -1
        , typename mpl::next<First>::type
        , Last
        , typename apply2<ForwardOp,State,AUX778076_FOLD_IMPL_OP(First)>::type
        , ForwardOp
        >
{
};

template<
      typename Last
    , typename State
    , typename ForwardOp
    > 
struct AUX778076_FOLD_IMPL_NAME<-1,Last,Last,State,ForwardOp>
{
    typedef State state;
    typedef Last iterator;
};

#   else // BOOST_WORKAROUND(__BORLANDC__, < 0x600)

// Borland have some serious problems with the unrolled version, so
// we always use a basic implementation
template<
      BOOST_MPL_AUX_NTTP_DECL(int, N)
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    > 
struct AUX778076_FOLD_IMPL_NAME
{
    typedef AUX778076_FOLD_IMPL_NAME<
          -1
        , typename mpl::next<First>::type
        , Last
        , typename apply2<ForwardOp,State,AUX778076_FOLD_IMPL_OP(First)>::type
        , ForwardOp
        > res_;

    typedef typename res_::state state;
    typedef typename res_::iterator iterator;
    typedef state type;
};

template<
      BOOST_MPL_AUX_NTTP_DECL(int, N)
     , typename Last
    , typename State
    , typename ForwardOp
    > 
struct AUX778076_FOLD_IMPL_NAME<N,Last,Last,State,ForwardOp >
{
    typedef State state;
    typedef Last iterator;
    typedef state type;
};

#   endif // BOOST_WORKAROUND(__BORLANDC__, < 0x600)
 
#else // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

template< BOOST_MPL_AUX_NTTP_DECL(int, N) >
struct AUX778076_FOLD_CHUNK_NAME;

#   define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, BOOST_MPL_LIMIT_UNROLLING, <boost/mpl/aux_/fold_impl_body.hpp>))
#   include BOOST_PP_ITERATE()

// implementation for N that exceeds BOOST_MPL_LIMIT_UNROLLING
template< BOOST_MPL_AUX_NTTP_DECL(int, N) > 
struct AUX778076_FOLD_CHUNK_NAME
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        > 
    struct result_
    {
        typedef AUX778076_FOLD_IMPL_NAME<
              BOOST_MPL_LIMIT_UNROLLING
            , First
            , Last
            , State
            , ForwardOp
            > chunk_;

        typedef AUX778076_FOLD_IMPL_NAME<
              ( (N - BOOST_MPL_LIMIT_UNROLLING) < 0 ? 0 : N - BOOST_MPL_LIMIT_UNROLLING )
            , typename chunk_::iterator
            , Last
            , typename chunk_::state
            , ForwardOp
            > res_;

        typedef typename res_::state state;
        typedef typename res_::iterator iterator;
    };
};

// fallback implementation for sequences of unknown size
template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    > 
struct BOOST_PP_CAT(AUX778076_FOLD_IMPL_NAME_PREFIX,_step);

template<
      typename Last
    , typename State
    >
struct BOOST_PP_CAT(AUX778076_FOLD_IMPL_NAME_PREFIX,_null_step)
{
    typedef Last iterator;
    typedef State state;
};

template<> 
struct AUX778076_FOLD_CHUNK_NAME<-1>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        > 
    struct result_
    {
        typedef typename if_<
              typename is_same<First,Last>::type
            , BOOST_PP_CAT(AUX778076_FOLD_IMPL_NAME_PREFIX,_null_step)<Last,State>
            , BOOST_PP_CAT(AUX778076_FOLD_IMPL_NAME_PREFIX,_step)<First,Last,State,ForwardOp>
            >::type res_;

        typedef typename res_::state state;
        typedef typename res_::iterator iterator;
    };

#if defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG)
    /// ETI workaround
    template<> struct result_<int,int,int,int>
    {
        typedef int state;
        typedef int iterator;
    };
#endif
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    > 
struct BOOST_PP_CAT(AUX778076_FOLD_IMPL_NAME_PREFIX,_step)
{
    // can't inherit here - it breaks MSVC 7.0
    typedef AUX778076_FOLD_CHUNK_NAME<-1>::template result_<
          typename mpl::next<First>::type
        , Last
        , typename apply2<ForwardOp,State,AUX778076_FOLD_IMPL_OP(First)>::type
        , ForwardOp
        > chunk_;

    typedef typename chunk_::state state;
    typedef typename chunk_::iterator iterator;
};

template<
      BOOST_MPL_AUX_NTTP_DECL(int, N)
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    > 
struct AUX778076_FOLD_IMPL_NAME
    : AUX778076_FOLD_CHUNK_NAME<N>
        ::template result_<First,Last,State,ForwardOp>
{
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

}}}

#   undef AUX778076_FOLD_IMPL_NAME
#   undef AUX778076_FOLD_CHUNK_NAME
#   undef AUX778076_ITER_FOLD_STEP

#undef AUX778076_FOLD_IMPL_OP
#undef AUX778076_FOLD_IMPL_NAME_PREFIX

///// iteration

#else

#   define n_ BOOST_PP_FRAME_ITERATION(1)

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct AUX778076_FOLD_IMPL_NAME<n_,First,Last,State,ForwardOp>
{
    typedef First iter0;
    typedef State state0;

    BOOST_MPL_PP_REPEAT(n_, AUX778076_ITER_FOLD_STEP, unused)

    typedef BOOST_PP_CAT(state,n_) state;
    typedef BOOST_PP_CAT(iter,n_) iterator;
};

#else

template<> struct AUX778076_FOLD_CHUNK_NAME<n_>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State state0;

        BOOST_MPL_PP_REPEAT(n_, AUX778076_ITER_FOLD_STEP, unused)

        typedef BOOST_PP_CAT(state,n_) state;
        typedef BOOST_PP_CAT(iter,n_) iterator;
    };

#if defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG)
    /// ETI workaround
    template<> struct result_<int,int,int,int>
    {
        typedef int state;
        typedef int iterator;
    };
#endif
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#   undef n_

#endif // BOOST_PP_IS_ITERATING

/* fold_impl_body.hpp
2Htz9wDwUgkheDqJ7Gm7laSpu4x+0yObjNt5LkVyyxU5rP29zcN0K3xTfZuGRUYP+fxm4x5EGTzukTUdnf/jA+uaX6hehDuTbYK+Qwflu37TIKX3macQQAZvbfHzZlGbOQGfh2pkwWMtgrIjvwUFrdRFIgQH4THrIMvTGbANaAnGWkH3pnE3nXI0PtmWfysPuPQ58cVRmCoeZcGuipzHqgAsfOF8FVFgMfoQaAGZg+9bkLlTQsbo65R9fYhc7mtp0zQQRN5g5+KSL8Leh2FfGEAQmjM5VQQ8l3wUHId099ifJNCINbJx+BSagJ7NN/UoBEeBv4eqzfFZil/v188Vl5pfODEUAP6RGU6VIQiE5N6OU3+U5juX/v81/W/Q/6vo/322/2+w/j1i/yD///t+/+Lwzwr3ua7wBWxRI/ysTsOJk3KKv1iccg/kFCbL7Y0qlUEVwSfdITP2qwzs7Gc5NU7SU9Ar50H+1cWuj2i4J0h95I4PS2Zs8KgoWbPrALoJneikyglE8JblEF28VoSwyTFmbYcL9DnEGF2aqGQ1HqXXIfw3EGleSOyHtaG/O2RqV3hZ85K6GPMvhd5oLrd0FVrK55ZCTyh+JVXqzF7VCBxluWvCrOtMwBlEv0qL15B75sC59iaSuYnwVeUFa/JFeOvVUH4kZbaVb4np+OlbpoeIsgqK70LeuwmTrqYpr6IYtzBqS8WRHy5insArd8HafHNIrVSroM4uss/8AbfWgl8b7kwfeearjLmV1VN6t8PWozzcP+xPWxghM+FbRWRHv+fG0lDNrE9qtCHEUYEBanazaXYbExTDe2xFTj2rl1/6oVIp5uifZLeIp5IPzP7XO6tAQB2RXV/miksk3Gi/Tno9xj4Ev2P9H1FvPFNzyNs1NsfzHAFUxT73k4oWVYdeUFYy1rh5x1o72uvn4lV2x1pftbf5pKYeaRc5AQr5grS5GNlJnQFWLwIa/sBpRi0lgaEe+RI7iRnmrKp0BjcTuvK78nmo1/f8Tjo+TuMJY4TL29n8i9IlD3SwSvsQC0RguwKxjRgv/NlfCUrSp+TW4cfaqqUo9HFDPbT9U1JT+sDbesD+6ZgW/V0We1n+ZMkzEMbNC1wDhYXC3vAVT/BHsKsS2tR/cyhkdQHrEEYKk9kq4wGpfuCnxHElfYzbVU1DEFao/ISufAxVlnGfTzLv+6t1hhJDr4GKYa15M/tNRYklSqzmoZyyLmGPijTI6PYgYY4eSj7Qx3hA971I9X2S7vtBMflLaMcr7VtXeDpPBIuaqScCHVeam7JAuuRjiceoxgCpa4qMr93aLTKUUBEgUKonGU9qCI7HQB6LAI9CIc3JD1mMf0wP9e7iwOOtcwq/nz8r/mESy2PorJ78DyyDFYPtcoZuqYBusYj/cQiTQgxey28yMwGe+Bo7Pt7Z6P73diD8+vBOvTeCfq0Km7lTbYt+gSIF3Hk0jjweByQa0xIUNk21OWvmu7lX/GMS5+nsUI08bwfayfPWRPznDk3Jc5VbjqcsDuNJAI1M3+uyXA56lZ/tc/X84MplnJtYx4/FuSEs/6cevX4lX0etXx9YsFtLaMxnEW3Xb9Uq9tHPgDl+pXaDXXrIGZ/WcRPj6UTjMSvfaGo9z35DzTfL2GGdF2MBj+vag9aqFvMAMEa1w3Z0U2NEkeltGqNY3yCdbHr2Hd2c/dXZlB9j/9mhJfurH3dtFP+xxfL1RCra7D/TW7MXDXWJiv94dCvl2f6jc+v8vi+8LcQ/jqP+hXj2Nc8PvK3p9pke+ZRIz8ZRyCG2NGw65IukqjHEvY8jw6PcWF+yXdIxjR2sQituTjeoCNVlezfNv7mvj9C1K/whMo6ukK4=
*/