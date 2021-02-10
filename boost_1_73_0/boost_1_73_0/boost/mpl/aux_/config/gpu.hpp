
#ifndef BOOST_MPL_AUX_CONFIG_GPU_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_GPU_HPP_INCLUDED

// Copyright Eric Niebler 2014
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/config.hpp>

#if !defined(BOOST_MPL_CFG_GPU_ENABLED) \

#   define BOOST_MPL_CFG_GPU_ENABLED BOOST_GPU_ENABLED

#endif

#if defined __CUDACC__

#    define BOOST_MPL_CFG_GPU 1

#else

#    define BOOST_MPL_CFG_GPU 0

#endif

#endif // BOOST_MPL_AUX_CONFIG_GPU_HPP_INCLUDED

/* gpu.hpp
L3Rlc3RzL2RhdGEvdGVzdDIwNThVVAUAAbZIJGDtVlFv2kgQfl/J/2GOU14qNrYBU/A5SFyKGtRLodhp+rqsx9iK8Vr2OoT++pu1Sbiqzb1cpb7cC+zOzs58+30zA4HGWktR44wFWZEo+nrA40FVcT1jN1G0bj9gfRd1i7JST8du+S7b0V0QjU7ZButmj+xaFRoLzTei2NHuLoxWt5vFp7tFGLHAPgcO7C4X+x1CrB6x4nUWIwsqLPMjHcdCiy697V664DoOmNBZ0aDFuhs+3GayUrVKNF8uQ9u7dCz2Tmj0IWyKPjhDmJcVDBzHA3fke2/9kQfvbyOLfeFrdcAKY/7n0Yd5uL78uCCzdc43ctz2WfSUTAqdqQLKHIkkqA/1VjWFfBXG2MC4v7/n8/N9gnTiqkKR7696hvN22euDyHeqynRK5vBmzgfemIyFohRXPdfxhmNn5I5GPeuF2+hYUkCNT9pO9T7/A2Qqqhr1VVYrPpl4U+6enf/CYqdTHxzzvsDueG3pJU6df1BMPMEcVh/+9V3/CcLQQFAPJxRd+g6KTFE+/C/3z5b7l2l70pN2p36mNr/OM3Oha3PZbmZkZkHdQpqxVOuSbjxvgwSFbiqkYfFbGK6XTFbHUivWzZ/APh9DUIg9zk5zahVG
*/