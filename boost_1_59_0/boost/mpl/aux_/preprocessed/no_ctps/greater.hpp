
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