
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
/aTpA3SpV+Mw/27HgrSi/0lDWOXnelFjirPSVm740J+zu2FfakGDDSQLhj+e2t4pVQxPlWhXqLak2wAIOwmlAml72xp6pViqaWWTWQO+c6qEEA7rUvRInXVVSmDNvdsCVSveszQcJOMAe6XOcqp//BoP08vFyXR/m5Oydp6jpga+2AV9W3qesxW3mxWR8cbJfVcKlwP/EVzEOVIiSW909tIhRUULtFmXnAwS7rHY0pGSgM9JF5q6Ck6AK8IMPLvT7YwOOpp0wv4cOzC6fPdY+3nXg6GGLEsvRi+Ur4vSWnxp0+pzyNMVke9RB+rY4UrgArSyj9rGSIlYqY5Yb0e3smf9sP+teCANegyfYWLST1pViPiYNkve2JXkVrRXAdr3P3F2VkFxMFkURgIE/4HgluAS3D2QHwnu7u4ug3twdx0suLu7Q/DgGlwHmMFhZq1qd192q3YfurpuVVe/3jp9+nz35mOnC176LmdyAN52ArZxT8G5KdkUMktxLmaYtcOwqX50lfLYpXaMrwtlq6mQYz+tdjCzC7rjUF47CumNuP2Q/nLcg/ab/EZGCxwUDdnlPbBAX/Zcg0ONgAOU5W55u4tfqbpeXZbF+lXPyK7G5/yC/xif4DjiBke4EkFTt5RqeoaE4L0D+QDWxfAiADlB7YhHVMJHJL6MAUTRZ9bQzFyDsGd1BKZt8g2hctdVZBbttejOPNKT6UaXCSnK
*/