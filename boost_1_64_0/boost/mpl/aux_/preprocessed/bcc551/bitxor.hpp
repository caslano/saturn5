
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitxor.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitxor_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitxor_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitxor_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitxor_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitxor_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitxor_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitxor_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitxor_
    : bitxor_< bitxor_< bitxor_< bitxor_< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitxor_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct bitxor_< N1,N2,N3,N4,na >

    : bitxor_< bitxor_< bitxor_< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct bitxor_< N1,N2,N3,na,na >

    : bitxor_< bitxor_< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct bitxor_< N1,N2,na,na,na >
    : bitxor_impl<
          typename bitxor_tag<N1>::type
        , typename bitxor_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitxor_)

}}

namespace boost { namespace mpl {
template<>
struct bitxor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  ^ BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitxor.hpp
Nbf6mhubo8Y9toa9dCda7rWyNhpqCxhb5JM+nyr5FJSPL02ojXItXVhsbEiolcRmSZ0kn7ZwmPb6Ap9aw/Xcn1sSo6FAaC9p6xP3tIYozGviOVOWzfKJAZ7xSj7pGt3CedbvjERrm0PX1Da0BXcab7c1MF61Gs9KDPvjo90hW8NOGRwYC2wN/lADT1MYX3ejraEh0CZ3x15bQ6Of/fLX1DY0c54hY8jWoAfz99kaWv3+3caIrSHqp6bMNbXsHQzxtnZtLa3ZovvutziHmK4WrlUbWfmD7by71+frawsb75bc2G7J1lIfv66eRj4xNu+Nt1VzaKXxattb94YZaaOUtOfMdfFVjOmR+mZOKtVWHw3x9cAr4rVNpRw5Y5+GlX2yEyP++MEPJtKvdA3eR7s3hMI07FttcV8mOen6qW1lJFhT29iy0nqf4BzrA9zoja26BVrDQeOV8kk+GBcnUhnXtFHqrxu1O5uoFvo0tdnKmHdhcfPGIuPpCbWrEePSxFamIvW07HmSHmnWvebmM8+4dWd9kFwPSJn1Noflk+6L9jUrV8AFPKpJazTRejIG1NKnmXORSbChuZHrujZYzyntra2PNLYzr1xT23zqwn1klf+R8Zg2vONRW4SC0lS1URmjDe4Wtacml6fW0Pfi42mSlMi/sy36mJ3mKQv9tD6q2/zHp2K1e9q4V9RKIvdlUuOf3hw/OgdoMe5c/VzrN/yJ0VPjmNFGHtcwD/XpK/jscnZ5qi9/uMp43O/Izi7/L8sa3RnSeHfzmHT+4/vaM9P5V2jMovgUflq20ZVgnF3+8UIdFfP/7cY2o5b/bzGu4tNW4+XGlcS38v/L+czCnf2Xf6Z+9X+8S3vEF532O9fH/vneORLWkF/UiBjN/CK6kdya+Qv0fnIO8hc7QvJdv2xDSxYTXqC9RtrV2G88n/TNbNPCnz6rZ/t9lKaemD/+u0X+hYCfv+/0ctb6WbuN/yqJVxkR9tlF2k6Om09KE0bZ6oVGAf/t1f952Sa+Xyv/BSTOfo2sZ6EezuHYp8paTmglN86BfaL8P8R+LI89Nls1UcIIaT5iAba8hhgplJ2Fo9hX8+Uofta0npbfBWxB4PwbJEqJPWwvdRXV2wbJK7BaCytH2Knzp2TkcwWl9bFGnh+exr4v16VuJMT3PXXs4OPm4SUE+I+F6ymVvHTNktomNfuE2qKa7UPksZtjRNmuiPN/TD6ProUz64A/b3cp+1SyVaM+g8265fatnFeTzvfMNIs8XsB/JfSiIqOQ2IWk/b1yXkZZoqwL6ZJ4dQrnjqs5tuoYPUGXt13amC151tLXwnZp5TN7N0u2vjKqWVtPaivr60/vQ4xXo0/gXxueXc4u/yfLOH/CAH5a6Lmg+oK+C6YvuLDo4qLLito3Htx488a3bZzc+NWND2/81cZ1xZnFxcXlxcHituLu4v7ih4ofLv5tceIm76ZNmyo2Xb3p8KbuTXdtunvT9KaHNv180582WRduurDywroLRy/83IUzFy5ceNlFV18UuqjroumLfnrR2pJzSnJf+LwXXvDChotbLr724psvPnrxpy7+2sXfv9hd+vTS7NLi0teW+ktjpd2lXy79WukPS39buv6SnEtKLnnJJXsuiV3yxkvuumTiki9f8p1Lfn6JujTv0hdf+qpLP3DpFy79/qVLl778RY0vOvKiO1+08KK/EnbdgTldffiSkCCSIPYKYgfnnnPvPefcqcQOYtSoFbVX6NfUqhFtKK0RlRKKRhuzSlpqU63oZ1dL7aqRoiixKR/f8958e+af0/Hmvfee8fye8bsoRxUfq4qQGsQkC9lOtp8dZb+x31lprZrWQhuqjdEmaYu11Vo=
*/