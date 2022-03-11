
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