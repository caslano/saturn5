
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