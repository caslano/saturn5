
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct greater_equal_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< greater_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct greater_equal_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct greater_equal_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_equal_tag
    : tag< T,na >
{
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater_equal
    : aux::msvc_eti_base< typename apply_wrap2<
          greater_equal_impl<
              typename greater_equal_tag<N1>::type
            , typename greater_equal_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater_equal)

}}

namespace boost { namespace mpl {

template<>
struct greater_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value >=
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* greater_equal.hpp
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
*/