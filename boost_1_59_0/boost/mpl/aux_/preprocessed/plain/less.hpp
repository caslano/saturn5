
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