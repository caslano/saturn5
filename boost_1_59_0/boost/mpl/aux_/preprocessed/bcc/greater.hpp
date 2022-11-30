
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "greater.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

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

template< typename Tag > struct greater_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< Tag,na >
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

    : greater_impl<
          typename greater_tag<N1>::type
        , typename greater_tag<N2>::type
        >::template apply< N1,N2 >::type
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

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value > BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* greater.hpp
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
*/