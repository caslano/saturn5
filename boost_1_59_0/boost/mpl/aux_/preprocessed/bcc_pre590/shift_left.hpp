
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