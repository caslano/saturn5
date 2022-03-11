
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