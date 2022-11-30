
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