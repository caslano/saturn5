
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct equal_to

    : equal_to_impl<
          typename equal_to_tag<N1>::type
        , typename equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, equal_to)

}}

namespace boost { namespace mpl {

template<>
struct equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value  == BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* equal_to.hpp
QmcK/DywAPtXRNOZfKzFg5LrPq9qUYeycVXHvff1wbE1HSo/KVGlejdOQFGzM4WY76CZjvO9lLUyVr56uDsWJ6vh2nNBQFKMfGE1192dO87yBslQz2zHBlDDpIUr97eFMIgw9sFMuRafbLhujmvX46OPmok8ES372po+l29Pi9vQPHhQviHMD93rDzZXmJMyymJ5fdMeYZpxx3Jat0LkPFydRIf923pe5VclSqfjaaQsFtGEv+0k2lQ6Tx67sNHgjkdPXglb470saelq6fct5fY2+NOG+21+NM9OHlUL3iEaRFqhbH0xcWsbvyL5hfwtJvDGQemdrQWBEx1kdb//YMscN1J7qKOrLt9lr+/AbPmrGjg1lKXc/V7wGdjgq+94WzQ4OqU5cWP/ePv9roYbCzVT8bwcdpoFULfLv3pMEr6BQpsk5q5YAKz0eiKfwPBaLKaUHCghnEQZG0jTXrmoklA2cPBhYMFXt/Ox5SYEhpZQERL5m3Dqu/ILAfVq03FNjziH++jMe2wey8Lfxz1lwYV4F7AW6P2gX9/wzbm/D+wKhucvtgHko8KmCEcCCl5xsSPIjTN5kavkfuNLkDcaj0BZAQimlEWzdeJjx9Qs17xyIJq2oQ8l1icc7LG3p98s2iDf2ZJUmwvqXuDBZuiliA3LmGmM/WySSJNv/Pg+iySbrWXsg3G9Kbnz++UniU8aJxs7mjPskHDTtlCK
*/