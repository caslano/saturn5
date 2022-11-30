
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