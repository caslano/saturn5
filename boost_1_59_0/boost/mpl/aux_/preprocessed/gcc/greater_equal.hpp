
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