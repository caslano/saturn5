
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