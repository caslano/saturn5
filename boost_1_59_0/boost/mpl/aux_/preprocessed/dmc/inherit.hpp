
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