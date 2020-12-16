
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitor.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitor_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitor_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitor_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitor_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitor_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitor_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitor_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitor_
    : bitor_< bitor_< bitor_< bitor_< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitor_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct bitor_< N1,N2,N3,N4,na >

    : bitor_< bitor_< bitor_< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitor_
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct bitor_< N1,N2,N3,na,na >

    : bitor_< bitor_< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitor_
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct bitor_< N1,N2,na,na,na >
    : bitor_impl<
          typename bitor_tag<N1>::type
        , typename bitor_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitor_
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitor_)

}}

namespace boost { namespace mpl {
template<>
struct bitor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  | BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitor.hpp
GQtwCz6CL+JWLMZSLMFPcCuW46t4Bl/DINr6dXme9wZOxzcxHnfhjbgbb8a3lfzwHVyF7+IL+C98C8uwDN/Do/g+KjFs+zECP8CueACn4kHMxk9wKR7CJ/AwluFn+AF+jj/jFxjozzUY6+JRbIBfY1c8hmPxG0zC43gLnsCN+B0+jydxN1bg1/gjhtTgvhTD8Gfshb/gJDyNf8czeAeexSfxHL6Gv+NbeAH3YjWeI5zE6liL/doXr0J/DMKa2BYvwylYC6fhFTgXr8T5eBX+DUPwLqyL92A9XIlh+DQ2wG3YEHdgI/VzTTkOGxo81+xfje2DAzAMB6L1e2WVfG+EfG+kfG8Udqkhc2dVMod/CA+RTbOYq4a0kffbsZwUkOLrc66YuYOKXc+rNbzYPrdWs79r59eKK/7PzLGVU/z/O8/W0mLP59pay3eKi92fc6us2P15t8qL3Zx7q8Q+/1bLkr/GHFwxJVWbhyutxD4X1+ISz+bj0s7FhSXuzce1scS9Obnionz/cvNyHShxPTfXiRLt/Fx+Wz2bo6ttCvUmmUgrScWkQySfVObtIg0npZHySZtJB0h+/IG3JWk4KY20krSdVE7ym8O/kaJIJtJq0nbSEVIIfwiOIEWR5pMKSKWkI6SAdL5HiiKZSCtJxaQDpHOkUP5o3IM0nZRHKiTtJJ0g1c5kvaQYUh5pPamMdJrUzMQ6STmktaS9pFOk8Ll8TsohFZB2kk6RGmX5+kSS4kiLSAWknVne+cq8L+/LnZcfKeMSj/9vSlwQm0PsmTIBANn8oTkAlHH0vwz0kXFHLGMn8OJZDve5mI7nlLixj/j9Zxl3jei5tFSKkJiSnMifcF3HAZvjfD+29pPPzFKPp/Eb6zYplTGvR/rx04gmBgUjl9Qcyc36nUAsknnMs/n/9SSOfBo/YKVcmalJ2bZxJ3NJM9PiZ7GsxOvqx8U6SRkyMpPoim+PnW7AZ1Is8lCNU5FBkfiy9fMK+X58LsMwyErU40IWVtePf3ae5Us/1ranbFKJSnR/TFpbOVVl/ymM9snNMhpbRBP/UVtO6x1IvqR2pJY0ZvlBc9mS51Mfd8dGtpbnFd4oX3OMdV7kq481ebQezyA+CZUYkIETxnSMHTto5JDBEz2MCX24nj7W+ZyvPubkCZYbYJSfhzF2D9dzHets8tPXt3oDnstI/hLzEj02asTgKbGRAycO9CzOxqeBPq7Ix19fZz+Wy3OepwTCul/3n8O0cbDRoZo4WG18n0F5alCeQqfl8TwGyKeB63jHwBr6cgTwvVLDcowZGznE83hHzgFG8Y6afWKlQTlqUY5y5+VQgtGrXIZXDOKCA2rq98va5j/COiuDZ/uHlEHT/iaDuQWuIM9wp3lWLc7ziEHdgsgnwmk+nh1zVxkcczkBjtuUxHLRTvP0/Jg76XDMtQpxHnt+OsB4HzM5LY9ncaeV7WPSJnSi05ehLmXId1oGz4/7qxq4jm88dplxfGPRodCLGt+YVMs4vrHsUOgli2+0zZ0jec+T+4ssUihtU2HJW7k1MA8Cb7s/8XE9RlQdyb+est/IPY16e3P/qSnDdpkjYKWUIZ/UqAF+qi1DbkZ6fA53jUkelEF9L1NHytCAdSfGsyJpq0AcFqS0jYz1qr0PkXtB43ulYfwD47TGO167SmVgnlFyHzwMGyvH9WF7nRi/OzE3jUFeza2byaDA5hELXM5N5OzerbZDm9eT+1XlM9pPPnV+n1fhYiyaY7x3bJcT8ll8xgIOY+25ZJeMub9W2qAQw5V96zOjNsjNTs5Squ/O7wHH+su5TX8fbxsbS3uPLeOBGdS3LSXni9J2trpFy48IqbO+HSpkXzAPvOk=
*/