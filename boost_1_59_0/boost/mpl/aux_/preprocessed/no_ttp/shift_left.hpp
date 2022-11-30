
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_left.hpp" header
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

namespace aux {
template< typename T, typename Shift, T n, Shift s >
struct shift_left_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n << s));
    typedef integral_c< T,value > type;
};

}

template<>
struct shift_left_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply
        : aux::shift_left_wknd<
              typename N::value_type
            , typename S::value_type
            , N::value
            , S::value
            >::type

    {
    };
};

}}

/* shift_left.hpp
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
*/