
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

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N2)::value >
             BOOST_MPL_AUX_VALUE_WKND(N1)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* less.hpp
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
*/