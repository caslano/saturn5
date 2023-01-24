
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/inherit.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    >
struct inherit2
    : T1, T2
{
    typedef inherit2 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, inherit2, (T1, T2))
};

template< typename T1 >
struct inherit2< T1,empty_base >
{
    typedef T1 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (T1, empty_base))
};

template< typename T2 >
struct inherit2< empty_base,T2 >
{
    typedef T2 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (empty_base, T2))
};

template<>
struct inherit2< empty_base,empty_base >
{
    typedef empty_base type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (empty_base, empty_base))
};

BOOST_MPL_AUX_NA_SPEC(2, inherit2)

template<
      typename T1 = na, typename T2 = na, typename T3 = na
    >
struct inherit3
    : inherit2<
          typename inherit2<
              T1, T2
            >::type
        , T3
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          3
        , inherit3
        , ( T1, T2, T3)
        )
};

BOOST_MPL_AUX_NA_SPEC(3, inherit3)

template<
      typename T1 = na, typename T2 = na, typename T3 = na, typename T4 = na
    >
struct inherit4
    : inherit2<
          typename inherit3<
              T1, T2, T3
            >::type
        , T4
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , inherit4
        , ( T1, T2, T3, T4)
        )
};

BOOST_MPL_AUX_NA_SPEC(4, inherit4)

template<
      typename T1 = na, typename T2 = na, typename T3 = na, typename T4 = na
    , typename T5 = na
    >
struct inherit5
    : inherit2<
          typename inherit4<
              T1, T2, T3, T4
            >::type
        , T5
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , inherit5
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC(5, inherit5)

/// primary template

template<
      typename T1 = empty_base, typename T2 = empty_base
    , typename T3 = empty_base, typename T4 = empty_base
    , typename T5 = empty_base
    >
struct inherit
    : inherit5< T1,T2,T3,T4,T5 >
{
};

template<>
struct inherit< na,na,na,na,na >
{
    template<

          typename T1 = empty_base, typename T2 = empty_base
        , typename T3 = empty_base, typename T4 = empty_base
        , typename T5 = empty_base

        >
    struct apply
        : inherit< T1,T2,T3,T4,T5 >
    {
    };
};

BOOST_MPL_AUX_NA_SPEC_LAMBDA(5, inherit)
BOOST_MPL_AUX_NA_SPEC_ARITY(5, inherit)
BOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(5, 5, inherit)
}}


/* inherit.hpp
TQNr85pF1LrLvLYtt40ATAGGlCI3hIbdi2nc7USJMr8vDpINCQc81NAuq+0gSB1BvxNBF+4USoHVUMcerukdEZDJA9JyH+ywUwhE36QdDN3ci5rOu/o59tY306hhL8zV2MEcDmCx3NUzQqhCVyrq2QPZvDjA3jhgnbxG/MUfEVFitWjR1P+FCklsVBoUR58KiXQFrZQnBKKnPdj567zxPCn1jUqAVqxR743mXlbMoBSvHMbWgaHWO0/QLEhYPDT/L4Cni/oPKMU/7D/7B9Gi7P8myjL99+ia/5S7cEt6uLs7Of57Ii+I+o9c2RNhmwQCOKR4DorPmDA4RMjNVfg4BBQ2YqYDSObUcESHRwrv1DU9vkx9AVHxyLPfzNoyonlg1E6bybhdrS5auX6VuiwUg7gf27kcs4ZfWz0WuEHcDiDlMoXMcE/NMtrt3HefdzNs3TDL9YxNoZMeP6DIc/bfr5PN5ys/I+h65fXH0/kXCAzKAiV9yPOi418TQ6SQhbU+a0S+vYPc1yXKABkQo5I8bPpmR7tDwc7T2eXu4PzEfpX6ZGNiCfwB12B8OKYw5H7GtbgSEkax5G9Qi7e+PFWJ4EZ4xtD+/C7kpLAC4+1mAn3iPKvWG0kP/LE+hsyuu0ixD8+DuMRrYwF8IV6kZFRfSnizZB7Wd/oY03RZc9doeA7GL/fjO8iKhtM/xtOBWA/0hZvYkN096xNDaO9N
*/