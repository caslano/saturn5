
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