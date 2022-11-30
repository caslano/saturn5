
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

template<> struct less_equal_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_equal_impl< integral_c_tag,na >
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