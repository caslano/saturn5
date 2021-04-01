//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_COMMON_HPP
#define BOOST_COMPUTE_FUNCTIONAL_COMMON_HPP

#include <boost/compute/functional/detail/macros.hpp>

namespace boost {
namespace compute {

BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(clamp, T (T, T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(degrees, T (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(radians, T (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(sign, T (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(smoothstep, T (T, T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(step, T (T, T), class T)

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_COMMON_HPP

/* common.hpp
C1wc67ZsYUqwx8pq16z9gE054UIukExZ1+9fsL1yV66M9erVJD3DyzdgolH0bMqUXCXPWflvLxX8lWyyjOeoci23XlFwPVWqY9NTh1Hm+wRMUMm5tj4D3iZfw2cqyE6iVUdueOI1SnS4hP8KU7SpDXcpYUH2pVc+QHk6q9umMwA+yoGFOOLUI8wTlCWqR574yvwQdUo7CG7prxvwE+auvW39GMV5hYSszp+0iZ9rl5kBlCC8/FV6KV7kR6KEVsY2LCZwXQcIlTLo9hiqVD5D9XW9InRJbysdZ0XV2Sf4oU6wMio+knD2Xs1NabfuGbgX5NuTQM9qKUnEDsUIdaBdd6MBeqqcglOcVwTSHZQ8KigECZjrt5+hS/v4pTGvK5u8ogkfiqr13ZEprvAchwWaFX6dZaXArUxkyyf8BWJKeSkCXujCVhMvcisYDPN2n26vC7fOmdYtv6HeS5b3FFHqnjjqClrecKQVhODHnQjZcdJ6+3kz3k/2ABdpwB+PqPWG3fpT/MuMcRoGLIsRKNZR4BK4Lp3PeSYcfnKT7vICORaUy+dLCYBkkFP21Q==
*/