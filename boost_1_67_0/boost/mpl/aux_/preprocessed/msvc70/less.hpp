
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