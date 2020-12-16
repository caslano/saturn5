
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
NW3V/HjvmNhauatYJ7sRdRZHtcF8Wbc0rFO6mp/jabcDKcot0W3QiDrL9PY0ok4rz7kxvoHnrNb63NiIOm30ubERdf7/99/zd6Trt8JcXBV7Lt/O5C7V/aqJyMxkJ7Ov2t9jMZ042XBizkAR/v02qk5T1jnQr/4601hWiwTWyT5MnTOMyD6fqOtkRtdp+GcLvX/f13Eemz4g2Vl8jFp+oI6+/mM9dWqy6q/zXPS5j3Uqjqu/zpe+6HOfqrNxYP11Dvqiz31ct0H11zGs6HMf22Bw/XW+iz4nsU7gMG3wg67TiLb+SddpRFu/qLenEW39N7ab04i2/krXaURb/6yvURvR1t/oOo1o60O6TiPa+u+6TiPa+ml9vmxEWx9gu6U0oq2/1nUa0da/6OO0EW39ra7TiLb+X/478rlERzMi4wGz6zin1AxFGx6v2nGpUXvcLo8+p7DO1uz665RFn1NYxzlMndLoc4quM0zX+efOKX+PGn8yhRPQv0eo5S8wGv/XgP1QnId//TJzK8pLF/btnzkwYof4ua0anw/9eiq2+Qy1Tss921wzVbl07g9dx2Kdimn11+kVVcdmnT2n1V8nzVNe/kzWyTxMnZW+utet5sz661xZT52NuXXW+VX7PvqvR1Rf87WQYBnGk5l8T894snKGckOijgOLdTYW1V9nWFQdm3WmF9RfJxB17Ji6Tn79dXqyTopne2qOsD1DuW4pnu2pOcL2HB9Vx5Y6R9iejnrdPNtTc4TtucpX97qtLKm/ztX11Jk+q/46J757S8+F+zrGfBu1ji2c5qG6e0pZ97/k/HLk8UaefESO+Z2i+y1YXIl2mae2bVcd42rv6H7LOplz66/TObrfss6aqvrrHBV9HLJOdjXr/JNjfl23xRvn49w1v2HjSJeo9TsR7FmI+6lFqr6NhWefjeWBTLqjo9puPOvsObf+Ot2i6kxgnTUL6q/TNaq9x7GOcX79dW7X42wjtmcGy8Y0os4/+3fkfo6na4f9rnepPNTg8+aSed1ZLsbTzga358BirPcFjD3ZRq2/PNaJaUSduv4SrNr3MsZyLGc5Y1x11GliRV37s07gkvrrJEbVsVlnz6X114m3ou6Z9LqF6/xzfznR5ydxK3CdczmvGxpwnA8/YcTIUaPHjB134vgJJ518Ss5vJk6aHJxy6tTTTs+bkV9QOLOouOSsWaVls8sr5lRWVc+dN3/BwrMz+/brP2DgoMFZx/ToE77/0H97Dvzyy5fhV652s8N++eqX41X9Y48bMhTGEEyfZcfExsUnJDZp2iwp2WneomWr1m3aprRTtdp3SE1L9wc6HtWpc5euR3frntGjZ6/efWRVQrONBv4d8RgI/Wpkg573qd8VqfNjGFhK6NszR/osxuzAkAZWPuJ6z6uo9YXAmSUVVfrr/nikn8sP4Dd4eeqzGw363Iv6MCs+fyJfy1CPP4cODfQNLFp0uPlZR5jfd5AR/jviesizVvUp89wRk6fmlszLVTtIGrV7nXsJI1gDljujtCGftKmjnjtWBnSNRpWfWTI7rzRi3Qqr5EPR6qdjWM8w3N9K4k8qRzx3r6+CanD3w2/8vFvE91Aif11Gz6tYGFG2urK09ndOPPMifqwmspT+k84emsvfyS0MoAlCPSHyt3sKSuTDwKgc2ij5veOqKF/7dwZDq6q/dxeQIyLAIyL0GxqF+SGfNztQXJbn+V5J5LzKqjzOip4XKCjmnGjPKtG+0PMmJaWlhUV5pYEq2W11rLz+7sjZEd+40fMq5larJtWlCgsif6/Is7UR3t0l9PzVGu9nKvXnr0tLykrkC0z5hYUFevmRn8nCClSFPkip51UXl9fddeQ7Kuw=
*/