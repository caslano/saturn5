
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