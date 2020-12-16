
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
87Rt26ykLW6hq21tx2+Pvf/6j9n3XFcr56u9F7/3TOA2Mfs2z0BtYgHfgap7CfSbAevaPAuls+4lOAtrm56hUham3wP6ncB6tAdR9grvzHwOI/F5bIkvYF98EUfhSzgOX8Ys3Il5+Couw9dwNe7CW/F1fBjfwK1Yiu/hm/gVvoXf4V+R51SRH9LHt7EN/t1IH/dgLL6LQ/A9nIB7cRK+r3I6qnl+A/DbQOXsxr/T9fsrXuUcp3KON71jsAMmYFechL1wMg7ARByLU1XuafgbTMKleCmuwhn4B7wM78UU3I6p+CzOxOcxDV/EdHwXM/ADzMJvMVttk7MxTM96qoM52AznYmvMxfaYh13Rgb1wHsZhPo7EArwUnTgD52MBLsCFWISLcCFeiZfjVbgIb8MrcAMW818JXomP4lJfvev3B/uOTb1frXq/RvX+W9X7ctX7CtX7tar3Var361TvN6jeV2Mx3ohX4814A96KG3ANbsbb8Rn8Pb6Aa/ElXIc78Q4swzvVFvwH1fcf9Qywu/EM3ICNcCO2wnuwA96LXXCT6vs+PBc3q77vx3h8ANNxC2biQ7gYS3ApPozL8BFciY/iKnxM9b1V9b0Nt+NT+Az+yfuMI/32Qba/3zOOupnuEYrEXtgZe6ue++BQ7Kvjux8WYn+8G2PxPhyMT+MFuAPjVJ9D8RAOV72Mxs44xvzuunG+tuMUgrlN+KhpuWIt1+w4y60/znI31wirrG3Z2/4cNy48wDvuzO3Mfu+1U9uyXbty5e+xK+Jvak+mHdm2DVntx9a2Y2sbsbl92P49dP0Gm9uE/duCNxCsbcB+7b9+bb+JhCICbb1q57W8S05tu37vjlO7bhBtuqh2XL823BcItN3qvXB27bbBtdk6WN/cVlseZ3n3G220J/7Ot8rf91Z5G63aZ3nHG2VA/zbZqrXHHsJYTCKo7ZV2V/s2VweBtlbaWP3f0ab3s9G+ynbF6WhuU1V7Ksd3uKtNtQhvI+wgfESoPZ5n5RCGE7LGh9pXQ1NoCk2hKTSFptAUmkJTaApNoSk0/Yz9/+nZ+afi/X+e/v+dvv5/YvZ0/7v7/8dREk+fbUyA/v/SOL/+/6zUgiwjsqDGAHj6RUdrDEAjbID1MJP4y9zxp6arJ5x4g+4XTW+nflFT3y/rB+z3PaB3pxVo/ojmHWHuZ+71ow76ka8VOHSokS+/Z9/p2XiKp8DXPzyYus7I9fUfF7IsL8rzvi/pz4rvn82sfYpbVS+jVO8jCBcQV/GF6i92bTZizl8YRN+mtX6UJ0vfbT+NS+ir9HoTilmuzJyeexOnzXUEn9YS4kjVfH3Nz0Rz2huUdgulHUXIZbno4X5pU9TjjzFporTPJw5jrTCl11Pp3awmne2EBoSthASWLT/PlR6Jufrhg34n18n2wzex9sOznPV9Y3zm3d+MfTsnnb+b+ubJsGtf6n2+p1/eWt7a6itPVXlnEJL4y47+rvIadeo9vsKDLG9OofKoPBG3Zf9N0jvkjOcWNcdvyMNk6jhugCtNns/pPq7ZuLyW0v3uTiP9ftWCezem8azPthcQlzE0ITebjWzNX1GO7x1pc5t5j3fvNolmmdzUud5zQCTWbmIaB/ET5TKdR8qZ78AyWYrj0590jsgrcGZmu8eZ7Oaz20irgHE/3nPLT9YxIx9pfrYnL5Qni3TSU52pnnX2apk89fuHsUwy8c70nJ/09zmaL2PeyDvJus5X9anr4dT/2nCOt4G+81W46XxkpL2L9S4j7SxTfg958puusTOs4zqOjJV0PlzFNo0j/mijX2eQL/56el5pmpY7wHKxLNeG+cRYLafnin4UYdSTe58heM+HM7Xc3HbWfXg=
*/