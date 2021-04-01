
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
SHfm8/Zi23zaszOdM+vsaxy1NLX431O8nl2n5tbWPn20CWQ0XVMFrYP13I0Ef2XA06zpqnTG7Pm/cqAz6sdfhkXWlsddVJOCMomV+EHOlRcrJAIUs9uHxLQsxArXkSG4un0UxppGVWi0LnkZ3ce5Y94ceUQek+150PluL7KeWW3Iq2z3EBMCZhaxpU7GVTIrYisliNdmx1jcWcZ/ghkTKicIbSeUVCOa8N3rU+4U4q5AG6iDa1pSzHmwr9LUKvymr+ggqRruT+DYWnb7GO2288hCOC0rN4FWkinevNrF7sEWqGv9vf5dDud9711PaIX/7ut6nmpdBZHR4HIzfYDalhEgyw2vWTfEX2kql0w0fNSWKB+2xMeHvaZa5wYY/JscrgtxlqRthOaLbqZarmE7p8PAPg6m+CFqtntuvhE0fCWL+0ZD/K/Erc6UkUZoNF2L1h3ljdBzJLCtC8DnAA5UXYchAFSWPX9ORx3TKDc5to/W8rtqBuy6aYqnRpKBgJnX59tvBUPK3vBmRVgXqnavi2v7I1dnCpcpq0r6E/zCm6j6WbVGAAJlNtAC2g==
*/