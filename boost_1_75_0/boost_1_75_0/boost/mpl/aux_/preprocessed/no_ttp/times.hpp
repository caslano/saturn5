
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/times.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct times_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< times_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< times_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct times_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct times_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct times_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct times_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct times
    : times< times< times< times< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , times
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct times< N1,N2,N3,N4,na >

    : times< times< times< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct times< N1,N2,N3,na,na >

    : times< times< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct times< N1,N2,na,na,na >
    : times_impl<
          typename times_tag<N1>::type
        , typename times_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, times)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct times_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 * n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct times_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::times_wknd<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , N1::value
            , N2::value
            >::type

    {
    };
};

}}

/* times.hpp
+9oZyIu7jbhc+slip/3SdZMHBF7mtbsRn7MKOaS92fMF06j8IxJZBzRB1rZSz2kqUS3Rh2iK2XafhFK+AYIWE5gtDwkwwzE8ZufXg86L+8l1SnJ9jljltcOhm+tfuattvJAJng3ICPcMJtUsN5/3AGSzBpSvFp8E5v0OW4r9GHc8ih8x4sq30Q6770NCHL+HJ3aVJDAdlIfvNGydWg2vrblt9Pz5SJBf57hFypg2rgNmOqUjVSBY2vUnuhGD1+YMnR/JunJkxcnX2FIsaFXJrCmUVs7RrUCXRQqLRjfFqyx2CNA1fZ2ljPqcy1D9qyspd63KXQSA0TQqG5+YD6ldoO6mEn1BGd9qzuxF5N0IsrdBZf8qTTihzSsCBAwOk3ipVs1hiIDQxkVemE6R5bMh6El1f21yrwLXqW73m91FSSYa5mX6gQrySrUo3Cc3ha9TMU8X0rnFzI9nF3WuLXDXOZEGdR1QpzrS5rPU8u6tFg88Stjnt5OssstvYMiHPKmWv9Ro24zMBiRPJf889iwf8mtqpxanatRSFskgW5fyubqHoHts2Y/O21X4PxNicKVl230JnCmxu3SwJbz0QgT06Duvve4jA9EQLZr9deN58wTAJ8p826N19dUL7Zfl+mepDcP3TOk/u9zJzWK1euw2SIKmrezEVpPNiuWZ3N11o/RvhjzQhVn0LwtYjOvqvVt1KuP0VxhWauiAK1po
*/