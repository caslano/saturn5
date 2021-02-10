
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
FbBTDraIFURuV/uIyUOHDRQHZd6tpj5z7dTWUOtjLPyfgWJ8CV9QSwMECgAAAAgALWdKUkjzW/OMAQAAAgMAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q2MTJVVAUAAbZIJGCNUrFy2zAM3fkVOOU00mw6ZPAxWuL2kimO5bajj5YgmxdKVEjKrf6+BBVFuVyGLKIAPLz3CFAG9KFSHgsmddfYeDzj+Ne62hes/Lnfst76wF8GG5BJsdSkmODsil1Bie6CjntdR5DD3owRUKugoLPVGavn22xEnxVsM7TtCKQJjTYIjXXgsLUXTMnISl3E/sqS6O+Mxi680lcpiBCfRAvmm9DHhjkE2akWJ/OwmJ9lSDZixAQCWdm2VV1dMM7j5aAanDlMEgeKOe+H4yeFVUwDHyD/Vf7YrYHvwdiTIPKb6++r8C8Af4KMuxby7Z+N+FDMgEyvhcjvH8v9w3adl+X99nG3p/MwNwy9sapexR6IPnTnMZqgLbx5lnS/NOCC9egM5OXubvOwE0YfaZ6CPjfX31a9gZPtcDEzFZKZSPiORqa90HRus4+uv7I/StP+5jWlBf5Gp5sR0otQTUAH4Tx1wFl5OCJ2kPmzDRmTl4SNFNP1v6I5I+VFmZPTNJlae3U0
*/