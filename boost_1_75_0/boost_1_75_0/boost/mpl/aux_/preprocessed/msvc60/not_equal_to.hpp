
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/not_equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct not_equal_to_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< not_equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< not_equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct not_equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct not_equal_to_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct not_equal_to_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct not_equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct not_equal_to
    : aux::msvc_eti_base< typename apply_wrap2<
          not_equal_to_impl<
              typename not_equal_to_tag<N1>::type
            , typename not_equal_to_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, not_equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, not_equal_to)

}}

namespace boost { namespace mpl {

template<>
struct not_equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value !=
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* not_equal_to.hpp
OQlbxVGdswcjVU/ougkTEXNEYPLnwkzzZyDIt5m7mZ3t1NpFS/V0Vd9Js4ej4yWWTQewtgtxFyS2i11nRRNkn07W7+PvVe+B96z3dX7qt6SDs0USS9nYMGDhfDR/qyO2r/+Mt4yTH2cluCOQZFnuZ+1uUpKrUeoqTJXONb6tMb0Q5aXkRDyY3j/BNJpssu9DD/Phz7i6C2XIKTmbSkQftnNZxhWTbw6M9qY4kJ6sPonupeoywXp4qOpksqo2cN74eryURzH+rHHVdHvwwl5QcPRxtwPpsR2HOxc7ZlvR9RssJU6XIjM1ThOM1+zrWa30Ohy0D8hwUQDQvI01I/iSf9zyYXgTBMG5bz+fPIuBX0GMvnFxKHCY+8vDdX9QiEdHS41sSL2eV1BbzahFoR1lQVFKpb7bsdJHnEG8fqvG+bb20o89a6IDVFixkdpBcCKuknFmnQ6XwTe3/eMPgZ0fG+hPvzh9+hm5fe0RAptjaugSmu7O2DT2RUJfpPfS539D80RNn8KVhNPchQNWPO/frc/GHhC1ymSr4tVb+G1NZpOPrBrwyNrGQgC1kx9EuyjnM44pk0UeWVJ7Q/BFna+sco+D+AC0FMlD+0P7/ZuH+zOcYUT+HLgZ9FuaQrkZkzb8lG9C46jNL6PyFyyA2xvtZO3kIdbxmIYO3G6D7Pu1zXstK428fnq+nIxxpbP+/GwH6VU0hoyx39zkFOrU
*/