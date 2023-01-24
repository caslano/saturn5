
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitxor.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct bitxor_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< bitxor_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitxor_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitxor_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct bitxor_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct bitxor_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitxor_tag
{
    typedef typename T::tag type;
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct bitxor_2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitxor_

    : if_<

          is_na<N3>
        , bitxor_2< N1,N2 >
        , bitxor_<
              bitxor_2< N1,N2 >
            , N3, N4, N5
            >
        >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitxor_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct bitxor_2
    : aux::msvc_eti_base< typename apply_wrap2<
          bitxor_impl<
              typename bitxor_tag<N1>::type
            , typename bitxor_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, bitxor_2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitxor_)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct bitxor_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 ^ n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct bitxor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::bitxor_wknd<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , N1::value
            , N2::value
            >::type

    {
    };
};

}}

/* bitxor.hpp
ZTvbgZMFgmu149wh9wHdO8/67BzNxZ3nAi1TRttH/fI2GWDk/bSph3095zyBVrtRu7FPSnqwlv6ZXOhGGyW2FIJ0qwixthgi6dLXwF4r+QiYxK5aPgLUICOU2Wo0cP0ZDPl5+xmGjax5V/sgcuFLVT/R1nxMCv21mGwKDzl+MSPfenz0wj2c+fUZRgulDp4awBs4daG3zQ2G6oEfweAcJaSAdPCnjqQ34LlgRBj6F7dgP0a+9zqRR3htqPMKNLMhkgA25G151xk2JFZEVpSzfjpjLmckZ9rrv7KenPFvWhSakQFVZ3bk2zX9vLs+xkL1iCdIjsrcT6t6JbH7vKlOKJ6IvkGiBZREcMgaOUI3WPjNMFimJ/HQkeG+8vCmTcQ+DpcxMY6vM+gk8rSN+mbPuj8Wk3850m5tPh8eCtmYrx/h6iL3HXbfnPfdcUnA94yQKOXhP7hvrzUjj+6ytK/zHrzkweS7ynzzEjJZbCgKFWW25S9+iZUh68FOWFXhOrt/4A+9MTF/p1ILkObPwNSOF9hdn7GG6f2c3/ou9A5HfyxeRuXllxaMlR0jKwnnLi+FS69ue8DsRFXY/CWRUufTVq++Y92h1LR9l+FUVMdaQpD3aqS0KzCAWtBYKjVbINjsRZ4eecaLeH6gncN622JEH+gvQQJIlg0AvS9/MF7yvJUumiWJjQ5A1LSnMY2NDg6J97+yHr7gQZY3nLPK
*/