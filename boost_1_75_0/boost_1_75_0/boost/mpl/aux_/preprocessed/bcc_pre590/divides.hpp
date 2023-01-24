
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "divides.hpp" header
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
sTOp6rodmYxFVibmwDBV2S8K+wy2ijNNZ+UmIzGkSenoh1cIVI0yWmwdtxlyQC7JCMdp+j1+KMbHaIwk2bqTnpnFn6R9o8Cmw7yAByULWei4bqaRcE6mWFpLwWzZqLybJLGxidKtXF4nkc9OETKvVzPILqxV9K7I69okBKXNf+LwUyum5uQIk6XbJkm6sqGz7WRs4EhsavZ5dskXFS8SsIp93373LTEr0l4rYG1OitOeuU6u2TQXw2yEgOdMITn9NRbLLcwe7PdYexrdxNTuG/9wqQsktfauw6E8szXncbRb9K7kE01pwmJRYUBLTk4sEaxzrS44+WZlO6+6gfpak35gsbKWql/+496tN05VorzJLI0mMLRnK36rv6BNenPrGPu2qtfrYpmPzlQv6zfkKIr+2DRG1k1T+b13Y4GwKOkC27o5Wuici4vaTp8GAlswgH9P3XnsV8/66S2keOpCNIf0vRjQAgBQf9/9S0avmVox79Y9lHKblx+U9EdzYhBf1wBg6MidFCj8ba5tsE49hnQJ2ZyR02uNaItONlE8Ss1c5ruHLaT3bQtUQylftLcALC5KyB+eq7pO7BI3yJ7FLW6oyvtGW6HiBP1WUDqbYxqgl5MwlNgPNJLLOSE16RVoaRZIHUp8BDrGC9Sblz3udpcOJwo/CMkbRNg/V7G0ASjmIYeqOaSRt9jnMdgjI1CBc9YrjXpn+/U/55PZ
*/