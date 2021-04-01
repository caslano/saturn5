
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct equal_to

    : equal_to_impl<
          typename equal_to_tag<N1>::type
        , typename equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, equal_to)

}}

namespace boost { namespace mpl {

template<>
struct equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value  == BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* equal_to.hpp
tCGEfpW6w7TdSVaphR00NwRxLiWVWDHF8PYKiKIjmA+7bCuTqVY0y2Y1bcyfcsdf1t8vIaCcE8IopOhPFD6TS4QC7bH4vbE0SyLe7clE4T3RKFPDRtLilrIVZYyR2B/YTCueDhJWBcUtRBoXYvoxyBgWOtA2TjQPcLp6WFzTnklP8JIpFWEEsLrerD35kP0nvIn8dEBDAp0cVp/soFyNsb+laJXwHaZmTu/ms0yY8Isk3aOBrGMMpVeim+jCaW+h77aGpiuxzm/TJ9GwVMwAgbXWMZCol6ZWGOF8MVS0EMuY6I2cBy6YUF1CfHxmPih2Kg/QCrS8v/90jnX1t2+l0Doq0SsM5kVEwHT/LDBgBdS0Zbi0Ny0Y4PJw2Tyw6GXuaAQKvLoMLThrD0jIeewiAwBDi1nmSo7a5/jt/oAD8natkJ/5GmQxVWPql4b/9FRKiuRUoYBu0lfyhHJ7R1s7m2Ysfee2KMi6x7j1AR4z7K88eh4cKY+qIyd6SMlDxuM8kw8f4QT+QJdpyke6BSs1P6MFS+6e+WATJOkN4++wo0yhRZQ5Lx0UXKM6uA==
*/