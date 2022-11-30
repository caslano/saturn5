
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

template<> struct shift_left_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct shift_left_impl< integral_c_tag,na >
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