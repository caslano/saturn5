
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/not_equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct not_equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< not_equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< not_equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct not_equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct not_equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct not_equal_to

    : not_equal_to_impl<
          typename not_equal_to_tag<N1>::type
        , typename not_equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, not_equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, not_equal_to)

}}

namespace boost { namespace mpl {

template<>
struct not_equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value !=
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* not_equal_to.hpp
3FfkOJZ6Qev6I4GavoHgUP/HNG4JV/crn8v2qbiD8yvje5V0ZN5yOX9mZ6QaJb7tnJpinSbn1QHkJSHNnk6Zfdog2R9sacVS1so91fvW29Mq1UirQiOtKo20rmikpd62lVI33vE2ti22w+5s26LF9m3LV4IcqtXbNvQG31cHlhKXwy0zI8myzXbKeHYCX2GyHZfLtKREmVbLduuq7Luh8g5Yp3ctlKm+x5RlXGLc9l0ny73ItLY+jnW/l53aapRY46Vz2pB5LljnSbdv3y+U/NHpjsY5UMpblrOQ5ai2X79WTGMjqPeLe1iWUrisrsM2KZHbRtvleNuCvZXvtmWO20ROS279hji+vOZviJ5Srq7OEdclj1LD6rCPG02sX411sUR2bCtjcjzfmZprn+/C1ziuG/9luNPG7Fae7wZJHsslj0GSxwHy26J0lT2P/Bzi94X7+dP+TeFYNmFS331UtvshbKkci1nqdOVQlLIJvMF27222bvfav0cjqXBh4UyVc4nGcVSmcRxdcjqOSjWOoyt1PI581fuUpUWDwZavyxrHV7mc4+T4cixTClIZ8qVMN6IvZVpsVpepHEpSpn43KFP9YudjScpvoev9r1KOBxMp2dZZ1pFikPWoWeZynrfEY43l2VrHc06Vvaw4aBzXv7SF9vHms0a9/tWHW13aUNyK4836WzrmLu1rhkL779bspMScrFTzMuXiwa22HprXD6pyKbib/xi8Zb9ohkOVcllrTzN1gbVc3Gu3+BVxZb9wWU79mJkFs6eq2iC1tLfD1DuUm7RVlHIzUXBSvra2h5JROefKcSa/XWIp1zzWcwfjOZa8ybWfXNNlyXiFjFOwsn/Jd+piS5k5nBuv3V1zWw0nbwHVv1cpLQNZcq89tNb5SJ2W0Ud7v4he4ZAWLxNyPy1X15M+/K91zWKqPk4y04wGp99C7l833arrFmte9/C/1nVLZc28yomtfseLq2uXKtQ1vnVtocZ5K9PDvu3dK+ablZtPjJ/jV9F06xrXbaQ+sbTFMbfP/3rd1L1zNvaddcAnxKvMdRudsEBl+oSI58Yahn6X1+ZQ4PJPzffm8C4OS7rn3o39/PG0DuX/3FkU8VG3p6mwfrWFMr346uwuP4o/zs2Xkka+3zx2uu5ts9b7KdOvbDBuP9r2q2fK28z/7YXcl/rWvc3Wcct65T627/1PXwsKWvfa9KWp245WfH9tufa1tCw/+pGx5cfTQgoDL779539s6/X9tfH6wtLGa11E5l+/nXzp4JMdf1vy0KUN4+rexqs+bbn8Gsl9Pbnfl8cyAuR7RSfv8WiB41CP47ED3o9dcCIG4iQMxik4DKMxAqfhRIzBqTgD5+BMjMdZmIqz0YRzcTHG4Q6ch7vRgC9gPL6CifhbNOLvMQlvJ8/J2BQXYB9MwX6YipPwQZyCC3ERpmE2puNyzMRVaMLqNj9y7w/1BMpH2vzIwHyNFbAV3ibxwnVyLw9NEu92DJFoAyReECbiICmHEMzAwbKcYp3ck8MqWU5rPCzLaS3bxxd9sa1sFz/si+1wIPpjFHbE6dgJk7AzLsIuWIBdsRC74SHsjk9hT3wde+Fb2Bs/wT74OfbFSqSspQ2c3LfDCMm3ug1cc8m3t+S7BQ7Fu3Ak3o3h6IPSRlDuv7EvyPLUbQTNsrwl2BuXSvxlGIErcCauxLm4SrV9z8py/TS271rZTuskn+tV8UolXieNeJsk3mb0xzyJ16yR3HeS+1DEs8S/LvFKZD3ewiD8JQ7HdzEa38MH8BIm4/u4BH+Fq/AD3IiX8Sh+KNvvI3wTr+D7+Ilsv9/ht3hVjp8ybIGfYif8PXbHP8jxVI734x/lOPoM07A=
*/