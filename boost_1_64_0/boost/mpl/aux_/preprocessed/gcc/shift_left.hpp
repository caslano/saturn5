
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_left.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_left_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_left_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_left_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_left_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_left_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_left

    : shift_left_impl<
          typename shift_left_tag<N1>::type
        , typename shift_left_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_left, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_left)

}}

namespace boost { namespace mpl {
template<>
struct shift_left_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  << BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_left.hpp
r/Boxz/ITbUGxdB3bxNP765LtlF9D8W22jXGH9t7084jq8DSAi12kZDcuWyO7bO8Fe6CaJr26EQn3phF68nNYDOLOrT0PbAZTDnjbcPrMcw6IOqP29knYfjbReC+qoxqrSpwrqdxa5PVBWCWO088EuOKh110LuaoIkL4Wzy/fajAMsddRZsVR6+Y/9twhG/7QVQTWqorzBM9MFKv6jbK/RYo1Bgu6km9nHmf5DtTfEKpVcmGMRRCyI+rUsg+2CqZP81YaU54Rk5YKXjFgCXnlgs7RnyDqYyMXZMh2ICz+9Ucy52VgQs3+ZzH3YqzvVtZ5xL54nD/lnSnRHEcGOZuMLgb7Qbc61hK5q1Lj/rYqhfAjRQ8P9Xv5SFbBEMb5lNZhY/bwzVRgklOyJXLdMsqgPou4V2FexlBK/JMHEX8lg4bx2SU0wxtyo1YxrslHYKlD8gsZNBXL2+B6FSMdFIwX/iA6IfoTVFIyzBkDo83KdlhdjfDD3UEC7nVXFi9Si4I4svi91waHwjoxwUhHlUM28TYjtlYqJYg/xNwauAwt6juZW6qbhN++6YpjA==
*/