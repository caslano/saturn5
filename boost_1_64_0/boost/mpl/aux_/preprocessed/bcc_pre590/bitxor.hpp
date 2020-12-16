
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "bitxor.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitxor_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitxor_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitxor_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitxor_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitxor_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitxor_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitxor_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitxor_
    : bitxor_< bitxor_< bitxor_< bitxor_< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitxor_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct bitxor_< N1,N2,N3,N4,na >

    : bitxor_< bitxor_< bitxor_< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct bitxor_< N1,N2,N3,na,na >

    : bitxor_< bitxor_< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct bitxor_< N1,N2,na,na,na >
    : bitxor_impl<
          typename bitxor_tag<N1>::type
        , typename bitxor_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitxor_)

}}

namespace boost { namespace mpl {
template<>
struct bitxor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  ^ BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitxor.hpp
t58XP7HZFfGaTCoJPVEjnSjiGtOzKuKZePOseIz0nXqsJv0S8tdxdP2Q/SH4W7///vtX6KEk7R8Vr4nFmzNCv530G0gfS2UARCIdKaQkXOf270ie7OTVuTdOfq7zLud9c/d+a17fr//144+NRB7munjL6LK+uf4XL/5V75EX77jpu08ikZWdPX2fp+Yt3r7/lMfPnzP+3vMevWcd1eGs37N7rPjlSZubDj3wqgvmzb3zi0hkKutP63nV00/P7FO9/sZTH9x0yIlDI5Fjunj6+48r2br96KGvXvHxu8/Xdah7KRK5gvUPXTLz8sMXP1z/7l7frvqi/0+GRCIvsX7z4n7XHPFMcvuCz2955Oxb9r0rEpnQwdOn1zed98WWg1949bKCvoe/N/yJSOSXHT39cf3iX54xreGwTrMadp73cfzVSGQo69+49L0XRscTNyz4+2m19+13B7ndu6un//HrdTs3njzhnD/ueF76gEPKb4pEall/61X1FWs6f/qHx28+6Purly66ORJ5kPV33HBr4TmdO303um7Ynck/DfMWdu/g6TvenNjvgDO/HNFnW58eezxY+1YkUsn67W8/3e0XZy5YMvbNL2sSJx64KRK5kfXPdt/9seiQIb8+tsthI2buU/SjSGQD68eU1vV5b8rWw3dM99101lHbKFw/6ebp6/YdtPSz524qnr3y9Xt3mFtH8V/G+gEDbq368JVveldsPL1vxfV910Yin3J4Z+57SL81ey299+u5Dy16+YLPqTPwC463sodWlL7z/V3Fn9155bKdVh54XSRyLrvzyumvvvD9F5dsnXvhvnvdv/hECuvnFLT5EeR/lIvVHUTZyCLD/5go3v0+dP0JXfvR9SC67k/Xwz0bEV29b6eD6er1GQ6h64l0JWx+nK4D6Ootbh9E1wRdh9DVKxMj6JrxyjddH6N3jhzRMTKFZD7JapL3SXod3TEyjiRLsopkHclWkt4/6xgZQlJCMp1kEckykjUk60k2kWwl6TayY+RwklEk00gaSeaRLCdZTbKBZDNJ5JiOkQNIhpBUkcRIsiSLSW4hefIY4pK8TxI5tmMkj+RwkkKSKpI5JMtIVpCsJdlIso2k23EdI31JhpNMI5lDspjkFpI1JM+QbCLpPop4JENICkliJPNGEZfkWpJVJI+RbCDZQtI9n/gkw0nGkUwhmU6ykGQZyep84uYTlyRvNIWNZAhJIckUkkaSeSTLRxOXZD3JJpKtJP0KOkZGkpSQTCNJkywiWUayguRhko0kH5FsI+lW2DHS/mv/tf/af+2/9l/7r/3X/vv//nUmOfk//v3flJmWo7OUkjO8T/9/67u/Z6R7j4159P23gL65I02ZBv5+6dbjPdKVV9GsnfySktH5BRO8yQPFFWWlBLOt4CjCh8JWkEW39hx8D51F14+951eyrYBmHJRWVpZEq9nHEWEz6BUJtxn0hM3gz+QGb6QMXXd8a/HB3HTdFd/4nq1gumeDpbB8Qs/04rDUpPl97IB4fjNxPyW8Ppesi+D5baT7K+l47zR6/jP6P89/fnpNMkYP7wobg/fuxniSbRFvew5QuGd79pFVFE74cQvx/kZu4O1E6UrPj+hx5UrB2UqYd78a91/h/k0D3xNufo3741bp+Hjc/w33aYnzOwchbUZ2EhF7LOw4R5NsJ84oYceJZpKzeTuxeqRLN2ey9NPSZSbFd3R0rr6e8k8fpEuOBLoCf6/6nrDlnEB/omNSzU012cAuk/bcyG9uKElkAu42xHG0Ip7JNWY5HEdGduNwLEE49ojI62Zyd8AKDkdjzWlzB0YQBnfWWsRhUN18P8TN8jukmwPa6Obwzm4304qbA9vo5uI=
*/