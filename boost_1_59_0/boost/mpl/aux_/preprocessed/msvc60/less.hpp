
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct less_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< less_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less
    : aux::msvc_eti_base< typename apply_wrap2<
          less_impl<
              typename less_tag<N1>::type
            , typename less_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less)

}}

namespace boost { namespace mpl {

template<>
struct less_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N2)::value >
             BOOST_MPL_AUX_VALUE_WKND(N1)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* less.hpp
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
*/