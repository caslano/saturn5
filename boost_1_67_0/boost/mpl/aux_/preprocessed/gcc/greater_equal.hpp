
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