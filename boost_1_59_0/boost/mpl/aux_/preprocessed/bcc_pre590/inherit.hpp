
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "inherit.hpp" header
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

          typename T1, typename T2, typename T3, typename T4, typename T5

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