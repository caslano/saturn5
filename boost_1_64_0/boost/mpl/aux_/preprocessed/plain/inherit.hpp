
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
nzbfGRSdvLf5rYZ4QuURW/ZIoBFjA4AR+Q9wBPQpFRSnci6MRGIKiw3Wvt6d32W9nFyLArMLbQALWDnDDnTjqpyV2Zb2PNhxMvykRYQoknsx9jRJUaTQS0CclWrwZOi0ooaXKZjqQcYwNsKPEqu91lCqFuIqeP6Kifsf5mWDrohaBPU0SHrJelz5Nhgm/cyq3k6Wr6y3botOoZhPl8T0occUyWuQu/ljMwA3W8acpVxQUg8ZTgaOioayWxC7i1Bob2wifXLeX96UgK6eElNJwkmv9/pdGO0F39Vm4kTAAC7dPE/xmjLR78eoTvvrtC0CcCliOS11/dzVKMKplKTwxfqRBTIbDpGGRPefTZCByY67Y2XZTZ3nuqRm/2Fu/f5heRPISyZdDpUUvB8SHXpZAVcuDOiovRjV79NTMgZ4PF1DssMMJgCsZm/Knq5Z1iCHv31aBCsT/buneoHZWdxmd0m0bpKaLFETKNhLbvttJ11Y4fSgZWqqn/VTaJLpYaHU+qVAxgQ84vbc1Yxo5vxUlKR1zq7mrvC3Gc0Xam0oA4BKMaQAYeLKy3FKLg==
*/