
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