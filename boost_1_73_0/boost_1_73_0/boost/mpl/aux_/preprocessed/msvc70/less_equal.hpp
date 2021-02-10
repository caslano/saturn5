
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

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct less_equal_impl
    : if_c<
          ( tag1_ > tag2_ )
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

template<> struct less_equal_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_equal_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_equal_tag
    : tag< T,na >
{
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less_equal
    : aux::msvc_eti_base< typename apply_wrap2<
          less_equal_impl<
              typename less_equal_tag<N1>::type
            , typename less_equal_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

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

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value <=
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* less_equal.hpp
lSYp3Qyl1ONswR2qOapI8wJJ6maW9m3BDPPItL3Xgv1WC/rfQC90XkmN5IIZTCCb4SdoncCtnNuOdgvacRKfJLb3601GPG4CTnqkm4KW7AEJGVXM38TK8EwpXTFbQecVR2FWgvKmsA0eoUsmxtS2fV1CKtgUvVQYXp23jw+PIrOsEUqpprXUhosxLLiZyJmBy8cac5OsHLHD1E9DmsvplInC4yeUbvesj9eDZNsBD/rDjC6QLpgwNI4hugI31ymY4Fi50khZdfKZaoqSV9j5Uskxdf89jvfMo4GoB+GKPrT6n/i24CdCrtA6CmbCdTMNI7Ty3YF95zvBvuJiLh+w+EDSpqnREP7NE3ZJKWVEMgdlbwZTV46YsqRuynm9NtWS36Pi5RLcFoCVBlXD6fBgwrTVgQJCPZHGip43vW4XRvG6S37tnEth3K4ya3gC01lleM2Uoc77yGGe/o6a6+Perluan0trJY3MZdUlLq3w3NpV5NoB6dndJfDPHgLyw+4+Ohtb3gSc5XT7/nJ4d92/DchZnmNtj3fpbkDW4r6jGJtJAnHreHP4umIYyZkomFp2ojeuo/zw4KD4nO8f5RiQgLzV+7J7reGCaxtQbrgUCTwT4PfqnqGD9il7DwqX2obC2fgeBC5w4WkT6RXj
*/