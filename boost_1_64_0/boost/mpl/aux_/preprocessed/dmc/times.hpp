
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
template<>
struct times_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  * BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* times.hpp
6aYaXJ+8Ku3mOnTB9TgA03AIvoajcYO0m7wLIL+HkrF+sJHB76HekvZlOzri29gAMyR9ppKHpKcPn/TmOm+T9DlSrku4AD/HVDnet+MXuBu/xM/wCn6JV7Ec6/saq+EN7IM3cQB+i374PU7CfJyMP+Ac/BET8S7+HX/G9ViIG/AXKT9tv4zTw7aU8ivbb5+lfZXv9xnoipHYGmdiT4zCQRiDwzEWp2EczsJ4TMRZuBbn4OuYgB/gXDyGT+IVTMTvcR7ewflYi3IlYR1ciN1xEfbCxeiNyZhUieV4sJhBuEpw7lnWwY8QT9hG6E3cEW488gjj+duPh97uC8s6nN9T1iFyeFmH5YTjBI+XWAaP8N/uoXKTUkD6ZiNYVokjNFtU1sGXz3V7lXUIZj1dMJK4ZEIKf68mNCNdOp8jR7Buwq5eBMxWAvHjyecWf+cQ78WyjgxAkteL/NGbUMAyCSzjtJj/TihQ8iI+YjHxhMSRrBcr9yYNIT6TdDiRsJH/lrGYOmCkEsf6rypp+PsWcc4BpEum/gRvQhhhIyGLMD6A9RPSWHYt5iezLv7ext+5WPcpTkrWt5Hg0IfyYwGhWR/qxTJXA5ByJ7FcF+IcubnzJKTzOZtQnh/aBBLfDK/y2eFp8udzPMGfuOXoTNxG7IJZGEZ8LiZjIHHb0KEv+wudMJm4PP4uJHjw2ZeQTVwgpmSSD3/fIyTw2XlJWQe30awbe+NqJf0SlqHME/kcT9i4hEC6TMKRJeTTl+WIv7WE8qdwHPQlL4LzKupGaEVc5X5sC5b3wogUyjiaz4SJfC7ABPQaQ/0wGPMyyYPl9hHuKX8TfyuFsozhb0Ig26z8UvLn7+sExz2EQI4hlmu1h7Lz3xJZ5gifx/O3B/8tBgMpTx5xK5eyvDd1JXQh+BLCCPuUdOgfSD6k92Zdy/kcHEjehLXelN0bA1kWlYfW3oQY1jsec70pQyDbhJDE53w+Z+J4pXw+lJX4VJbNJs5xLHXDLGU7jaUsPpQPEwgrCbvIP5f/to+/I0l/Cb1YJpm//fAen515iO9J8FhGHsT58XcMIdmHfHAXoZB15GIAy6wmPsMHWUcBcY7jKDOf8wlO/akXyzTDLsRn8vc2lruFTsvZJsS1wgjswjK+hPGESEIwLxf789+WjyMNIYdwifLfwsT+5DOecwYzCDmEPII7cfGkKehPfbE3n/fheMzDQkKSko7g9ne2E3qj+wCWJfgTcombiMnEx+BavEdcFl4l1H2UY3IF5eYluZQB1JuQTnBbwTqIy+Rvz0yWoXPFl7hbe6gbaSL4+zz/zfkljrO91GsF+RCfgYm4knB9AOXk8y7+9iB9DgZgIfF1n6Vu/J1KyCRcIpSn48aDMJGQSsgkXCfU/Zi8CZGE1YQjhAJCs1yOKUIyYRfhEsGRzh4vQiRhNeEIoYDQjB/cBxISCemEbEI+wf3Tcg5+hBjCasJxQgGhFZ1FAYQkwjZCLuEeweMCeRKSCNsIuYR7hGYXWZ4QT0gl7CNcIhQS6n5GmQiBhEjCcsI2wnFCPqHyJfIj+BEiCCmEdMJxwlXCPYLb56yDMJ6QQEgj7COcJxQS6tKZ1YUQSIgnrCbsI+QS8gmOX5AHwZcQTEgkrCbsIuQQbhEq57EMwY8QQUgmbCQcJ9wiOH1JHoSJhERCGiGLcJVQ+Su2DcGPEEZIJqQR9hEuEQoJznSoeRICCYmEVEIGIZtwnfDXv7/+/fXvr39//fvr31///vqn/CtPmO5QpgY4+PacGB3DXEPRs2JDw81/xkW2mzxrWmRYu47tO7b3nNJudlwnz47d1f+W4NWtXVxESGx4WLuw8Mmzplr+e2js3Jj46InK6MI=
*/