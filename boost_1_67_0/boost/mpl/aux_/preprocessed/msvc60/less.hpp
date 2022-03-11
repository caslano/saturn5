
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