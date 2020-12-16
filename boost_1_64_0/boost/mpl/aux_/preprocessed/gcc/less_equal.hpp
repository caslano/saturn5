
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less_equal.hpp" header
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
vnf16VtenbO3YetMRDWS5yd5ropDZ7RyrcuzVqZ8182C7WEeHAnz4VhYAKdDC0yBi2EWtMICWASXwavhJngNvBcWw/vgElgBr4XPwBL4IrwOfgKXwWPwevgXWCr9isvl++0NMAbeCBPgTfAq+FtYAm+Gy+BKWApXwTVwNVwP18CNcC18AK6DT8Db4E64Hkp8THnGwjfyHKaOjzlaNYexNRwLQ2C8Kn2NpA83SN9D0veEwbAX7AB7S3rKLc811JekbwNtkj5B0pthCzgdtoWJ8EKYBPvDmTAOJsMEOBtmwrnQBq+EN8IUuB6mwS1wPnTFCxY7YsQO9VzOLmJHlNgRDVvBbjAcdoe94EUuv8izDJxi4JcLpP11hENgJzgBRqrsKZX04w3sCZb07WA0bA8vhqFwFOwAx8AwlT3Vh7zX80Ap3yCp58FSz9gm6eW5AYQYpO8r6fuJX2KlvvtDVxxsSX+hpFfHnZ4o6SeJ/snSTqbATnCq2w5+n72XY5jkM1zyGSHlGKn6Xm6R9BL/WvJik3ZRHeTb9/Ko5RxbHGTKvZxvysh+pBrZy/EzMoc3lr9PRbpP4xuvchyJn+b+xp57A9+YEee39m03cGwa+SE7hyPwgCIcPwmrONY6AT0wBsYhtfwt+Ea+WyO1HE/lWDb/LkZKEsgLen6n38rxCo5nYNveBHSOoIzK+fAk+6Fm0qygjEgckoFsRSqRZDN5yzzkTbCGYxUj8An/PgQjbnJ/8z9gJl+klGMD2d8GDyBB0x19Ad3hMeX837r7BaZyrAyGcmwrHAgrYcZ08ocrYNJv0QdNSt8ADIYrOFbNv08jzj6EAxxLgsfgGaT4MvKlwzRyBvnCEXCjkpZ/z+PfNmQr/96L7Ff6Htg/yb+DVrr7H3qsdPdBZK/EDs6pQuaxXwuL4VCJA5kKt3LOnpWQ/ZNwhXIMCVqFHngCaZ3k6LsYoRyDybCUuonhuGWVoz9jAzTq09jD8RI4NYlzSFMWh94k9CCOfg6YxHnQdAu6OScOJiOH4tCbRFmRUvZr2N8NW4/GLo4dUP59Bb6DsTCS40mwGNmA7CWvPfAo4uw3OcO/Q2dyPhKzGj3Kcf5tQZT+lHVwJ3IIMa929K9Uk89ppIJ/185E5yxtf8um1dLnwvHd/PskElxGmdnvAbOhZ3/MVI6XzaL8SBVyEikZQ97J+n6aKI7Zyhz9NRGFxJLk3yM4tgcmw2p4GilV0iKRa2iTMA6q+3cOcWweXMFxC9wEzyRzLjyGRMym3tdq+38i2d8N4+FA/p4ND7NfBuexXwFL4AZE6SOqZn8n/65CTrMfcSu+x+ZUZCVSgRxCTiORVuJuIhlIGbITOWoN9BEFtsAW2AJbYAtsgS2wBbbAFtj+O7dfof+/0GqRMQDnoP9fifW3hbTN7XEAyd1qS7MVWVNsmcWOfi/+fi9/j3L+PSstJ7eoUJn/n1VgcsQCtFHayzxiCKRK3+Y85BnSV+9yjx9INIv9TGy0WgqYYOnbnO5Ln9aPH5B+LVff0tPsu3NVz92WcQQyR/YprLUVLKIXju+SMrbgftLarDYpmrb/MokPec4++XC4Cz7H+alPG5XLmrMgHzcWOvrIehj3kt1IuainYXb7wtCmlPHjZ9xlDJEyqmw1GjMg8++lT0/pFpQyhcJV/E+xJrMwhSnMjnNPfPvzz/b02Wk5+eKjoxwTH9n3D8t+jvy9WvYXir6T7Oeh1DJkfk6BHKvh2Nx2ok/sP+3QJcesjvrg2J4o93zvWvZ32s/B8VYZm8Gxi+zHTKq+c7nA2BKlfSUgzyvt61mjerB7zef4Bpq+W63fZS6220dh0q6M2sww5/xmsXWG2DoNeZHzzc8=
*/