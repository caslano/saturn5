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
32dNtHMtrzue8wneSPM+4itxPmae4U+Jn93Wg+TgZUoiVeZ6GpZSuN211VrmHhP6XGHizTT9pW78ynae27N1d13w3fkuyfdiKRvnr8EtZY7jiiHNOtZw60ta9FF7PO5di/xL/J+5ExlrrrcftlaQhznkIc7MxSaasXK0xMU4om46nsmycGHuVPMM/FMrGUMYwZoZvcDF5nbmOfWI5LeC3du60zwrTZZ0cs369aViHuryUHI7
*/