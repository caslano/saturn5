
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