
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