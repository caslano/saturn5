
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