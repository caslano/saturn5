
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "times.hpp" header
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
Ejeh0PyX3BlCTXJyXPWn5g4Sl5au45QCkulRxtOk/CV0Jq3XFbkeqmtDZ1/i7xOm9iLRVNGaa7GlM46DymvSfBEiGXA8MWlwEZsHUXMvqCsu9sGhTUEz34dXcNYO6jB9pXbWmeF4CBPxQpGIP3zMFgPFKHnynuZpyGGDos1AEbBgRCvyAE4F5zn5SSEp9LNO9cJi+gFa7X5zcSA619xb2DCb9gHsizDe2pxOO+TIeyQW8aG2igAVUGk/6G17DANmFw/NoXRwdYQBQrihYbaZJP8i8Xxg1SpQ+eLGBUGEFLdfyzufAU3dQgGHNojqDvttwX660ygRSusT0zwYTwuQnk2TE0lNqiaYy5S/+RmU2VlkB4/hOGzbbUtRd0i7/kBJMuRd7JLdUoDNi1H9x95jh1SyuvIUF0wMKKWro0AfwKvahsUW+J1anmmXJWCy6kNIhOJr6pyqAzi5DU3ikEix1Fur0NIDJtJvbw5k0hJKtbzJlWy4mUH61xrYScsNE68709XDt+edV77l1f3Vp4rjUtw2syzwScG7wDShlkLBzDsWR6fxrTa4Vldl5XvYXO33m9/vCsTHwMOs8a9Pi+YWv7D2uAXKuF73PxfbHbIlITDdqyVtwIT20l8PNY6aBn8a+XbwyvMs5wX3wW3yJWMa76idpqeUMP5IdlBP/pswTWXxHFSVqU8siwzSQlIAD6hr2Oj93gh9UX3lY+tw
*/