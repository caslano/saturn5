
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
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, equal_to, (N1, N2))

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