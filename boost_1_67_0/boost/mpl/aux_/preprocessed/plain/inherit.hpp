
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