
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