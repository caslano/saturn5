
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct greater_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< greater_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct greater_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct greater_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater
    : aux::msvc_eti_base< typename apply_wrap2<
          greater_impl<
              typename greater_tag<N1>::type
            , typename greater_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater)

}}

namespace boost { namespace mpl {

template<>
struct greater_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value >
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* greater.hpp
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
*/