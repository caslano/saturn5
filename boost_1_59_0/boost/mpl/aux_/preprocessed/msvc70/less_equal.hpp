
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
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
*/