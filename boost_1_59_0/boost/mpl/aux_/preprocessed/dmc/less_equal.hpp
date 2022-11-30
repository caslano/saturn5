
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

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value <= BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* less_equal.hpp
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
*/