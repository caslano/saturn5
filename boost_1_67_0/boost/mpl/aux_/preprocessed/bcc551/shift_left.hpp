
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