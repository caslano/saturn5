
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