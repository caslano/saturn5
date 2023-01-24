
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

template<
      typename F
    >
struct apply< F,na,na,na,na,na >
    : apply0<F>
{
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

template<
      typename F, typename T1
    >
struct apply< F,T1,na,na,na,na >
    : apply1< F,T1 >
{
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

template<
      typename F, typename T1, typename T2
    >
struct apply< F,T1,T2,na,na,na >
    : apply2< F,T1,T2 >
{
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

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply< F,T1,T2,T3,na,na >
    : apply3< F,T1,T2,T3 >
{
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

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply< F,T1,T2,T3,T4,na >
    : apply4< F,T1,T2,T3,T4 >
{
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

/// primary template (not a specialization!)

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply
    : apply5< F,T1,T2,T3,T4,T5 >
{
};

}}


/* apply.hpp
9m/Ipv/rGN16tRujTS6T2o0t4vfqwt/Qcq/1+tfFPwBnbs20e0xAZ4xdj7KjgpaM5qHgPDKaBjOFSYyByD9NKP+4trf05bchMGhdxgFsZie9yv3O0IsIW/DhP28b4pp1JBwZavsgxEHONTIoJTHs78hqeZMhSfoOvoq4lhKo+Yi/ZIxRRdW4TjTPcztMnEvGZeI3NKYhM+U0x6PHEiVzbf2rsZs+bW0r+9R1Ru0ltuCHea6fbWbDWG/UyusHU6nyxZ2srCAt/fZCgkLYQl+EOrA6MfxWsSVzqIRaHS+O7U/wW1odbcwTyF/Ri4AjYXhjax/eq3IL7Na/DCcZSVp/D6ur6e6u9jPyMTAQev8y/apt70sTkaumSLQCwbr6o5ZZlYOWGCfy/GFDYKYX6GSCNu0lU8W7Na+Ib3ZcneN9yd89YU3mZJZ7NL5fdfhlxAV1y3AasbOC+GJlecor5LBXn0Pz9LzG/ZdHEg6zR3ugvrdq+pUOh30nIT3xiIVPedeTGuybYUXP2rNWisIqTTBHiQ2k7s3GhCGJ7FTZUabMLxd8gxWZBY7tOI4XyUred06trBVGmhQxywh6tgFyjkwS1amGQqrWcDsn6/3OgaYWw5orCVLySsF6W6ArLJ/zJhxhwFRsaEG+PrcWg9k3QUt5YMVMcvrj1Up+kHqLiZl1iyQPnIpUW1eYMn56XLbnyu7X7gkhdvbh+yxln3b5
*/