
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