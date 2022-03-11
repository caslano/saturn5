
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/not_equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct not_equal_to_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< not_equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< not_equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct not_equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct not_equal_to_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct not_equal_to_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct not_equal_to_tag
    : tag< T,na >
{
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct not_equal_to
    : aux::msvc_eti_base< typename apply_wrap2<
          not_equal_to_impl<
              typename not_equal_to_tag<N1>::type
            , typename not_equal_to_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, not_equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, not_equal_to)

}}

namespace boost { namespace mpl {

template<>
struct not_equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value !=
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* not_equal_to.hpp
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
*/