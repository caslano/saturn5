
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
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater_equal)

}}

namespace boost { namespace mpl {

template<>
struct greater_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value >=
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* greater_equal.hpp
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
*/