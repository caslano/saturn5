
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