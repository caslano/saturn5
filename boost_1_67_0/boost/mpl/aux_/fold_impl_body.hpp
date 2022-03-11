
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
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
*/