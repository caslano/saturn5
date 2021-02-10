
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/quote.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template< typename T, bool has_type_ >
struct quote_impl
    : T
{
};

template< typename T >
struct quote_impl< T,false >
{
    typedef T type;
};

template<
      template< typename P1 > class F
    , typename Tag = void_
    >
struct quote1
{
    template< typename U1 > struct apply

        : quote_impl<
              F<U1>
            , aux::has_type< F<U1> >::value
            >

    {
    };
};

template<
      template< typename P1, typename P2 > class F
    , typename Tag = void_
    >
struct quote2
{
    template< typename U1, typename U2 > struct apply

        : quote_impl<
              F< U1,U2 >
            , aux::has_type< F< U1,U2 > >::value
            >

    {
    };
};

template<
      template< typename P1, typename P2, typename P3 > class F
    , typename Tag = void_
    >
struct quote3
{
    template< typename U1, typename U2, typename U3 > struct apply

        : quote_impl<
              F< U1,U2,U3 >
            , aux::has_type< F< U1,U2,U3 > >::value
            >

    {
    };
};

template<
      template< typename P1, typename P2, typename P3, typename P4 > class F
    , typename Tag = void_
    >
struct quote4
{
    template<
          typename U1, typename U2, typename U3, typename U4
        >
    struct apply

        : quote_impl<
              F< U1,U2,U3,U4 >
            , aux::has_type< F< U1,U2,U3,U4 > >::value
            >

    {
    };
};

template<
      template<
          typename P1, typename P2, typename P3, typename P4
        , typename P5
        >
      class F
    , typename Tag = void_
    >
struct quote5
{
    template<
          typename U1, typename U2, typename U3, typename U4
        , typename U5
        >
    struct apply

        : quote_impl<
              F< U1,U2,U3,U4,U5 >
            , aux::has_type< F< U1,U2,U3,U4,U5 > >::value
            >

    {
    };
};

}}


/* quote.hpp
m4/DyvUuD5/QyLKFQjgBonTkJekGLw0WwsIcUUFoF9pRKVcdtrPXyMZHgYyKv0ZPXp9F9GMn2vvyOn4a46+YaOZ6qQph2uFmso3QntPn6k4nb4x2OtdVyo5PzydABx+w8ejsHE5mk3HC/0xJGrDZ4TSDbJLwv6aMAEejbOQDvCbny6bSogClFV5XUpHXLVry95Bs8p2XtQ0m62aKa3mDxT48qyZSLGuMyDMrtUrgzWAn2Nhk/z76YC3MCGWJIzr2MZfqMul63FM8aJXnMx5J22grXae1D3VN3/e7XPd9cL8H/kvKhjYhT3ojyJHu5+Q7N2Vvd2ni3pjHd5mO1//f31BLAwQKAAAACAAtZ0pSyEZGi5oCAADgBgAAHQAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDY1VVQFAAG2SCRg3VVtb9owEP5uKf/hlqnSVjWY8BJoFpBQW62VphUBaz+bxBCrwc5sp4z9+p0TKN2LplX7tEko2PE9d/c8vrsklhubMsPHJBFypfDvge+2SmdmTK4Xi2n9gPdXi2ZxKdYIAFbZnCT0aJrQBv0a5lw/ch0YkXGSaF4WOzzNmGWNPxq2Qui1Q5igC6XFV2aFkjDjnyuheeaRBh/DpGRpztG82+oM4M0l01sh
*/