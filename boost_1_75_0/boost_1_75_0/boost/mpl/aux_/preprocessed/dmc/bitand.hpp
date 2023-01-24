
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitand.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitand_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitand_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitand_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitand_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitand_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitand_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitand_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitand_
    : bitand_< bitand_< bitand_< bitand_< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitand_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct bitand_< N1,N2,N3,N4,na >

    : bitand_< bitand_< bitand_< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct bitand_< N1,N2,N3,na,na >

    : bitand_< bitand_< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct bitand_< N1,N2,na,na,na >
    : bitand_impl<
          typename bitand_tag<N1>::type
        , typename bitand_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitand_)

}}

namespace boost { namespace mpl {
template<>
struct bitand_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  & BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitand.hpp
ptjYtzGfI9IWXq71/271oEBu3krMvC/d7L6e7tbu0hQyeMV9gt6vLQN8QHT02GiQ02maHJu+j4e7tbM93Pzi0UWBXM5pXJyMm1TAAW33/fv9iL9ttP6vw2enmNVPyxApWPuEzx9uX92+apXnwKTj+iCcp+Dtw/ULhTUqRylnR1StCmuHbdnw5kezKF5jMDVYcl9gl+Du+l76MP1Vby7lPnuVsLEub2trO/4qIeQao0esOGsrfJsYIyOInKo8C6aHaxdo5WT6Sf0qBVcl2mer5SDRpMkDnKuW65aUF9xh15jX7iTmVyfHt1bhZwZu9Pu8wgacEWvLXnPd7DooI4nzVKz/kmIawYA4SwARp1EFO3hP+R+7wai2yrjjzrbSpC8KgiXJrMCuL7YZkBHGTnyR5KEs4+9yj3/yT3nnZL1xsvpPeG1LZ9yFHIJWGgQv9b4PWDX8HBRwuD7CaD5uGHP09dJWs6ToiRPsH0PPwDCmswl2RyArZpVfj6xzvKuEbKuJ+j/HU9zBlxOKJM8jGuOz4j9HSIonDd4EYRQU43w8IDvE5T+EuCeTiwOO8isG+aC/xSuVlbTz+5K3K57lXHitH7C6j9XUkwMjEP7OHgyDQEKrEYTmqmK1heuCkocBURmAPB2DLIDaNW6xDBQHUguNyy5MEiVZuWuau3ObuweeIlsvywNiGznfYEUU1KL0RQIScvF5ABmQWjkxo3BH
*/