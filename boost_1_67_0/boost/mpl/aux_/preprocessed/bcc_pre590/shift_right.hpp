
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