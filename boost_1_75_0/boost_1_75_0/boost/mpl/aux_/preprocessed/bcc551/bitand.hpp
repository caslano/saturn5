
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
NFjIqHra+OZ5mAXhuvPBmeXCefR7S0fQusNqqhe9BcXY82GczoGZsxQLt4vmgjCLYZ/nloatYQTH9W/1L2jkBmPb1tcdbkqQia9D106N1PjIONkKR1R0JddbySQf3DoJPy1p0zJqnWk7rvv8+bPZINZCZ2UpzGhoa8f6r/U3Su61fP66BJ97X5N5mEbtQFNSC+wNZ9xxefoD+cKOSJhdgwbNe3EtyJ/GPSBRuxIDCl9y1r27+IoR5J1TRVRy2QnGNGwMUGCo5hqFqu7Q+rzF7bB05wcugdfz4VIX/ZfsPh8t3Q5FsMCHnBdb3Wl1Ug59TcmInj1TSM35dM05u0ju6XlQoiyKgoK8U4LJhLzuZkmRYyCKDBUGSGlQRzHLVt6pNfJZHK3FKvgfy83xnr0FL4Pen8rpojousdxeHrXUPNJ13JlyfjLKtnsZ3trysCq00pmFyv8KhDEGuAJNFedTz7/KmvvUrdOsNNRbVPbmJya72fzZYjWS/0I9QzBkllT5Zmmtq3OlEMVI49+dmqjkQqL9gIo10HmgoGhFoqqxq1Lq16Er+SNJw7fDNT2DeRrwmdvtVpYsG3djjxPZmKVB0POOIQZku5QYK8HhVdsf/WAU8oc36R7livEjb5zmTXvApn2yu4bVXAw9K4z6Tj/+jHcnbOAJUq5VdMM/ZnRFvxLtns5B59VpsTLsX/iOTmNKPaOZxWG8lW/ogXgE
*/