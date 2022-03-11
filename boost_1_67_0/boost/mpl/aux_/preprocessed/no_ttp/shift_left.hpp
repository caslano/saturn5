
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