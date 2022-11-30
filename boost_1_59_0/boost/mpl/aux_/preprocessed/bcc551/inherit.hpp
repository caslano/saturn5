
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
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
*/