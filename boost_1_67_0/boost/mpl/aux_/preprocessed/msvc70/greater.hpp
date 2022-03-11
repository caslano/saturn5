
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