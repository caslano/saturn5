
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