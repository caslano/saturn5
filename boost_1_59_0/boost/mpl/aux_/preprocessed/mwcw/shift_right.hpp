
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