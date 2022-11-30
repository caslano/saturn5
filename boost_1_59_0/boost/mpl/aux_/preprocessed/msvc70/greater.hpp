
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
    : tag< T,na >
{
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
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
*/