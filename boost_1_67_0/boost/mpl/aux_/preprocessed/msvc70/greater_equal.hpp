
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