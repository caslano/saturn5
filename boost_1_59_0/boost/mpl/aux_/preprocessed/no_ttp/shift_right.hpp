
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

namespace aux {
template< typename T, typename Shift, T n, Shift s >
struct shift_right_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n >> s));
    typedef integral_c< T,value > type;
};

}

template<>
struct shift_right_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply
        : aux::shift_right_wknd<
              typename N::value_type
            , typename S::value_type
            , N::value
            , S::value
            >::type

    {
    };
};

}}

/* shift_right.hpp
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
*/