
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

template<> struct equal_to_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct equal_to_impl< integral_c_tag,na >
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