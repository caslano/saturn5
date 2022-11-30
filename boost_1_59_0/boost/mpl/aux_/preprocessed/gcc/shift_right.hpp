
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