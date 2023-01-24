
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
+szS4FFfHzvrM2nfp2EYb1b65GF3+ma9sLbS/MmDLi7krxPkaQRWHhCYurr74rFB8+ukNk3RMP1EGbV/EGK++4ekb1VP8VrfBOTG2hJxuyvhj65D6b33TN4cIUDrqUdYyYcxKde4MSkV6hns5SYayNA6Q4eXeU4jNHiSXIoP4rFbrdx/ifhXqfdu9VI79Go1ycrrtFnAEYpPtd1QYF5cIIkVKa5y0W/a/jIBp83Zhqq2igIaZNtqykqSwDiNGqhM/OfCUvZ8yZT15ysM15ryx4D3TjZL+AkGGu9DJpvakQFgUDMdDIieMG4ISxvErC4zuCCAg5wTpvpW7r9uh4Tblyo5o5zV7rPFDjb3W2QZm70AGELEm068l8Yt+b58VTq2C+qN0s9kz9oq0c8z06qjs1+9SaZK4rmas2s1V7NMfJB78GvFKUdhCSh7DEUcxOMnniC8Qe0gg8Af1xfB4EsaC8VYU3PSO6Od6EP8N5RBQ/LbUclY4LoyM27R4y3GKwET9KxFNTzcbdnFPxXqehseiL2hLWCfNW7g4tQj7lET7C8MtyqzSm8rmaOY9bNTcB60rduEKXFW9WjKh2s1Jhjo7x4Cxn0+wMNOyx/MFCzMXpYb7UkcdNlZ1ywM0hYHgDmuYwz2h5OZyjUaHXPoa0oKdsUYlkplMVPCExeH/PwzObZoqWVcJTZgtlN+HU9Fa5ezS1llJXrD7aKAuS3v
*/