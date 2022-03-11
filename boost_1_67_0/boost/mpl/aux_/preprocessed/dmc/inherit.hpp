
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