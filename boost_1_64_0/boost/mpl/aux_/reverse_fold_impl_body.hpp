
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION!

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
#   include <boost/mpl/aux_/config/ctps.hpp>
#   include <boost/mpl/aux_/nttp_decl.hpp>

#   include <boost/preprocessor/arithmetic/sub.hpp>
#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/dec.hpp>
#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>

// local macros, #undef-ined at the end of the header

#   define AUX778076_ITER_FOLD_FORWARD_STEP(unused, n_, unused2) \
    typedef typename apply2< \
          ForwardOp \
        , BOOST_PP_CAT(fwd_state,n_) \
        , AUX778076_FOLD_IMPL_OP(BOOST_PP_CAT(iter,n_)) \
        >::type BOOST_PP_CAT(fwd_state,BOOST_PP_INC(n_)); \
    typedef typename mpl::next<BOOST_PP_CAT(iter,n_)>::type \
        BOOST_PP_CAT(iter,BOOST_PP_INC(n_)); \
    /**/

#   define AUX778076_ITER_FOLD_BACKWARD_STEP_FUNC(n_) \
    typedef typename apply2< \
          BackwardOp \
        , BOOST_PP_CAT(bkwd_state,n_) \
        , AUX778076_FOLD_IMPL_OP(BOOST_PP_CAT(iter,BOOST_PP_DEC(n_))) \
        >::type BOOST_PP_CAT(bkwd_state,BOOST_PP_DEC(n_)); \
    /**/

#   define AUX778076_ITER_FOLD_BACKWARD_STEP(unused, n_, j) \
    AUX778076_ITER_FOLD_BACKWARD_STEP_FUNC( \
          BOOST_PP_SUB_D(1,j,n_) \
        ) \
    /**/

#   define AUX778076_FIRST_BACKWARD_STATE_TYPEDEF(n_) \
    typedef typename nested_chunk::state BOOST_PP_CAT(bkwd_state,n_);
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
      BOOST_MPL_AUX_NTTP_DECL(long, N)
    , typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    > 
struct AUX778076_FOLD_IMPL_NAME;

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
    && !defined(BOOST_MPL_CFG_NO_NONTYPE_TEMPLATE_PARTIAL_SPEC)

#   define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, BOOST_MPL_LIMIT_UNROLLING, <boost/mpl/aux_/reverse_fold_impl_body.hpp>))
#   include BOOST_PP_ITERATE()

// implementation for N that exceeds BOOST_MPL_LIMIT_UNROLLING
template<
      BOOST_MPL_AUX_NTTP_DECL(long, N)
    , typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    > 
struct AUX778076_FOLD_IMPL_NAME
{
    typedef First iter0;
    typedef State fwd_state0;

    BOOST_MPL_PP_REPEAT(
          BOOST_MPL_LIMIT_UNROLLING
        , AUX778076_ITER_FOLD_FORWARD_STEP
        , unused
        )

    typedef AUX778076_FOLD_IMPL_NAME<
          ( (N - BOOST_MPL_LIMIT_UNROLLING) < 0 ? 0 : N - BOOST_MPL_LIMIT_UNROLLING )
        , BOOST_PP_CAT(iter,BOOST_MPL_LIMIT_UNROLLING)
        , Last
        , BOOST_PP_CAT(fwd_state,BOOST_MPL_LIMIT_UNROLLING)
        , BackwardOp
        , ForwardOp
        > nested_chunk;
        
    AUX778076_FIRST_BACKWARD_STATE_TYPEDEF(BOOST_MPL_LIMIT_UNROLLING)

    BOOST_MPL_PP_REPEAT(
          BOOST_MPL_LIMIT_UNROLLING
        , AUX778076_ITER_FOLD_BACKWARD_STEP
        , BOOST_MPL_LIMIT_UNROLLING
        )

    typedef bkwd_state0 state;
    typedef typename nested_chunk::iterator iterator;
};

// fallback implementation for sequences of unknown size
template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    > 
struct AUX778076_FOLD_IMPL_NAME<-1,First,Last,State,BackwardOp,ForwardOp>
{
    typedef AUX778076_FOLD_IMPL_NAME<
          -1
        , typename mpl::next<First>::type
        , Last
        , typename apply2<ForwardOp,State,AUX778076_FOLD_IMPL_OP(First)>::type
        , BackwardOp
        , ForwardOp
        > nested_step;

    typedef typename apply2<
          BackwardOp
        , typename nested_step::state
        , AUX778076_FOLD_IMPL_OP(First)
        >::type state;

    typedef typename nested_step::iterator iterator;
};

template<
      typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    > 
struct AUX778076_FOLD_IMPL_NAME<-1,Last,Last,State,BackwardOp,ForwardOp>
{
    typedef State state;
    typedef Last iterator;
};

#else // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

template< BOOST_MPL_AUX_NTTP_DECL(long, N) >
struct AUX778076_FOLD_CHUNK_NAME;

#   define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, BOOST_MPL_LIMIT_UNROLLING, <boost/mpl/aux_/reverse_fold_impl_body.hpp>))
#   include BOOST_PP_ITERATE()

