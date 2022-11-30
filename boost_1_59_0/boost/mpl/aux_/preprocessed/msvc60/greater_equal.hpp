
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
{
    typedef typename T::tag type;
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