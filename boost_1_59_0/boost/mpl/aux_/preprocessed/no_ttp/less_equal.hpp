
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< less_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less_equal

    : less_equal_impl<
          typename less_equal_tag<N1>::type
        , typename less_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less_equal)

}}

namespace boost { namespace mpl {

template<>
struct less_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value <=
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* less_equal.hpp
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
*/