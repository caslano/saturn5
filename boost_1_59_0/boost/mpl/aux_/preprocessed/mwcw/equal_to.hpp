
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