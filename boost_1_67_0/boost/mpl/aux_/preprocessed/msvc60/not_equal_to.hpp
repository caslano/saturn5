
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