// implementation for N that exceeds BOOST_MPL_LIMIT_UNROLLING
template< BOOST_MPL_AUX_NTTP_DECL(long, N) > 
struct AUX778076_FOLD_CHUNK_NAME
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        > 
    struct result_
    {
        typedef First iter0;
        typedef State fwd_state0;

        BOOST_MPL_PP_REPEAT(
              BOOST_MPL_LIMIT_UNROLLING
            , AUX778076_ITER_FOLD_FORWARD_STEP
            , unused
            )

        typedef AUX778076_FOLD_IMPL_NAME<
              ( (N - BOOST_MPL_LIMIT_UNROLLING) < 0 ? 0 : N - BOOST_MPL_LIMIT_UNROLLING )
            , BOOST_PP_CAT(iter,BOOST_MPL_LIMIT_UNROLLING)
            , Last
            , BOOST_PP_CAT(fwd_state,BOOST_MPL_LIMIT_UNROLLING)
            , BackwardOp
            , ForwardOp
            > nested_chunk;
            
        AUX778076_FIRST_BACKWARD_STATE_TYPEDEF(BOOST_MPL_LIMIT_UNROLLING)

        BOOST_MPL_PP_REPEAT(
              BOOST_MPL_LIMIT_UNROLLING
            , AUX778076_ITER_FOLD_BACKWARD_STEP
            , BOOST_MPL_LIMIT_UNROLLING
            )

        typedef bkwd_state0 state;
        typedef typename nested_chunk::iterator iterator;
    };
};

// fallback implementation for sequences of unknown size
template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
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
        , typename BackwardOp
        , typename ForwardOp
        > 
    struct result_
    {
        typedef typename if_<
              typename is_same<First,Last>::type
            , BOOST_PP_CAT(AUX778076_FOLD_IMPL_NAME_PREFIX,_null_step)<Last,State>
            , BOOST_PP_CAT(AUX778076_FOLD_IMPL_NAME_PREFIX,_step)<First,Last,State,BackwardOp,ForwardOp>
            >::type res_;

        typedef typename res_::state state;
        typedef typename res_::iterator iterator;
    };

#if defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG)
    /// ETI workaround
    template<> struct result_<int,int,int,int,int>
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
    , typename BackwardOp
    , typename ForwardOp
    > 
struct BOOST_PP_CAT(AUX778076_FOLD_IMPL_NAME_PREFIX,_step)
{
    typedef AUX778076_FOLD_CHUNK_NAME<-1>::template result_<
          typename mpl::next<First>::type
        , Last
        , typename apply2<ForwardOp,State,AUX778076_FOLD_IMPL_OP(First)>::type
        , BackwardOp
        , ForwardOp
        > nested_step;

    typedef typename apply2<
          BackwardOp
        , typename nested_step::state
        , AUX778076_FOLD_IMPL_OP(First)
        >::type state;

    typedef typename nested_step::iterator iterator;
};

template<
      BOOST_MPL_AUX_NTTP_DECL(long, N)
    , typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    > 
struct AUX778076_FOLD_IMPL_NAME
    : AUX778076_FOLD_CHUNK_NAME<N>
        ::template result_<First,Last,State,BackwardOp,ForwardOp>
{
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

}}}

#   undef AUX778076_FIRST_BACKWARD_STATE_TYPEDEF
#   undef AUX778076_ITER_FOLD_BACKWARD_STEP
#   undef AUX778076_ITER_FOLD_BACKWARD_STEP_FUNC
#   undef AUX778076_ITER_FOLD_FORWARD_STEP

#undef AUX778076_FOLD_IMPL_OP
#undef AUX778076_FOLD_IMPL_NAME_PREFIX

///// iteration

#else

#   define n_ BOOST_PP_FRAME_ITERATION(1)

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
    && !defined(BOOST_MPL_CFG_NO_NONTYPE_TEMPLATE_PARTIAL_SPEC)

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct AUX778076_FOLD_IMPL_NAME<n_,First,Last,State,BackwardOp,ForwardOp>
{
    typedef First iter0;
    typedef State fwd_state0;

    BOOST_MPL_PP_REPEAT(
          n_
        , AUX778076_ITER_FOLD_FORWARD_STEP
        , unused
        )

    typedef BOOST_PP_CAT(fwd_state,n_) BOOST_PP_CAT(bkwd_state,n_);

    BOOST_MPL_PP_REPEAT(
          n_
        , AUX778076_ITER_FOLD_BACKWARD_STEP
        , n_
        )

    typedef bkwd_state0 state;
    typedef BOOST_PP_CAT(iter,n_) iterator;
};

#else

template<> struct AUX778076_FOLD_CHUNK_NAME<n_>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State fwd_state0;

        BOOST_MPL_PP_REPEAT(
              n_
            , AUX778076_ITER_FOLD_FORWARD_STEP
            , unused
            )

        typedef BOOST_PP_CAT(fwd_state,n_) BOOST_PP_CAT(bkwd_state,n_);

        BOOST_MPL_PP_REPEAT(
              n_
            , AUX778076_ITER_FOLD_BACKWARD_STEP
            , n_
            )

        typedef bkwd_state0 state;
        typedef BOOST_PP_CAT(iter,n_) iterator;
    };

