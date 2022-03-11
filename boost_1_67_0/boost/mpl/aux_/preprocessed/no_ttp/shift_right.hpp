
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