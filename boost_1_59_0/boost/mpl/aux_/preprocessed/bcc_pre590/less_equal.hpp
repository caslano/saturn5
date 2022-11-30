
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "less_equal.hpp" header
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