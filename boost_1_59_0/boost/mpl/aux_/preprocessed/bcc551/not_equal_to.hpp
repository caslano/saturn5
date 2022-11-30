
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/not_equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct not_equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< not_equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< not_equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct not_equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct not_equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct not_equal_to

    : not_equal_to_impl<
          typename not_equal_to_tag<N1>::type
        , typename not_equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, not_equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, not_equal_to)

}}

namespace boost { namespace mpl {

template<>
struct not_equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value != BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* not_equal_to.hpp
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
*/