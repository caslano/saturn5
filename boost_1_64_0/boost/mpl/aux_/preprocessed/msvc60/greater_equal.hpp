
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct greater_equal_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< greater_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct greater_equal_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct greater_equal_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater_equal
    : aux::msvc_eti_base< typename apply_wrap2<
          greater_equal_impl<
              typename greater_equal_tag<N1>::type
            , typename greater_equal_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater_equal)

}}

namespace boost { namespace mpl {

template<>
struct greater_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value >=
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* greater_equal.hpp
3ylHysf6/ROgKrP2UobsG5rfo4neUg8s6xBDWKocuwXWdcjN4DAw/2Joeh0s+/3XyrZQcqR6jkTZHxvsi63NkT+UffE9Sb/CMX1lR5Z9sUUT3yujC1XHoUN+1L+f1MdHe/tzRVGukWmqfaWQKY5lt1jyHillN5KwjLxXFdryzuL5EeLabz2H31n25dTGPOMRKafXCctJy1Bkl5b5J50b/Wxb0vKTMnH8feH4W0+dp52Sp6mSp8mEleSpbbE1T8rXr8u/yy156tdenSfZdpZMqfKUKec/dZ6OX2peYJRy3SdGKpXHN1jzpBwGnNwLcgwu7U/e5uvJG+W3EvtXkvnv4NhrBg8zyLRY27ShlmlBtmnm8xnTvrnBMi3CNP4X6/hQ0/jT1vFwzesUOZbkeSnLNQoSeAJqsOO75ZhG2o1/Fy6WvXK8bMexhGDKrM583eJwfdV0mTWW7x7+TIuw5Ufp/5rVUF/vEodvPYdjLZj/lWGb5HETIYRlhTrkMTPPtTxa9rXekh85J6iuNySP8hu0YLZ9Hgs08nhI8thVzgeBhK4sLyXJPo/8l+fKc9aO9xkc8+h4jUon3pks2NofdKB8j6jzmNS+4TG7Snmm1XbMckjJpnbjPOLqMSu/Weyum0M6mBf4hVxb/BVXM1+dfZ6MqQWpuebCcyVfXu3eLGn6no3kR97T6Hj+k2PJsXzV+8Fch+8EeeCltDnz4TwsJ42K+XbrwmmaLePi78qTCxquh/xGkH2i4e/Mtg6/C2Q9GhyT9apzu+PvTPldpf4tar3mcignx+0rv9EbXhP170DZkJE04nQzrZf971VTRxnM7HhdVC/leo0cW7GEjpRBUJqtXIvTuM4wun5c+firnnOV8TSHY7rK1xxxhRwvSwntmM+Yqk7X/njxdvPcaNmGMaTFwpgq12Sq86PDfSf5veL8fJnoZ050geR7HsGPfFenqPMtp0uXvgfJtyWPs52fi87L+dLIkplkn0+mkVO7fJ730z5nhiap82k66l1qU3Ehz5mW85PRX/t+Z4XtnlZhZnpxQXbRfNPNLVfy2dT9rdIA88x7ZfvtIQxT0rSVC4e2lIsL+52zcuG8LecI1fPVcu3Q8Nwn12lSTkaloORaq4jxEj6IY/zxJNW9Dof7KfUunDsoB+tz3AEeF+45bnef19Z+ntf58+Cj+ivTJ0Y/PT552E+rfO/rf/PnRSO5+fOpaf4Dbyf+/eGczid+vr0y+oOeT/Aw5CutlelVn13ffWvKI62WX3K4md93Dz3j/DnxpQHK9OPLMtY96H/myRO+aZ8eKnux74V7ftzd58S1nzd39jy18+fK72xnWn7cXeNPPJITXtG/+sipH9f2+e953vxl0/PmxSG+52KnD/9k/e7b3wq7a7i3++8edrcPJOV52ohmUqcldV2Vzc3PdvdvJt9bcpl6K3bGNRiM5TgU1+FkXI8JeBum4+1YinfgEtyAq3AjrsdNeBtuxkdwCz6KW/Ep3IbP43b8GO/Cz/Bu9CRv92BLrMQOeC8OwftwBN6PSbgDU/EBXIYP4nJ8CB/CnfgwPoxv4CP4Z/wDfq3qM3831mMVnsPH1O9WkPLzIVB+ds/HL5HnkZdie1ymfq6+kXgFEq9Q4hVJvDiD1F1hssS7GKNNsVC21wQMwRiMwokYjVfjNIzFGTjJmh+pZ8IAjfzESX7i0Q+nSLxEg9QLYZbEa4GxEu+OZuQHN2IH3ISdcDNG4hYch1sxFbdhBt6JlnwZpZz8NfI1T/JVgr44X/K1s5nU5UgdjxIvTNmfZL/e25x84T70weexM76APfBFDMWXcQwewPF4EGPxFczAVzEHX8OFeAiX4Z9wLb6Om/AN3IM=
*/