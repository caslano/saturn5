
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct less_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< less_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less
    : aux::msvc_eti_base< typename apply_wrap2<
          less_impl<
              typename less_tag<N1>::type
            , typename less_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less)

}}

namespace boost { namespace mpl {

template<>
struct less_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N2)::value >
             BOOST_MPL_AUX_VALUE_WKND(N1)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* less.hpp
M7iMlAcaiyoy4EwCYgCjGVfNSV+cTTnKP3PtJkcn0znByJeglf6DmnYAbpcxSCPQAcgNpUChBjQo5yv/P0GLCWa2TdZH52N9904bFs90TGFpj+4Ptj6ZZId9YWT+XU7SS3nSkfUepyzcHSZ5aaDuJ9wj9X/JFFyUAcGoJLfpYFhzljfgtoxoVw1npjJ2mRespDfT4NsWrp4eVqJeWyH+SGQbODQN2l21YWbygMaM0YTsqjYWiA003kr/NOdwW47sGL+y5NDq48mKy6UDz9p0z1qx8YywOG2WhjVsE4nbBdutKR8v2NQNDrRNsQI8+Dz2A1LkHs4s85zIrQGn7PrE7KusYybh9zlFe5JRfLqlIWKW6oZ7IWgGB18QMeWNaGK6ei/IxwS4uK8NVIQ/exQtn3qv6AHHNCBjZNdWA/REIuTFx45GZ5qvsiPLIrvaFLSaj+YOPqD6MN6MeJ1X6i8eMt3CR3iYGAA2kghJR40JLtm9NpCC3hugFJgravUKQ3YUNYE7EtQVk78ISFvTlut+772uTRMtRepNIB/1x594AlVa3jn/7nWrLDs7bw==
*/