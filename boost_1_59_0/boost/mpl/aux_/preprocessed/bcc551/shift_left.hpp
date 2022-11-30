
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_left.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_left_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_left_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_left_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_left_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_left_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_left

    : shift_left_impl<
          typename shift_left_tag<N1>::type
        , typename shift_left_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_left, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_left)

}}

namespace boost { namespace mpl {
template<>
struct shift_left_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  << BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_left.hpp
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
*/