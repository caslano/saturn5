
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

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value !=
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* not_equal_to.hpp
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
*/