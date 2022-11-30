
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
+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
*/