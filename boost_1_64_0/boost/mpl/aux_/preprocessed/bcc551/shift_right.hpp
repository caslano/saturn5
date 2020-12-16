
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_right.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_right_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_right_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_right_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_right_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_right_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_right

    : shift_right_impl<
          typename shift_right_tag<N1>::type
        , typename shift_right_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_right, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_right)

}}

namespace boost { namespace mpl {
template<>
struct shift_right_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  >> BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_right.hpp
3k1h69JNN7a7u8TFvo52Ve1J34PwvJWAHgT3ANNwR9q8Zt8zhJd74fYK4cy9nHuH8DQ4iwKTZh+pSVFDsMviq7eyoZFm33CNXTM0+4Vq8KyJaEmo2V9rtrYr9QZp1INS1BwgNTm7ZDuNVo62vrCoGzUHhmuk2+g8WLgGa50GFtpfenC4Tu2ROyScRzcvCvyhBu80HPCycsDa9nb0fm4Y7lB72G9qKWsOvxf5cK+Wa89bL0eEalS9YJpHhmoorQZUjGgJ0mdHhWu3LDYdmTDaPLqzjgwXK+LWLGqP+R2tTL8LtMf+nrbedMbAQ9L2cb+nb9pbuqw9vrNWmlX1dMJvaF3pOLZ7YgetvaXMhKPOgpz0G1oz/ZM76GAXiG5QnP4pHbW6Llz276m/o8Wt6nZTtcHTQvXkAvAApn/6b2gaRdel9Qefk/strfHtozNDdbjVAPmzJJ/HL2bJRl8v8zXZ2YqH8tAgw0/0+Jmeh2+K+MqvUnNuUKP9yZrzOmmqZdGssczn+zXBzoe6C4I6XSfFFqxJSXdhUOevO6yXi4I6HIylrmQ8r7s4TAv/K/lLgjyfPKA8XdqJhwLSzEO6y1gnLtq7rYTdFF9nKsGwTt99cmU7udyjy9lbw3JeXHkIwySlOfUKU4clIvxKL96Ue9qu8uBN2bhEW8Z0rw7ndTvmer/G0PX4JgY531/r0ei8XefF1R7T601cp00x5XNFQyMrUp2vMzi+kWC5VbhNAccHZPybDI0iOf7NHq4FV1fFphZR3m+RmlK92qCNzPRMkXHeOEDPFE0Ml0yE327iab1X7w6N6yUB27qTOTUJcX3e5cPVaoPLdHcYr2qTbNwTrgEj/NxR8c6YXocQd5+X4zbPzx6ZU7Mx++oBiY8Kn1A+H2QMO7J30FPf7XjIo9EdTV5fPmzysttx3Ec8nM2rwQIMp/wsUvF6IJH3kR8zORyCKc+PG3inPvCEoaE+4CL+pBdvVviZ9lMSd1yojlYRzkqqM0dPM4f14ykDP380eVkGShNtP2vwyjjXyXPMYTT25/MmZjWpfPJZo8nZZeqOxVaryePXi514+cIC1r30Gzrx+R6pe/m3dK1tVX94xaeDXTJ2y0Yl2nnVy+tXT3B60s5rQR0Z4X71epA3i4eaNzpoOCnUvNlJU6q3a3yv5i2laUHPq2L7eVti7ZociTDf72jc8JQu/7udeJ111L3XQaezT7r3ta5TzWA5P9C6kJohWx9qTafawTJ+FKZDQ2Tn4w68LiLpPumo4+RY96nWdaglfk7KOh4EsQ997sVkL6LnpchlB/VDairflyYu0uKNpnIO+yrA63NBX3s4fU7nG4XL5kJn/aTNbyUv7sLDzEcs2fxOciIt3AlL+PceXO+x/0Hh28MnZUn7I2GZfjzYoPck/uTFRxvsy58ljn6hevhFYjhoqjeWiGPczhhuR6SyxMYzdLzxU5ZzHJMTdzTFooq5cTUXeC/AeIpz6LQ8avQ3o8YP431n7yfwa7Q/0caEoXzbbWIX4Ge1YRq6mEd+4gDvevI5SZA30iDfT6o0lXqRz+ZP5sF0/U3uwfVZ7CkUzskUy2rtOKXiworJz2i1JphN9ufUPo3YkgrPADaXdT2Nn8c8UtxpQzlsRMhP5+dxc5neVzy95GlDMB4vkOWbQXH6xTq6D5PfZjQ19CoCTHcmxHMDVjIN9yCHsurkJqc7cwgv74XNEuQ89xFnJX7DoULWgm/08mdzyR+zhXJWQ+71m93HC1Z9N9bH6ZjUb+c0+MKauVQ8qc4SV8RTCum3uQI6HKzg+hYu6djW3AGNee4YdGxrnlCdN715gxpoPyyS5wyDGjEwet7ZMX+4Rp3BXiDA4w4=
*/