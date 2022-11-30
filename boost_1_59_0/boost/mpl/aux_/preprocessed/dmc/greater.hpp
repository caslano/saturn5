
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