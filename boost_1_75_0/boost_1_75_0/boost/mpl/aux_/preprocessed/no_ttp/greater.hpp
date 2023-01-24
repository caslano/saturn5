
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< greater_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater

    : greater_impl<
          typename greater_tag<N1>::type
        , typename greater_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater)

}}

namespace boost { namespace mpl {

template<>
struct greater_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value >
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* greater.hpp
2s5xJot6lu23he5B7Vwvv3XLmRG7dpEPgILMSpybTDjAemJvPJWztvGoKrT1tSWcxI5FUsWsoPot+Nk9/US/yL5Q4Vru4WJCvv6hV8XVSy+MRsyVLuekAQBvlMlGnhVrVLJwg42B9d1b898tkoGBZ203euDTrzfNAx3t78ezU73FovbCxnvk/WLGDn2LYAxn1L+m7bTR3oYkbYGN3/8R+mW4ClPauUTZDY0uwMw81i6EQOkSeg7BXBcmmsclHEkMTwIapNCHa5SrDC2D/s3+DD505bc4luVNj/bgR1EixIwfsqQjB+kMAs8uH1QdOnq5uLeLh3V6nuzc1TkgV1aVdsyeH2REyW03OzmW3zS2AI/09715oa9zIOplhqH3e3vD1Qf3Y3sI8HytL2yvCz1oY37Fvk3yo5Xl2Cuwca9pr52jBrGZpwWF2JJf3IWKnyb6WT022tcmn0JuCXtbT3MmUIAr4rv0HONOR+L7B7ocIb+qCh30jxbQo8Fos4sh+tcgjGVOIC4esvpAA4vxz6m+aBcQqDALud/7K0o4Qibufq/k7LIEGflZ7IaGxtMA35/Zvqpa7pKn5zHsDPaPFPCvpSA3kv/XR+7d/04B/7cP5fg+OguegBu7Bh68dxRQTpLPhLx4795I6XPOcI5MvVLh/Jb1if/ZjAy1jSDjpHks/gQrn92KL/tWeoXKoHPe0vvw2jdv+ESVjgYEFbcE
*/