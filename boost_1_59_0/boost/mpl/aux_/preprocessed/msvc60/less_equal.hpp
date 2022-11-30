
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
{
    typedef typename T::tag type;
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