
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