
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/inherit.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C1, bool C2 >
struct inherit2_impl
{
    template< typename Derived, typename T1, typename T2 > struct result_
        : T1, T2
    {
        typedef Derived type_;
    };
};

template<>
struct inherit2_impl< false,true >
{
    template< typename Derived, typename T1, typename T2 > struct result_
        : T1
    {
        typedef T1 type_;
    };
};

template<>
struct inherit2_impl< true,false >
{
    template< typename Derived, typename T1, typename T2 > struct result_
        : T2
    {
        typedef T2 type_;
    };
};

template<>
struct inherit2_impl< true,true >
{
    template< typename Derived, typename T1, typename T2 > struct result_
    {
        typedef T1 type_;
    };
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    >
struct inherit2
    : aux::inherit2_impl<
          is_empty_base<T1>::value
        , is_empty_base<T2>::value
        >::template result_< inherit2< T1,T2 >,T1, T2 >
{
    typedef typename inherit2::type_ type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, inherit2, (T1, T2))
};

BOOST_MPL_AUX_NA_SPEC(2, inherit2)

template<
      typename T1 = na, typename T2 = na, typename T3 = na
    >
struct inherit3
    : inherit2<
          typename inherit2<
              T1, T2
            >::type
        , T3
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          3
        , inherit3
        , ( T1, T2, T3)
        )
};

BOOST_MPL_AUX_NA_SPEC(3, inherit3)

template<
      typename T1 = na, typename T2 = na, typename T3 = na, typename T4 = na
    >
struct inherit4
    : inherit2<
          typename inherit3<
              T1, T2, T3
            >::type
        , T4
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , inherit4
        , ( T1, T2, T3, T4)
        )
};

BOOST_MPL_AUX_NA_SPEC(4, inherit4)

template<
      typename T1 = na, typename T2 = na, typename T3 = na, typename T4 = na
    , typename T5 = na
    >
struct inherit5
    : inherit2<
          typename inherit4<
              T1, T2, T3, T4
            >::type
        , T5
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , inherit5
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC(5, inherit5)

/// primary template

template<
      typename T1 = empty_base, typename T2 = empty_base
    , typename T3 = empty_base, typename T4 = empty_base
    , typename T5 = empty_base
    >
struct inherit
    : inherit5< T1,T2,T3,T4,T5 >
{
};

template<>
struct inherit< na,na,na,na,na >
{
    template<

          typename T1 = empty_base, typename T2 = empty_base
        , typename T3 = empty_base, typename T4 = empty_base
        , typename T5 = empty_base

        >
    struct apply
        : inherit< T1,T2,T3,T4,T5 >
    {
    };
};

BOOST_MPL_AUX_NA_SPEC_LAMBDA(5, inherit)
BOOST_MPL_AUX_NA_SPEC_ARITY(5, inherit)
BOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(5, 5, inherit)
}}


/* inherit.hpp
h3Efvolv4lv4Lr6NZ/AdrMe/YBvy+h764DHsiO9jX/wAQ/FDHIIf4RX4MV6Nn2AK1uAi/BSX4We4DmtxF36Oj+EJ3I9/w2r8O36Mp/Acfo0/Yh0qfWZ9g93xNI7DMzgez2I2fouz8XsswH/iIjyHq/E8rsUf8bR5P5C6IOqIZHsp5V/OBNPgwfaC5uiDHtgZvbAvXoQR2AJjsSVOwVY4By/BEmyNi7ANbsVL8X5sjw9jB6xCH3wbffE99MMf0B9/wgDsRt46Yi/shH2xM4ZhIEZgF4zErhiP3XAaBmEudscC7IElGIzLsBeWY2+8DfvgVgzBe/Ay3IF9cR/2w0PYH1/HgfgPDEOlr7PLsSWG42U4BENxKA7DCByHw3EyjsApOBLZPpz3pA4JP5LjsAPukM0zW46nHPTBPOyJ+dgXjRiFc/BKLMBMLMRsLMZ8nIurcR7ehjfjZlyAd2IpPoILsQoX4R68BY/iYnwfl8h+tdgg9Ui4RfLdGosk32Ml39EYiOMxDK/EcTgBJ2IMxuFEvB6vkvzG4nKchGvwGrwd43ADxqO8o0bqhkx1RuTD/h01zzbjeMd96IvPYyC+gP3wRQzD/RiPL+E0fBlL8AAuxIO4HV/Be/FVfAhfw714CF/AP2ENvo5n8Q38Ef+MXuTpCF6Cb2JbrEY/fAu749vYF9/B/ngUx+G7OB7fw+vxGM7A97EAP8AiPI7r8COswI9xM9bg/fgpPox/xd34GT6LtbgPP5fvh/0GqXfC72X7+uIe2b4rZfveioG4GkfiGrwCyzEG1+IUXIdJuB7TsQIL8DYswduxFDfgUtwo++km2U834/24BR/Cbfga3oVf4j14Cu/FM3gfWr5H28p6pGp8jyYxnwfeiAGYjEMxRdYnDa/FDMn/TEzGWbL8FIPUyeBVsvyWmCDLz23G8jEPfTAfO6MRe+EcHIAFOBgLcRwWYQwWq7eHpPOhxvaYL78HbpZ0Fkg6pRiMC3EILsIxuBin4hK8FpdiPi7DOViGC3A5LsMVuBxXyn6/CnfjanwW1+CrWI5HcC2+i+vwPVyP5t9ZUg+DkRq/s16S3x0vY0s8gK3xIPbAV7A3vooj8RCexgqCqc4FjshyL8UyWe49Uj73Yge8D7vgDgzDBzAOH8QE3InT8WEswUewFHfhPfhHfAB34wF8FF/Dx/B1fByt+1+xtKvT2P8ekuPoEfTDXTgQH8VwrMIIfBxjcQ9Oxidl/6s3SB0KRsn5L1Def6gMI2S9R6IPjsJhOAYjMQrjcSxOw2hMwvGYg1fK/jAR5+FVuBqvxgqMxbtxElZiHD6I8fgUTsF9OFXKJQEP43WyfyTicUzCz/EGPIkpeAYz8AfMRB/WbxZ2xGwp3yiD1IfgeClfLwyX9c+W/ScHL8NcHIB5OBbzZf8xEkJlOdtkOZdgRiPv1uqL0zEUZ2AMJmEsJmMxpuJaTMPbMBM34Uzr9YHUQ2BXjd/hz8nxsA8D8XnV9cHiRvarw5LfN9EP38KBeBTD8V2MwPckv+/jZPxAll/XjCDL/0J+NyrHW618r34sy/9EyqMGO+GnOAj/ikPxM4zCz/Fa/AKn45dYiCewBL+Scvobmp4LwG34D3wcT+HT+DUewTp8B0/jCTyD/8Bv8SLy+B1egvUYhD9gL/wnDsRzOAHPYyz+iKn4E87EnzEHKYDFS5sBrsTmeDd64P3oic+iF76IF2E1tsCvsCWewlbooexT2AK9sR22xhBsgwPwUozGtjgR2+F07ICF6IPF6Iur0Q/L0R83YgDuwo64GzvhK9gZX8NAPIZd8RPsjn/FnnI8cV6XOhG+O2S7D1T+lu3+tfyeqkNfPI098TuMwO9xGtY=
*/