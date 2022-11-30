
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct equal_to

    : equal_to_impl<
          typename equal_to_tag<N1>::type
        , typename equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
};

BOOST_MPL_AUX_NA_SPEC2(2, 2, equal_to)

}}

namespace boost { namespace mpl {

template<>
struct equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value  == BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* equal_to.hpp
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
*/