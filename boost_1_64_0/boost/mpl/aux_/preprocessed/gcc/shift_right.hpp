
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
Z+wAZcTC2EfFFSiOt7F8rme1QQBTYjEGZiuuIQiJDU8+XgKp6my8R1/QUCiX33zODK9nv20ZfjgvvEVmgVceTBGaQcpQMlQIancp+xe2nOGATRs7BzAsoa3hXgDW3MfhSbOcBZnv6djH3DB5Ma6OSe1xtiEa7jnkcCxvG2pDQJRUoLLnKhsZG4ERPUPosBnPfI67R7XpiHfqEKPzFHkNCSo8DKWq3nXmmw0wJhAGblltlnwUnFu7B06Uv6d6l7TZJPj+w8/tbofu/HjCBWtuCNqp9vuujuvgSe9atBQqAYSberfcPIvCoYuLDgbhEFYXRtb9JfWHsZdJ4eW0efrP5W2DkFiHDSS0QfTO+8lLDZS01pPVs2hDkO7/dxhZ1NQ7mhpk0TlMlTmglfDaVm1EM4nqW8EjXD+u7dPGxztjANiLaiuJtc8uwSlzK2QV6tmx6xxIyCMsKULroAZIIx/pZG8FGG/vFBGaGqrrabSbto8/9MZznBMQBheDij1f2VwGew5CtMdI+qfGPW1uoEeuy6SOMYqxF+s/C9q2dB88HvIY9Pnr35ausLKQRg==
*/