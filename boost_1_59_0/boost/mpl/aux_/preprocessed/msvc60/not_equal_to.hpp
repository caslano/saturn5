
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
{
    typedef typename T::tag type;
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