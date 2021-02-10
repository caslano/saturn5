
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

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct greater_impl
    : if_c<
          ( tag1_ > tag2_ )
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

template<> struct greater_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct greater_impl< integral_c_tag,na >
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
    : aux::msvc_eti_base< typename apply_wrap2<
          greater_impl<
              typename greater_tag<N1>::type
            , typename greater_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

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
+YAF/5/S4E7wD8t8+DPeAVBLAwQKAAAACAAtZ0pSqH83MS4CAACdBAAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDM1MFVUBQABtkgkYJ1UXW/aMBR9t8R/uKLq24JJKG1BWTRUmMa0FkYobI8mvjRRkxg5Dh//fjfmq5u6rpplJY5zzj3nJvfaN1iYSBQYMD/Jl4puz7jbKC2LgH2ejtm4F87Yt2E4ZT4/v/H5HnzBLiBEvUbtFIlE5mtcpTvah3mMOUiV5E9QsT/ABuEJDZgYQeJSlKmBNCkMqNKsSgOx0NKJlEQJSW5RlTMKRCagsBLMl8KIKMboGTJCfqwb3Jp6wIwyIgWvyaTebLVTTQC4hc4t7MdpUY2268EoMuB54La6zWto/C/vD6L3BvFe7CoAuJ0OER/wx5Q52jlMwrjQPMJdeDlabfhapuBeH7iTQa9/P2BpJWznW2S4gT5GZMeSO7CgT+sEUBaa05LcOy/dvx7kmHa1S0Fu6O+t93kf5f+Vt9ch+93mFZXDJk+VkI3YZOn71R/UGlpNq94GNNFf1V/1TUz3qttqwapc/K7Zfm/G9L2o4k/FV5X/oc5tA9ylCebm0ACRfSDIvmYDtjQrwh+fwM9Fhra1QCtlQCZ63wcZdUQS
*/