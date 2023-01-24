
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
01kbzQyhzc8RYewv7pfrPkeZLkCep2met/k2vv0nQX1scehG6CnRpfq72XVn30zkaBm0SSPgUv2KXTWfT8anqiu2EpRfhuWbM8p6GTD64ujFydCoxXEeFLeqhFYN1y8lDN4aPnPTX7Ad5oqbnrR1xxGrkMxY/9pjMZANn7Ql5EP3OsuybmfFyWim7xKP+pBP0vqeasdiNQtPEFqZDXca5L4Nc8uVmw9vOa3m6hffrTm4iizveHMmkLH+9JXkcK8fsT+smI5lI59PGV3yCUkAtoQeZBBye2QjNj+hy6eXsf51PjmjQLzWzwboNR8PAjNyN/j8NWVhSgwqYzV9WXe98BfK95uY2PKWOz5EdXyJ2eKAJEwOALwSp8e+qwfAaZL5u+h5OlnclhD7JzcDp8b8dVhfxEQvmk8mipMbhMy51F/OwA7cM9IDHaBtxAgw2+5yhjE/YPanQaGpjCE4kKlgqRQM0MIeYKngqZTtuGg6gcdpATMyvRsBPmhv7uuWW5oDvshGTGBrvns3aPcCSFpxWjH8EJ5YtehKUQ7+4Z82Nk8eT1EXOygtQoy869jq2CTd0w09+bE1K4bq+obdW+qGV+uGBrqGZ/sCbg/qJE8o/ttGNaDcZaLz4wscX31YyE8px1G/+9sjN4wfRctSOrLlv6nXJxaILy9e7u38wAWseTRd2q0t7trgaOHa+mdM7sYYj5fjyH5ZXpDmEJOj
*/