//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_INTEROP_EIGEN_HPP
#define BOOST_COMPUTE_INTEROP_EIGEN_HPP

#include <boost/compute/interop/eigen/core.hpp>

#endif // BOOST_COMPUTE_INTEROP_EIGEN_HPP

/* eigen.hpp
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
*/