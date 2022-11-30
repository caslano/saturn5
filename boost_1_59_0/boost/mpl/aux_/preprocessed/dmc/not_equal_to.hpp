
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