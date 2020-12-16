
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "less_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< less_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less_equal

    : less_equal_impl<
          typename less_equal_tag<N1>::type
        , typename less_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less_equal)

}}

namespace boost { namespace mpl {

template<>
struct less_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value <= BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* less_equal.hpp
87aLHfq4Ds8YHPDQx4s5H17C+fAyrjuWc91xtV/nJdeDw6S9+VX/r+R64la/Pq+4za/jzRq/zjPu8Os4e6df56d3+XVf5m7wXWmf9OF8j199/N1HH833S33Td/I00Yv00byRvpn/AN4APgje5FNfymt85hmE0asPg5gjG1/KqCs8lzd61fhU3ukzz6bNfvvjfvWx9oRf992flf0A8DnwC3AbWO5TH8v0EcszFCgDlqPTR+woluNoluNFLMeLwVNkfsV1UyrXbeP8ur+T5tf9l/Fcb6T7dR6XAUqbyvab8dz4fLrH7DXoOiCH66Jcv/rUzQNfkP7r1/2YQr/6UCv26/PDaX7d35oJtvSpb+6F4GxwKTjHr+vxuSD8jxufQSkI0X0Oqa3mNpurt9fcd7O3X6BxuE7bzdF9AnWJ7heoDIyw5RyDX6CizeobaEyFfec4fAPFYuN5F0g7z/QFFJ8foCL6Alp8rtv+89Zzq/YJVKeb0xZ0pD+ghZttm9Al3SLtQq/sFm4bGgG/2YwQ7hfI9glk+wPaubl6u9GLwXFg2WbbfvQh+TeuR7UjvcX2BdRii7c/oDJ8XwHWTvL2CzQTHIB7k/D7xUlhfoHitDudIvIke9ufbpIcaYM6Z4vtE2ge/t23St9AuCc50jb1SlzbiLByi9tGdXkUO9Xrt0T3D9STPoJyqvETtBrciLCzCn9B27b8MnvWVfkK2r3F7S9opcNn0GawJ7h/i23rencP3PuYl81rb/9BjZch4P4khHEI8xDWI+xEOIjQ+HHIijAOoRRhLcI2hL0IMmAkIiQhjEMoRViPsB1hL0LwSciJ0AkhBaEIYTnCeoTtCPsQrKdQVwg9EcYhlCCsQFiPsA1hL0LtpxEHwjiEUoR1CDsQyhEabIV8COMQFiKsR9iNYD2DtoTQE2EcQgnCcoT1CNufqbH1XfOp+dR8aj41n5pPzafmU/Op+dR8aj6/5PMb2f8vyimcIA4A/iX7/+Lfr24j7A2PDVnYnRgwPLV3r+QRI4f1Ss0uysxNLSqy1J5lfdxTanwEItnUCZlpRcVTM1OLxudY6v/vujqWbV+X+8fHIAT4zOE0+X0X856ZI5H43lVcRltZfKfN4a/AbYOhHPcVMC1Xhqzq34NthLw2g6wFpjyMEVD80G3Xow2Xy/WZplxsid+sjkwTb2NXn6bL5qBEGGZjtRXiTupk4s5uNy3VEX/1Nnkq3tG7vH6FzRC+o8fydNRm5Xu2q+oZe9C0t+2205Ntud9lnMTvti0Rq/LduXqWiR9RZSNV9/vcMwNh9cYy3NqF7xC7TKNUWs+o9j1qp/2E/UzD+e58G6Sx0zON+OwnnNko0n5CSdDc6Ho/vB3uK/dML377CcvC7Cf8UDe67YyDHrJ0kPdiu3rJYt6Wj1uOivdjUe8RdgtmhiLTP1veIfZMP377DWc2qt5+xn7KEG47ZUjXX9d2SkV6OQnmxgh7IQVd/732Qip0xzba+XfaG+ooZX6OvgvdLjtSd3jbnrLt6O/tjN/Snm2kLrHluQ/X0otKcI+tQ/KMvxX7XWXqmwkVOmWvrTOoQ6LrmHqVdveNbpKYae+K1/Iy0ASpq+jrBDfx/d4IXWTe1d1nygXnePiO+fGd9XuXRva7uzujv7sb9d1O73d6o7+7O+JouX7UztoLJ5z0frdvHu/wcMPcflnR37n1ftc3/ndxvd8xjv5Oqfe7u9He0Y3/nVvvd4CjvXP7673b7P3ubvzv6Mb7TvIiU++Pd+s865obj930fLfuj775+dM50d49/nXf6U20OB/jPC3F7z4T0tRxdqSA9x3ucd/xjvtW8776VcRXanEuwzlOSti7j90sno209Aw=
*/