/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_LIST_FORWARD_10262014_0528
#define FUSION_LIST_FORWARD_10262014_0528

#include <boost/fusion/support/config.hpp>
#include <boost/config.hpp>

#if  defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) \
  || (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
# if defined(BOOST_FUSION_HAS_VARIADIC_LIST)
#   undef BOOST_FUSION_HAS_VARIADIC_LIST
# endif
#else
# if !defined(BOOST_FUSION_HAS_VARIADIC_LIST)
#   define BOOST_FUSION_HAS_VARIADIC_LIST
# endif
#endif

///////////////////////////////////////////////////////////////////////////////
// With no variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_LIST)
# include <boost/fusion/container/list/detail/cpp03/list_fwd.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace fusion
{
    struct void_;

    template <typename ...T>
    struct list;
}}

#endif
#endif

/* list_fwd.hpp
Nu7HOfgCzsW3cR5+jakYSP7mYwQuwFRMwxxciB+r9/m0bZdtWu4FqvexpN1WytNXyhOId2M/VL7UH1fhADyGQRim3PfHWhyE7+NgTGX7GYJLcCjacBheh1bcjSF4EIfjazgC38dQ7MuKHImjMAzTcBTmYTjuwAjcj5H4EkZhE0ajcl9/NA7BMRiKYzEMY3ABxmIFjsMtOB63YZzU11GCbO/sB3IPj3BI/r9Y7p9lYBAuw1D8HkZjJsbhCpyCKzEJc3ARrsI1mIvFaEMH5uG1aDaW9S1YgLtxrWxf6/BRLMInsASfQjsG4nHO1c8QviQE13J/oNZ/7u6f/JN/8k/+yT/5J//0XZn+G9f/JatXTYy7CO8BUK7/R+iu/9PlGum0co6NL2MSJ+Vp1dr1sjNtuWJ2PYtbgcbJ+O76bOTd9eq1XLV27cylZLN3k5eUO9zvJpdrvkJ6FzjyLRK/W7vOLsvNz7OVF8q7rOu1ZfA26lxnXANxDjWuuLxIrjcz8JM+6n0H9XO8XENxjap+TtCu2Yvl2tf19w3aNWuKO2/qPKnad8pyNuS5n+23q2nbtHsViThFzbujQLt/ocu3Ky7OnWaM5/Xu6+r17qydbzm2brlz87kHfxHwr/vraKiW5/FkXanrkEn3PJ5cB8bgAJyGQTgHh+BCHIYr0YrvYgjmX0JesBJH4I0YirtwJPZWnv/CHTgKf4jh+FOMwOMYia9gFL6L0Zjdnus7XI9j8EMci19iLF7OjjQOU3E8LsQ4zMQJWIQTcRNOwm0Yj50p92V4PU7BZzABX8ap2F13PZXhv47yT/7JP/kn/+Sf/JN/8k/+yT99g+lbHf9Prv/zclcpV//f+Np/mO79VVVyjfiQ0v8H78PpyvuPqtzX/qTruvL3uQ+u57V+iuFaX54PMGk7D9eulW1yPe26Ji7U2s5D3XHadfI4Kc+rUp7OkqlOhD+Rl0T9vQzqpaTYt37SruvvLpnK9ffxiZ+e6lH+SPhnUzp1Hva7jxgsQ/qzSH2p9chk7M/ST55fDsJ7cCA+goNwEl8ajCkYjEtxCObjUHwPh+HnaMUylh+C9+Fw3fPnUj4pt+45amkfVgzATtgbA3TXw41cD5/0XxP7J//kn/yTf/JP/sk/+Sf/5J/8k0/Tf6P9P/citv8H69r/U+Wa9eeXcm2JT+PlXINnO9zXzLnG9n+fx332vA9QYdLmX+2lzb/WS5t/nUmb/259m798v15rn5d8yz2G6Fba/uNM2v4T3XnU7lNY1c+5cn+jeRt/jHueXFec1aTdP76Fdv/J6n2Hr5+56pb8kwlTtnzcdN3nAxcOl/cCXSLrSNadMo3R3dPpL/3Zg3AsDsTJOARn41BcjMOwFK24EUOwnbT/98URuBtD8UEciU9iGB7HUfgGhuMSaf9fg5F4BqPwbzgaB0m7/3gcizMxBhdhLC7FcZiJ47ES47AGJ2AXaf8fhJNwH8ZjI16Gz+Fk/DVOwSZMwBXyHEAxTsMP8HL8Eqdjb+pvBo7AJJyAybgYZ+IqnIVrMAUbcQ4+jXM9ni8457+X4p/8k3/yT/7JP/kn/+Sf/NP/9fTfaP/PXZV7Udr/g3Tt/1xXKZP6KUSczAVbXbL72p90De3/Gd6v+7k27g7KhRPf133Ols99LB1733al+v/Q1PnjYy0St8EdF+OKW6LFjbvMFXeZOy7eFTfQHTfJFff3RVrcRFfcG+64Ca64I+64OFfc0Lla3DhX3D/maHFanl93x2l5fkqLi9XyfIc7TstzuTtOy/NCd5yW53h33ATX/YJsk/sq+Sb3Vewm91XkHoz+uQvpn2G8LyH3X4z3T0z6MxTL/ZEYd1oe91AqSkpjPZ8=
*/