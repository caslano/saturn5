
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