
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "plus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct plus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< plus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< plus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct plus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct plus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct plus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct plus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct plus
    : plus< plus< plus< plus< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , plus
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct plus< N1,N2,N3,N4,na >

    : plus< plus< plus< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct plus< N1,N2,N3,na,na >

    : plus< plus< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct plus< N1,N2,na,na,na >
    : plus_impl<
          typename plus_tag<N1>::type
        , typename plus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, plus)

}}

namespace boost { namespace mpl {
template<>
struct plus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  + BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* plus.hpp
JceTE8nJ5NfkVHI6OZOcTc4lvyXnk9+TC8nF5FJyObmSXE3+SP5M/kquJdeTv5N/khvJv8nN5JbLvjAlSolTkpSUlFQpt6WkTrk9JU1K2pQ7UtKl3JlyV8rdKelT7km5N+W+lPtTHkh5MOWhlIdTHkl5NOWxlP+lPJ7yRMqTKRlSMqY8lfJ0yjMpmVKeTcmc8lzK8ykv/J+xqwCP41bCLixL2jLTK3NjB5pyHdtJ3CR2ajtpUrqefWf7mrPPvT2HyszMzMzMzMzMzMz8/r0FraS9vPd9bU7zjzQajUYjWO1a21DbSNtY20QbodVrDdpIbZQ2WhujbaqN1TbTNte20LbUttK21rbRttUatXFak9astWjjtQnaRK1V206bpE3WpmhtWrs2Vdte69A6tS5tmjZd20Gboc3UdtR20nbWdtF21TLablpW69Z6tJyW13q1Pq1fK2i7a7O0ojagDWolbUjbQytrnlbRhrXZ2hxtrjZPm6/tqe2l7a3to+2r7aftrx2gHagdpB2sHaIdqh2mHa4doR2pHaUdrR2jHasdpx2vnaCdqJ2knaydop2qnaadrp2hnamdpZ2tnaOdq52nna9doF2oXaRdrF2iXapdpl2uXaFdqV2lXa1do12rXaddr92g3ajdpN2s3aLdqt2m3a7dod2p3aXdrd2j3avdp92vPaA9qD2kPaw9oj2qPaY9rj2hPak9pT2tPaM9qz2nPa+9oL2ovaS9rL2ivaq9pr2uvaG9qb2lva29o72rvae9r32gfah9pH2sfaJ9qn2mfa59oX2pfaV9rX2jfat9p32v/aD9qP2k/az9ov2q/ab9rv2h/an9pf2t/aP9i0X/QvrC+iL6orqm67qhm7ql27qjE53qTHf1xfTF9SX0JfWl9KX1ZfRl9eX05fUV9BX1lfSV9VX0VfXV9P/oq+tr6Gvqa+lr6+vo6+rr6evrG+gb6hvpG+ub6CP0er1BH6mP0kfrY/RN9bH6Zvrm+hb6lvpW+tb6Nvq2eqM+Tm/Sm/UWfbw+QZ+ot+rb6ZP0yfoUvU1v16fq2+sdeqfepU/Tp+s76DP0mfqO+k76zvou+q56Rt9Nz+rdeo+e0/N6r96n9+sFfXd9ll7UB/RBvaQP6XvoZd3TK/qwPlufo8/V5+nz9T31vfS99X30ffX99P31A/QD9YP0g/VD9EP1w/TD9SP0I/Wj9KP1Y/Rj9eP04/UT9BP1k/ST9VP0U/XT9NP1M/Qz9bP0s/Vz9HP18/Tz9Qv0C/WL9Iv1S/RL9cv0y/Ur9Cv1q/Sr9Wv0a/Xr9Ov1G/Qb9Zv0m/Vb9Fv12/Tb9Tv0O/W79Lv1e/R79fv0+/UH9Af1h/SH9Uf0R/XH9Mf1J/Qn9af0p/Vn9Gf15/Tn9Rf0F/WX9Jf1V/RX9df01/U39Df1t/S39Xf0d/X39Pf1D/QP9Y/0j/VP9E/1z/TP9S/0L/Wv9K/1b/Rv9e/07/Uf9B/1n/Sf9V/0X/Xf9N/1P/Q/9b/0v/V/9H+x5VvIWNhYxFjU0AzdMAzTsAzbcAxiUIMZrrGYsbixhLGksZSxtLGMsayxnLG8sYKxorGSsbKxirGqsZrxH2N1Yw1jTWMtY21jHWNdYz1jfWMDY0NjI2NjYxNjhFFvNBgjjVHGaGOMsakx1tjM2NzYwtjS2MrY2tjG2NZoNMYZTUaz0WKMNyYYE41WYztjkjHZmGK0Ge3GVGN7o8PoNLqMacZ0YwdjhjHT2NHYydjZ2MXY1cgYuxlZo9voMXJG3ug1+ox+o2DsbswyisaAMWiUjCFjD6NseEbFGDZmG3OMucY8Y76xp7GXsbexj7GvsZ+xv3GAcaBxkHGwcYhxqHGYcbhxhHE=
*/