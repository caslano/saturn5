
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
{
    typedef typename T::tag type;
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