#if defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG)
    /// ETI workaround
    template<> struct result_<int,int,int,int,int>
    {
        typedef int state;
        typedef int iterator;
    };
#endif
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#   undef n_

#endif // BOOST_PP_IS_ITERATING

/* reverse_fold_impl_body.hpp
zpWXHUSl4R6SjZuH5gEDSeXuN6S5bELpxp+InH2Hy51QgnTOUfbp8yyE6gphbWwCLT2Syheov0RZnj9zcBuCGYfmsGGdnnSTZJHVrCPQiX3pZ6YySeiVsN5FoPkbj7J3PvL0cdFN6rr0HtVJ/Zn1hTmwc77KViQIUWBoMgV9PwjrNT6UmnuP3hlJUuY6OwzKcaOSk524muxJtUHTcX1GFuv+MR2F/W3Z2Cd2iBj9jSdUrSaxT5L0c6UM+Y7fTglbbPFDbCEVvA6hn2+7cV3lIgYZetO40mhaFzyY9d/tSguFqqijKwy6QzXZ5zcZlF2SxiJ6uyBiXSI+aCVTWUo1JCXH0Mvbxph9t5MW3GK0xtuCxuMCWXWq0wqdUIz1raWHIX1ZnGM6hg2JYqfu51CRsQaJ9z0Eg1Hv2ZOSLjSc12fH7z9DSdJ67hK+gEIOPRHYKAyj7piyV/VRlPpCE/19VlKDlTSReQcV8iTWkGWCkZNO8wF6IgiXEmBqOSoI0pSHR7s4qZhxXjssle5oO7Oy4YyG71anjOkq5Cx9CIq+M+n9xhj+OnAu7ddLZPc9jpCmTRmVDPxO3fv6YwV/j2ejfVib2g8avXcP9QpRpeLiG+zdgBbqOT6Ldq3VJYPdV/gOssWe4AYSW5aM7r2PEZLzWjCmHeA7xBVoVNZODBbIUGHbR1Z//zLlyNdyR8E8qqjiM806FoxM96U8zCKPDmkfxzBxG1o/+Ruze2AEvlKEFzlep0XXJHj0oyf0ac1hZCW40NOofbx2TQX2qyxmsRXFlJ8hRFubZ5LSaH+WRc2YWqKJELM0er+8mUz0Iujg/cFsYJAIfHcqk8n807j69QA+ybdj56EsXrDzKNZPJLY6wAh9CkZjyOilGD/lGpc6WELr+wlTjakwbDT2cC3ZMRBxe8suWPtR37uSfPvIeOoMiSCbb21I9dgD186PtPXaUxa9S58sFWJZkvZRavl8hT/PeYxa/RA+pd2BHqqfRWDadZj2nOLmGRV0ZVEPjs3xgYKuGlfSu0HxhqtI0fYFKU6XR5KENapbfpKJiQDTGUH84yJ7iOS5YbnvPqzYMIznSeyDbexGGL82ooC8TzSo9yAaE+eI0+tX0rh7TuyEnTzFRRjCdXUwnXs4HwN2jqaGvhv5tR02EGAd/MHs6RTfEE1Vchuo9PRFRETGoGTgMfbYxRzHR57neZKy2BpQQzPqLSnw2gtal3KGzA738E1j1uCcdW/cLo2iNtcdsCuaThfvu7GTa6vJzG4yvZ4r+B7Ud+HBiNPkOKOZicnG0XjfPFb3ZCTSa9O57ZmPaC9NYfbDs+hV9HoYtoYj77w71OJ6kbp7f75oVg2dzKpGgOU+2vggH3L2dZQz6RazfeMB1wWRJGkmQ+an1rFyz1A67JpHPW7dNPaVAUICfUkkeRdbvcQag+rW8bYFewXjWQ0/6rmFjhQS809bSGU7ZoBJXMOUE8dYp6kBchsvs4P2s9DRpcimfDEm2cbNsFq+EJLPnGAyXrBelLKUHjaNId2aUP7Hq+1YOOIjbTm8DLH1Frwo+DROpX3h6UP3koJDIs45f4aQ43GmcLEUcaMkWPLURbCYJMc7Mz5hU1QYnllk0+cDP2mQkw1t047hUcvu06LELN4+QZnszUT5c+uV9POFOLl80YFj9EP+WjwVJsM0kb7lEu2Ks+ZvAg9i1pf9fKLTHjhFzGFOhWGUkvCZFIUf0b2+3jRVtB3ft+5gg3qdJ5FXU0j8+WIy3eXGCsLOwFQknx8Q2EEJM65x1Y4AFGUU4vDdrXjHO0HhbSSZboC+ajOQLn2Ll98CmUYPRUzGV5qT/5BWL9KEnZQKvneVY/i1S/AQzSY=
*/