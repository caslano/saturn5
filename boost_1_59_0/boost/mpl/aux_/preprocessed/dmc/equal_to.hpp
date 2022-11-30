
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