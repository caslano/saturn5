
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct equal_to_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct equal_to_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct equal_to_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct equal_to_tag
    : tag< T,na >
{
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct equal_to
    : aux::msvc_eti_base< typename apply_wrap2<
          equal_to_impl<
              typename equal_to_tag<N1>::type
            , typename equal_to_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, equal_to)

}}

namespace boost { namespace mpl {

template<>
struct equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value ==
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* equal_to.hpp
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
*/