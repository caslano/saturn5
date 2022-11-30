
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "equal_to.hpp" header
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