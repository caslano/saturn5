
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

template< typename Tag > struct shift_right_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< Tag,na >
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