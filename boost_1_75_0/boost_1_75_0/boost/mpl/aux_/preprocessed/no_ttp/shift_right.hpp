
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
OFvmoIhGVobcNvWk+BzkuVBcCgRxO+U8Zad+td+ny3Wh7AOUa8IEQ6FGsDiUhTvHi4CZO/cNAkh5jgiM58d81G785PMXJeJLiMSPdR0j2OKjCupnZLqvu3L7wi3+z90iCsKQ7jb6864sqDPoJRDN8kkEgqH9ijHYPsg+GBoEDdbqsQtiCURuxbVBWXhlH5wZ5NHzNyStFq2VeAmz8VVVD0Eelg1dG8RBag1tDdEBqT3opAd7Q9uUrhZjSelpOcwGZwrr+pVwD87rVyBMv2xumOY1wmPQc8+HkWMAWXiCyNGPb9n3XRGo2dfkyk/CfYNB28rAvsgzyUpEuuA/3iBzbrxjPT4/iFBBYqOjlBl7zkeIRvRCoDVF4I5/PRDkYoqYNgZ1ewH5q8bYy8wlsVVBImjN9UV1zAfOE4bVxp36Ei8kRRs+lgjbQaUL6H7XAKlw5322am2j7UqEfAanV29Khd7OXG/idgw2Kz1bzCxUUq2EgivKPGfmwrDT1cbn8HqFhfIzkkLsmCIXtgulxRWWJIT2nNljQ03lCe+kZoeDHO1wV1npwm/tk8K1/F4b1SpR0Xbw7+yEYYubykbF8MPcRcCPymRkEklbH6HhT7Lf17FKNGTcBUrabnw9ZuvBiqICxbTmh5UmSpKNaRxj7uFVYuON72FBGUTK5b0rCOD6gIFQTecwhb1HRGXBLNax4/Q/oL1o06dBJPNYJjPN
*/