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
nAsguJYLEWuLeG+N5mVGI6axlUDI8FiWAntd7ZLLlfSAndZCNUWbcW0DtFt7dCSNoJ/S7XUQcnGWvgGxTcrI4bCINui9yIM6qPKyOgefusZMsXO6GoINmY5WhxSOc4CQMSgUboD1SeqcbLhKFFFLysrf4bN9MJtU/5MIXdLKoE0KvKGH9gx4xoMn9sUrwWtv2VrXAzie35O6I15coOhWU1X7u6dL7vJ1t77LT4Jmui+KCqeP7H/D5slpjwixrHIAGSyEgShjvaKgu0R5JFbjEjoh9VEJ+pmGCgc4q+Xm1hbK4GlyRRWI9iD3sYlM3n7RzMCFg5HhuUhG0m5Shr+1KxYNED3HrFREIZC0gEJL7h8SwUoHZA4WN2dDAWjTZFTBS0j/m3oTz+Upk4WVaUBFcPmUqyNf+APkD1VH9/P17uXXsd0XuAlxrz9qRccddiMOVlYzAtXLLp1dHmngQjmH5TQt3PsCRBMnsBR7ScdCvem2Gj7Ouwb390waqdYd02nzY8st5WsG3/Lw27K84A8jpo62yFK3o/kx2/9NaMk2OVWgA1t3DMlUzEa8Aw==
*/