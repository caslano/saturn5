
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