
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< greater_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater

    : greater_impl<
          typename greater_tag<N1>::type
        , typename greater_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater)

}}

namespace boost { namespace mpl {

template<>
struct greater_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value >
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* greater.hpp
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
*/