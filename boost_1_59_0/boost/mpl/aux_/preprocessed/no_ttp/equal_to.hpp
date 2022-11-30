
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

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value ==
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* equal_to.hpp
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
*/