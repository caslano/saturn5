
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