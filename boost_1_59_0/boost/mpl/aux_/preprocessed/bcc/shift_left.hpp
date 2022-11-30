
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "shift_left.hpp" header
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