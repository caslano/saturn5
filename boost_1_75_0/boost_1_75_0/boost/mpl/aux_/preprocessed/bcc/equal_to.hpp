
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "equal_to.hpp" header
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
onVLvlc8Q9rNMXEvzMD3gbazRq6VG+R6eTvAZTgPiRDiXw/5fTENuvPrQBeeAEi3w4zyFiq/RXwXwXhcfEH+kVxNefaAFjcGde6FPC1Q/tthXvkd8TnxfphHbKz2QJ4z4oMwk/yy+HUV91nxC+LnxGcg74eohfj8GNS5BXB/BmC5AOEnxfMA+w8B698XX4G4e8WXxBdgVkHNvgAzy9+pUv8Ic0pBfFP8K2D8WvmgfAiemPtKmFd2Obc494prYDZZI2+UN8s2OQawCwB3Df3aJltSdN4r98gtQAfdNv3slv3SEXfIo/IuOSLvkcflkLxf/iTh9Vb5JfFm+QXxpCxAzU/JOaBsgbB8l3wnlHqf/G75PfJeSP+gfE5+v/wB+UPyQ/JH5T9CjuehzGrA9QX5CXr7lPxJ+fOU8lmTci/g9TmA+SH5O/IP5e/Lt4ivQdpX5FGFnab0RqDxP8t/h1YxhfYKfm8hLLH9l8BskqbDKofzFMR6pyDWOZc7G4FeV8KMIoGyVzvXQez18N7qdDg7nZucdudGp9PxnKsdxG6v84zAss9DztViv4Nc0eP0wVyyRt7jDDnHnUFnxDniDMCc8lrnQec1zpjzkLMesN8APPQMUOtKp01uFNPOo86MgxxZdR52HpSPOW3icWdCuGfdsy1zLU+3PD1/2nmne3oe7r6zwExn+s5izOazznMYg+/2/5vPzp/m23knxuEt
*/