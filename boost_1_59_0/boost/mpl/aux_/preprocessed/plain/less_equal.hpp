
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