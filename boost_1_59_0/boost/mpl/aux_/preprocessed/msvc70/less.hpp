
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
    : tag< T,na >
{
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
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
*/