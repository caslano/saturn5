
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/divides.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct divides_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< divides_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< divides_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct divides_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct divides_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct divides_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct divides_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct divides
    : divides< divides< divides< divides< N1,N2 >, N3>, N4>, N5>
{
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct divides< N1,N2,N3,N4,na >

    : divides< divides< divides< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct divides< N1,N2,N3,na,na >

    : divides< divides< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct divides< N1,N2,na,na,na >
    : divides_impl<
          typename divides_tag<N1>::type
        , typename divides_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, divides)

}}

namespace boost { namespace mpl {
template<>
struct divides_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  / BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* divides.hpp
KYG0c1+6zT2PHetTnevk0qZr+18m+ewrzyJ6Sz6Lnfn0LmwybfgsFT+HMMoraXqef0ib7dqSZk1Xf4MirzRzcjXJ+jNvk2eeF7PnH2b9qs3ajpn1RzfrJ23WVs6sH3ngbeWMn4sEPpZjoM9jTNo8mrShC7ztnnHbusD70xu3lQv8edX16n5/aPuDL779+uwzC+rujuwY+tMo+qDPV/fLp1M2vb3j+ZyXT5WXdIz9MNnsOVngbULleZWcJ5Tzh+98Bk2lf3QLbIbR2BpbYg9shYOxNZ7GaYRiia+vxBeGSRJfO3n+1R7D8RKshR2xHnbBhhiDzTTPx3phbyRIWyP5DMtnWz9/Qz9J51LJfxxm8UKfD8IqbCsU19fTt3qTH+NgBjKu/1F096fm/9PGBD6uf58LMLY//aYDGt9fM7a/X+P6n8+Y/g3HeY3rbzSmv348/wrH8f9vjuFf0fj9SXdVO+8x/P+s8fsrGrt/Cp+vhYTCD4LPi4NLcAkuwSW4/HeXP+n+n67O53//r7QBOBjLPY16/2/Pt9ly8xzWNCXy/Cyrsw3AIf7eVP17Zk6mIzMlK3O+5x3yfKB7lEXmvPf06/hE7n8/InTgS3XEOuc4AmNGX65Mwd3NNdm93ArLvPL+zcvsmltZttHMwytjCPCcoNU64/nuQyv7zhH+T8oYs96Tv0xn8ZR8Jqdnpcyw+3GP7hqPbj43Ftlp3mkurOzbR/Z90ow3SVP9rx9jBpwtzTKDcn5AmokmafIwI6A5pCVNr77AGVV80zxCmtNM0sy35yWn0en9XNN1lfVIFeOy2ozT9WP+3YrTTJOHWrUkzXDCR6RZYJCm/RyOo2slzbqu+YYJEodXnZcb5OMo+Sg0ysc51rnkxT1uZxXSdMej6zO7XObg7yD5aU/4hPwUa/Ij2UlJS6s4D9pnbnKMuuvkMPFmKu2VNH1lh0RST/Kadn+FXOR7jHzK9pZCT74MDk2/8zeOOrIRgUWX7r0X+e6fz0g3wjdd+/mma75/PM9FQ6W//tVyfp4gzyhjfPJjT07nlG/P8O8ZrnL+VY4T5VjTp/mrpBkh46uG4xfUQZFvmmoDMdexGenHsanOxZ+TLseE97NZOSY8nx3Z7qRnznbWPWOCZmrGl2lCWeZkWdzPom0hrMsE/9rxUh8kM+r5xO6930/IRexdqee3CV8q+/0h4zLLBdCvcVCfVuOw+Mxtr0QhnxG/68N1PV1PPSqXYu189VJHsn8911z9/p0nt9+7pKzbCcU8xIt+2Les+TlKaSu+zrv2r4OQkpUl13jNfpJ8j5Nzk/YctE/67XeT460znlTq/hFPfmwpeXYm+6envP9jGSmVp2yRbPGei91utXmNy5OTa7e5zkmR+FWsbJc6Xd2uoXxGU/JmyPHmrmt33ROZ13jHatoM9pvnkH0mrzmy+eqY5vxtJPkR7zGAbpD1N6Kc64/KOvlR14/r3l/rUc/ftcdyJ5lTP1LOYXXlnLFCfX8l+UIq5wzm5Q/kd43uMl7wcUkjRPaZBb9VzhHONDyXDD9+U3IdOzO7cp2258pnwfcaEmFwDYn0uoZI/ctx5pBzmzbfu+XD+rAc++sJp2L5Z6M235xJ0wI7zrT5LPNO3/izIJ9Pm24s55xUbifkt7N6G72Ph1tk/VPWtWM396EgyrJY9vciwmDqpERfJq4O/uxnV7nc1wfJz2lJn/r2qtNCSX+QpB9PGM+2BZu06XOkBfAdWc4TXunsreV844tyzD2H3yltor3SUe57Kj4vK+MiJTyulodB0jg1y7m6i/M1XjC8Zp/t2OQ1ubZIOSI91zvZ557zRn3NPifHnGs4a1rT3Mevvu7XPEa+5PhX1oc=
*/