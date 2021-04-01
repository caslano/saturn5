
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "greater.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< greater_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater

    : greater_impl<
          typename greater_tag<N1>::type
        , typename greater_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater)

}}

namespace boost { namespace mpl {

template<>
struct greater_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value > BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* greater.hpp
0Rgg2HXqm5v0uHcCCiXUJ092dgDB7bLC8J6DKPS9Xf9YprfjkGFS+YZ5oKfDBfrFiAaj+zLgtylmNmhqWgmwEZ0LCFFHJ6S6fNr1K1Um9KhiaqtQcsdNBaM/x78sOkMB8OHA6y412mjsKle6X+ItRQtGKPHsXmG5zrvpD605OOShIvmw7kFNWyheqMRtc/wPQG/k6I8e1Jf0ALfH4tSb7CvUCvJaHQEWpM1d5mplMpjQLFxqlJSgD2RQJsHF8mjgzb+nRmzfH3xc0yOcs9Qx4UBiJhP6pundrwnYPsPEzPZCJJRGfJM0Neye/JoI3LJW/w0MyIcZGREsljw4RCulJnQYhHKIxadq1OaCcE3m4CnZgaHn0Xs2by8xJfTEoHjHE8P4ZTf95hQTYxvY7b/D5I76PwMl+n0g1ZdEY/HGeEOoRbYK6S/Lz2+sDesBr7nIn9NdXOZmQOjKCPcX5fUenod/PxJvHqIq1PMZgeSQWagPSk/JXm6aJRmqdqsUOm7VX6p2pJLi2JoI8O5n03QYTWghPTBwkUY4Gc3Do35uEsMmYu9Oyomx+vG6PQ==
*/