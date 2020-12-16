
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
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , divides
        , ( N1, N2, N3, N4, N5 )
        )
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
OsKINmpiDibzZoJIaZa1iDXf6myvsfs4M939LveSvU+9P/qYWlBpjKGZ+r3an63SdwNnKhiNjB1Gfz6ZXxLhMkmuC6CX3cT+g51hf2ZbTifnMXZxPDD5uqeQgv4+jiAU5ymZ5tAoVLZwfQPOThWcmj1GBR4n0sVzYclmZkfrazvW3eXdA1YW9Oc2jowjKepQOpt9wxRUxyA91SgrNEkty0oFrtV0GjojnJsOdSe4U9333VI+ThZUOmMoSbqRviSZpJPnpLH6ipqKZ3imlqFD6Ds0jX6CM9ybDdHO4HyMMgqLvmK2qCpDzO5minnK7AEse9U+bLd2qNff+9BTEgsqif79vEG+JL+TOHWLukPdreao+9RD6lHwk1PqOXU8W8MesrtaKX0PkMHGHJUUfUR1mYp6E4EzXsFeZ9dwmjrtnUHOBOzzVKzbTCfNSXcQlSrx+P5hZDm5RUz1VTWEzWM/szZalnZFS9DX6+X4APFXnHiMSqXY3dwcb593yDvqHfdOeedwPnK9a4HnTymoxGKIoWHMZb3Yy2BHut5Gl3Yd59V/qLQZ7mJXSct/rm6kD87SOVSWXJymm6Q5O85OsXPsAstl19hN9o72Dp6nGm/LB/PhqATJfCyfwFP4SXle1jVzgec3zTzzvtnRfmiPct51BrrD82tyZkElFUN/Mp/swzn5Vs1Vv6dnaA3WmMWxliyeJbDOrBvbBG7GDRdnciifydN4Os/gi3kmUHQVzxGHxQlRRxJpyJbyFTkY1b+GecGsbTWxjmAuytsFnWJORSfGaY6ZXewUc8u6ptvUHYiZuR64h2ycAwydSSo5ToJVTe2vpuM+NJpKj9NgFoU7ScdzRmkx4JL9tXQtWO+sZ2GHxhnpRnvvQOA7dmMfYzhIyqmV1dNqP/YmC9aj9PNmlBVjDbVSrN3WGauM3cU+71RyDwK3ynhdAr93tKDSDcM+8oIMUctSSvvTZFw3nWahiuTg+ie0eH27/kTfZuTi6XP4GV5bTBJx8riMMztbIfYiO8b5xolyVfdVd7y7293nRnsGcDAfPxqRJmSJmq3+oJp0AL1MH9Ju2khtM7hjUT1G76+/plc0GhoTUcHPGg24zjfxw0DpSoILV4wB9zgv7om5Mkv2Mkeak8xaVozt2aNRZ1cF7j2voBKGIUa2wFEM8vfUabob53efdkg7qh0HVzinXdBytWvaTS1Pu6891p4FSFtkkP974eYnnhId5O+vZCDwKlpLi9Tr6c3FH8UNIaQj28thcrZcAgTZh+f92Ue1MmZds5E50VxurjPPmAWt0lZFS1oV7eb2WqeWK4Cixbwkb6m327sUuEcSpAzHsI5cJAXVN7Guv6kPgaiC9qCD6bt0Hv2UXqMRjDCqcS1Bm6svAH9+qpcwyhiNjUxUxefGFPEQiPqB7GBOM6+YyfZ5+yp2VC2nmdPOGeo8dXa5Db03AtdqHKSMwhClTlfnqJSeoK+xsay+RrVceU3eBOe7Lx/LZ1Ixg81QM8yMREWJNYmpmcK0zcHmcHMUqv9YcwIQJhXVd6aZZqabGeZiM9Pc75Rwy4Cvd3S/QH155po+jgUpGoZ25Cy5S0qrY9Sp6kJ1k7pX7UiP0rrsIntVa2g2Mc+bN1CzIq0lAR6eGKQsxrCMbCXVUJPWql+o+9UqdBBdRg/Si3SOtlwbpX+ub9IVI9U4b0RyjS8EY6RiudgidokfxZ9ENTDsDLlKfgnUOgCGd0f2MJNw56WtKqiM7aCLvgB3+Q5rMgMIaWKe2jh9nPlgDSud7c4jPElZt7571a3iUdTJ9t4OnKCj3lVwwiClJ+6tCokllLQic8lHQLsd5CkpokaotdQEtY86QJ2gzsW9rqQ=
*/