
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F
    >
struct apply0

    : apply_wrap0<
          typename lambda<F>::type
       
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          1
        , apply0
        , (F )
        )
};

/// workaround for ETI bug
template<>
struct apply0<int>
{
    typedef int type;
};

template<
      typename F, typename T1
    >
struct apply1

    : apply_wrap1<
          typename lambda<F>::type
        , T1
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          2
        , apply1
        , (F, T1)
        )
};

/// workaround for ETI bug
template<>
struct apply1< int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2
    >
struct apply2

    : apply_wrap2<
          typename lambda<F>::type
        , T1, T2
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          3
        , apply2
        , (F, T1, T2)
        )
};

/// workaround for ETI bug
template<>
struct apply2< int,int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply3

    : apply_wrap3<
          typename lambda<F>::type
        , T1, T2, T3
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , apply3
        , (F, T1, T2, T3)
        )
};

/// workaround for ETI bug
template<>
struct apply3< int,int,int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply4

    : apply_wrap4<
          typename lambda<F>::type
        , T1, T2, T3, T4
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , apply4
        , (F, T1, T2, T3, T4)
        )
};

/// workaround for ETI bug
template<>
struct apply4< int,int,int,int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply5

    : apply_wrap5<
          typename lambda<F>::type
        , T1, T2, T3, T4, T5
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          6
        , apply5
        , (F, T1, T2, T3, T4, T5)
        )
};

/// workaround for ETI bug
template<>
struct apply5< int,int,int,int,int,int >
{
    typedef int type;
};

}}


/* apply.hpp
sbXhIuWurTIKngaCjwf3j52IzCRcd1PzNx2du84h6hPKNyKnFVtrN3fRylpKq6AGBjHvvfXMsfQ4xlOJNc/Tw54ItLLmZZ5HdnXuKezIsc1316KvPL314FR63r0GbW85xidh1rm57HcQejM3ESnJ15APk1hztTkriGBset7uuV+CXzbl1elzZGJ5rD7E2zntF75njumbke3w3TEwtjxeQUxhW4FnJ9z1HMbuXeidSNG0yjoQR2262LqMP3Glr4PeDV4yA2DoYP+xOp9DHrdH9K67rVtL/Q+36L5TvY6aYjXl1IAjexG+paBrug8in/QudsYDxISaWCZLW6Z1dPf2MX8m9x0P4t3hAe8KEYVzTYnq56enoTFNg5AGQPsk22cDiiX7MuPYEECufuA6lPg2zPBQX24Iqp9NZ3RgU51ra1LLu13xkKY3R+3X8wXnP2PcMq8Du0gGi3R+5jrgai43OQ5UGmYT2ftaVRnx/Gb46YWsNDz/sO7ytAWZ7CBS0URJZzd6RXcXbaphZG9kv4cpPb6OHOhfYPzSOQ0oAoIyGDU1bWF+o2MxEIn+98YH0PC9STmSJrNwKm/qljFUxcuIBS2P2gjlxRSaFkU64ej2kqgbF4OYCO628jKr9d8BvTs8x4/YbS6IHvuul7501nmYz2JvPWvRfKsxEfyl2HFpr8Tu4/a0dl0xtfp7m8mpP97+GtSp67emIxs0tsi/
*/