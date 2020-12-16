/*=============================================================================
    Copyright (c) 2001-2009 Joel de Guzman
    Copyright (c) 2009-2010 Hartmut Kaiser
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ADT_ADAPT_ADT_NAMED_HPP
#define BOOST_FUSION_ADAPTED_ADT_ADAPT_ADT_NAMED_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/adt/adapt_adt.hpp>
#include <boost/fusion/adapted/struct/detail/proxy_type.hpp>

#define BOOST_FUSION_ADAPT_ADT_NAMED_NS(                                        \
    WRAPPED_TYPE, NAMESPACE_SEQ, NAME, ATTRIBUTES)                              \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_DEFINE_PROXY_TYPE_IMPL(                           \
        WRAPPED_TYPE,(0)NAMESPACE_SEQ,NAME)                                     \
                                                                                \
    BOOST_FUSION_ADAPT_ADT_AS_VIEW(                                             \
        BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION((0)NAMESPACE_SEQ)NAME,  \
        ATTRIBUTES)

#define BOOST_FUSION_ADAPT_ADT_NAMED(WRAPPED_TYPE, NAME, ATTRIBUTES)            \
   BOOST_FUSION_ADAPT_ADT_NAMED_NS(                                             \
        WRAPPED_TYPE,(boost)(fusion)(adapted),NAME,ATTRIBUTES)

#endif

/* adapt_adt_named.hpp
9ol9ap/Z5/aFfWlf2df2jX1r39n3HPmEk0457YyzzjnvgotxcVxcF8/FdwncBy6hS+Q+dB+5xC6J+9gldZ+4T91n7nP3hfvS/c995b5237hvXTL3nfve/eB+dD+55C6FS+lSuViX2qVxaV0697NL7zK4jC6Ty+yyuKwum8vucricLpfL7fK4vC6fy+8KuIKukCvsiriirpgr7kq4kq6UK+3KuLKunCvvKrhfXEVXyVV2VVxV96ur5qq7Gq6mq+Vquzqurqvn6rsGrqFr5H5zjV0T19Q1c81dC9fStXKtXRvX1rVz7V0H19F1cp1dF9fVdXPdXQ/X0/VyvV0f97vr6/q5/m6AG+gGucHuDzfEDXXD3HA3wo10o9xoN8aNdePceDfBTXST3GQ3xU1109yfbrqb4Wa6WW62m+PmunluvlvgFrpFbrFb4pa6v9wyt9z97Va4lW6V+8etdmvcWrfOrXcb3Ea3yW12W9xWt81tdzvcTrfL7XZ73F63z+13B9xBd8gddkfcUXfMHXcn3El3yp12Z9xZd86ddxfcRXfJ/esuuyvuqvvPXXPX3Q13091yt90dd9fdc/fdA/fQPXKP3RP31D1zz90L99K9cq/dG/fWvXPvOfALL73y2htvvfPeBx/j4/i4Pp6P7xP4D3xCn8h/6D/yiX0S/7FP6j/xn/rP/Of+C/+l/5//yn/tv/Hf+mT+O/+9/8H/6H/yyX0Kn9Kn8rE+tU/j0/p0/mef3mfwGX0mn9ln8Vl9Np/d5/A5fS6f2+fxeX0+n98X8AV9IV/YF/FFfTFf3JfwJX0pX9qX8WV9OV/eV/C/+Iq+kq/sq/iq/ldfzVf3NXxNX8vX9nV8XV/P1/cNfEPfyP/mG/smvqlv5pv7Fr6lb+Vb+za+rW/n2/sOvqPv5Dv7Lr6r7+a7+x6+p+/le/s+/nff1/fz/f0AP9AP8oP9H36IH+qH+eF+hB/pR/nRfowf68f58X6Cn+gn+cl+ip/qp/k//XQ/w8/0s/xsP8fP9fP8fL/AL/SL/GK/xC/1f/llfrn/26/wK/0q/49f7df4tX6dX+83+I1+k9/st/itfpvf7nf4nX6X3+33+L1+n9/vD/iD/pA/7I/4o/6YP+5P+JP+lD/tz/iz/pw/7y/4i/6S/9df9lf8Vf+fv+av+xv+pr/lb/s7/q6/5+/7B/6hf+Qf+yf+qX/mn/sX/qV/5V/7N/6tf+ff83OPCDKooIMJNrjgQwgxIU6IG+KF+CFB+CAkDInCh+GjkDgkCR+HpOGT8Gn4LHwevghfhv+Fr8LX4ZvwbUgWvgvfhx/Cj+GnkDykCCkDf2ENqUOakDakCz+H9CFDyBgyhcwhS8gasoXsIUfIGXKF3CFPyBvyhfyhQCgYCoXCoUgoGoqF4qFEKBlKhdKhTCgbyoXyoUL4JVQMlULlUCVUDb+GaqF6qBFqhlqhdqgT6oZ6oX5oEBqGRuG30Dg0CU1Ds9A8tAgtQ6vQOrQJbUO70D50CB1Dp9A5dAldQ7fQPfQIPUOv0Dv0Cb+HvqFf6B8GhIFhUBgc/ghDwtAwLAwPI8LIMCqMDmPC2DAujA8TwsQwKUwOU8LUMC38GaaHGWFmmBVmhzlhbpgX5ocFYWFYFBaHJWFp+CssC8vD32FFWBlWhX/C6rAmrA3rwvqwIWwMm8LmsCVsDdvC9rAj7Ay7wu6wJ+wN+8L+cCAcDIfC4XAkHA3HwvFwIpwMp8LpcCacDefC+XAhXAyXwr/hcrgSrob/wrVwPdwIN8OtcDvcCXfDvXA/PAgPw6PwODwJT8Oz8Dy8CC/Dq/A6vAlvw7vwnh/7RIyMUTE6xsTYGBfjY0JMTEycmLgx8WLixyQ=
*/