//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_INTEGER_HPP
#define BOOST_COMPUTE_FUNCTIONAL_INTEGER_HPP

#include <boost/compute/functional/detail/macros.hpp>

namespace boost {
namespace compute {

BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(abs, T (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(abs_diff, T (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(add_sat, T (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(hadd, T (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(rhadd, T (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(max, T (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(min, T (T, T), class T)

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_INTEGER_HPP

/* integer.hpp
psG1sDq8G3aE98Ae8C9wCFwPJ8H74BXwfrgIPgBvgA/CW6BF+qvAw5jXwMfgM3ALfAk+AXfB7bCGTf8K28AX4CD4IrwEvgKXwFedeOFrcBXcBe+Gb8BH4JvwKfg2fAG+A9+A/4Bvw8/hJ/Ag/AJ+AY/Ar+Av8AiMczHmwWT4LawEj8FM+B2sB7+HzaGl5Uu/pXvfZH+dlG8tpKWW7xr6FRl/YAy8G5aH62EGfBDWhQ/BxnAj
*/