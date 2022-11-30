
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