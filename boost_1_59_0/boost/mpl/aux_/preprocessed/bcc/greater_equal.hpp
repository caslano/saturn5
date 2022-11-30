
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "greater_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

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

template< typename Tag > struct greater_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_equal_impl< Tag,na >
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

    : greater_equal_impl<
          typename greater_equal_tag<N1>::type
        , typename greater_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
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

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value >= BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* greater_equal.hpp
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
*/