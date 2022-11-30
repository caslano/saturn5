
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< less_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less

    : less_impl<
          typename less_tag<N1>::type
        , typename less_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less)

}}

namespace boost { namespace mpl {

template<>
struct less_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N2)::value > BOOST_MPL_AUX_VALUE_WKND(N1)::value ) >
    {
    };
};

}}

/* less.hpp
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
*/