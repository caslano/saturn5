
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