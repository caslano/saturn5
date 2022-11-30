
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "not_equal_to.hpp" header
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