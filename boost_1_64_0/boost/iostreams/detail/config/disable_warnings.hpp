// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#include <boost/config.hpp>             // BOOST_MSVC.
#include <boost/detail/workaround.hpp>  // BOOST_WORKAROUND.

#if defined(BOOST_MSVC)
# pragma warning(push)
# pragma warning(disable:4127)    // Conditional expression is constant.
# pragma warning(disable:4130)    // Logical operation on address of string constant.
# pragma warning(disable:4224)    // Parameter previously defined as type.
# pragma warning(disable:4244)    // Conversion: possible loss of data.
# pragma warning(disable:4512)    // Assignment operator could not be generated.
# pragma warning(disable:4706)    // Assignment within conditional expression.
# if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#  pragma warning(disable:6334)   // sizeof applied to an expression with an operator.
# endif
#else
# if BOOST_WORKAROUND(__BORLANDC__, < 0x600)
#  pragma warn -8008     // Condition always true/false.
#  pragma warn -8066     // Unreachable code.
#  pragma warn -8071     // Conversion may lose significant digits.
#  pragma warn -8072     // Suspicious pointer arithmetic.
#  pragma warn -8080     // identifier declared but never used.
# endif
#endif

/* disable_warnings.hpp
3yLpOQBrwon3v7fv659oP/6671v/D9mPf2TvK25+74UPF19Q+e4Pzj5i2AWJ9tev+z709v37E50bUPf98utrv3/7/v31dz6DfV//xOcz2M9PSHQ+Q/3t9/8PqcHlJ+tmlsLDMRP07wGYfP17C2aa/l1OeLP077X8XaJ/X83f5+nfW/l7vv69g78/ho+ZvdEIN4SbjkXu1Ti8zZbNneC7sB/8AxwB98Bz4PuwAH4GS+Gf4FL4Z3gd/CvcCvfBR+AH8An4IXwDfgTfVP9/gR/DL+AnsAXx2Q9bwX/AIfBTeDJEXs8O0P21dB+ppb6zAxbRmLssh83hYhjxp3tawWYWfxerv0tgJrzU+MPgz34/7OrvQr3fdz3+8mq53wr1d5neb6X6mxbSfYt0L6alsBdmgnshst66ogn8O2wGv4Cj4JdQujiEM8UFLIRJcBlMhRep/RK1XwMbw2vVfoPaH4YZ8EnYFL4Em8E/wCz4JcyB+HFawEzYCnaCbeFJsAMcDzvBAtgFVsDu8ErYA14Fe8JbYC+4DQ6GVfAI+AbsC9+E/eC7sD/8CxwAP4G58FN4JPwSDoSNSbejYAs4CLaDgzV9Z4R0HxbdW2ap9pmnaPoeg1wTeCzMgcPgiXA4nAtHwAVwJFwKR8E1cAy8Cp6s6XgKfA2Ohx/AifBjtf9D7Z/DSdDV9zw4EJ4GcSM+3A+eAS+F0+C18CxNp+nwGXgO3AHzNZ1maDoVaDrNhNWwFO6HhTCD5y7S9JkNO8I5sCecC3NhMTwGngdHwPPheDgPToHz4VmwBM6BC+B8WKrPucbsDUGaqf5nYi7ynfFxrerz9TAbboGt4S2wI/wR7AR/AHuovSe8E/aHd8Ej9fpAeB0cCh+Aw/V69GyUjRqfsNZ73rNRSLuKdLgbjofvwnPhe3Ae3ANd2T/C78M/wXvgn7W8VMPH4H74FPyr5v8H8Lfq/pa674Yfw8/gJ/Dfev1juN18d0+dovE8DLNN4/lPrS8+g4fDz+EQ+G94PPwSjoIO9eVkEIJTYBjOgklwNmwPz4ONYCnMgJfCpvAW2Aw+ALPgc7AFdMtIW7gAtoOLIeFE6q3oN82wXPM7DTNB470SuTC8HDaGq2AmvBIWwnUar/VwAdwAF8GNUMutfktKG2Ipt9cgdxy8Dk6EN8B8+H0N9yZYArfCK+Bt8Hq4Dd4EfwAfhbfDp+CdcBe8C74F74b/hPfAz+F9sEMI/YI94YOwH3xI262H4anwEXgGfAyeCR+HM+ATcCV8ClbCn8Afwyr4InwG7obPwTY87/OwO3wBngB/Ac+AL8FZ8GW4EL4C18FX4Xr4S3gzfB1uhW/Ax+Fv4NNwF3wN/k7TOS2k373p94NLdX6GZ5bfmci5PBs2g+fAlvBceCTMh4PhpXAInAlPgLPgCFgIR8HZcC6co/k9F65XfxvgQrgJlsJr1X4/LIMPq/1Rte+Ci+Cban9b7SHivxg2h0thW3ghHAwvgMfBS+Hx8GJ4IrwEnqzXP5Z6Rr8LggdUr5tjbtL0eETrr0e1PX4CngSfhGfBp+A58AVYAJ+GRfAnsFjt98Aq+Dx8Br6o8q/CZ+Gv4HPwXfg8/KO6/0Xt+127OYNIvxGBlZp/3jOIXkSuC3wNdoM74Anwl3AafB1Oh9XwPLgTlsE34A1wF/wR/C18Av4O7oJvwrfV3wfwbRjm/r+HqfAdeDjcDbvCP8Bj4B44Bb4Pz4B/hiXwr3Ap/BCugdVQ+0e6Ph6dCsX3j87UdmU6zIRnw2x4FZR9zWAbmK/pMAMeAQtgPzgLDoaF8BhYBEfA2dq/mgMnwmJ4OiyBZ8IFcCEshYv1fhfAcrgFLoZb1X6b2l+AF8BfwiU=
*/