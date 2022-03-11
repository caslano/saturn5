
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