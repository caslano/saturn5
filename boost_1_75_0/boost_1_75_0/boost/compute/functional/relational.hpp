//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_RELATIONAL_HPP
#define BOOST_COMPUTE_FUNCTIONAL_RELATIONAL_HPP

#include <boost/compute/functional/detail/macros.hpp>

namespace boost {
namespace compute {

BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isequal, int (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isnotequal, int (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isgreater, int (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isgreaterequal, int (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isless, int (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(islessequal, int (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(islessgreater, int (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isfinite, int (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isinf, int (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isnan, int (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isnormal, int (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isordered, int (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isunordered, int (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(signbit, int (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(any, int (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(all, int (T), class T)

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_RELATIONAL_HPP

/* relational.hpp
t9FSA35WPep1A32HZ/54UzR6IUKDHRyMG2JveX7Mu9xMyn8rfbWzRc0QIdEnGDvGOn0wyqODHiFmrWSLOBrgvRC86ciT4Fgfw08ghbe1uh5RtwEVSh+ryN3ha2qfNmOEn30EYYLy/u8xYdNCn6hBtwIfHtdPqEkuqguxnPmZ+IriNjnyikh8sAmkZBlCDkx9ebkZ6GVcV9gjyfxc53mKR5kxsair4yRiS/taBhlnT0r6/b3WVu6494Pj4nB3/i5Y2fLKa3QdjJ2FzUjrg+q/za08XAts1ffNWkjC4O+blW+pPG4C3ReCieSsNm5fwdfLAwxmR2B8lJ//lJfzeOQIAjiKer5VsNnc6/LeJoKpIaX9YE7Ldo+fQRkPpoXbOzgwNnGFts35xR42C2Y3IphbHlO4nracIncqqjOCuTZX4Q/OYfu04YuLO8NZt9axI7Pj4w0OyTJTejPBeubtWZ+ffH7CqL9Zv+n57GdxAhh4h+xSSA1BMd1w4Ngc9n556CO1exzGNYrOY44PBiR3reMsoEwpHjSRL2H2K2X6XNNeb1KjKrz3asn0iWUPdTJcM1irKNxREyQG/+aGQL51ttaC2z614a9+U+1bqE8sZrKrw7MGvuzTV5NM16n8ICpzajrS9f8TabNGD5g6RgATxKrqaCXQvQMd5VMlHdQrwHs+X+ho7vRJElMFZTvqBC1v4LEfBppbHe8jXwahD+x4
*/