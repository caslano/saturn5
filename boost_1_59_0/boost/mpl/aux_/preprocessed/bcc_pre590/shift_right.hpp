
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "shift_right.hpp" header
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