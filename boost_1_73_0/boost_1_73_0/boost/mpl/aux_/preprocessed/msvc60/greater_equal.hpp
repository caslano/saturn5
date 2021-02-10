
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
bSRB+B4DfqSyTOTSBulyfvllFE6H4+4lscejyZRzcBx65WRoYiXPIXx+YtLy4Mh6naFOljuocgGxNKhPrUYdWMACqWvrRaxMnflri6UQK62MilQasMdwMAGRq3yXqbKoVadDCOTgE25FtkqxQbq0O+/X2N28D7zGBuNwVmPTn+MB9Gr2IKmx749Duvr8HNfnJzF+PpF+AVBLAwQKAAAACAAtZ0pS04ooDigCAACSBAAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDM1MVVUBQABtkgkYJ1UXW+bMBR9t8R/uErVtxECadomYmjRmmmp1oYFmm6PDr4pqIAjY/Lx73f5SNJNXVfNsoSxz7nnXLjXrsZCR7xAj7lJvpL0eMb9VipReOxL6DN/HCzYt2kQMtc6nbhWAz5jZxCg2qAyi0QgcxWu0z3tw2OMOQiZ5E9QsT/AFuEJNegYQeCKl6mGNCk0yFKvSw0xV8KMpEABSV6jKmcUiExAUUswV3DNoxijZ8gI+bGjcac7HtNS8xScHhNqu1NmNQHgGobX0IzjohoD24FZpMFxwO6PepfQ/V/eH0TnDeId31cAsIdDIt7jj5CZymwnYWzoHeA2vBz9AdyWKdiXLXc+Gd/cTVhaCdfzLTJcwQ1G
*/