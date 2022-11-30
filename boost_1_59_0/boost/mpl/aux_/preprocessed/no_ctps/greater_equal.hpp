
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