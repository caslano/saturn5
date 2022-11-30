
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_right.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_right_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_right_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_right_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_right_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct shift_right_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct shift_right_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_right_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_right

    : shift_right_impl<
          typename shift_right_tag<N1>::type
        , typename shift_right_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_right, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_right)

}}

namespace boost { namespace mpl {
template<>
struct shift_right_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  >> BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_right.hpp
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
*/