
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