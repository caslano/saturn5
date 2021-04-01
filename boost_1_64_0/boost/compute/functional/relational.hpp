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
gDLrLBQwMp9LyFmXJWctbdUVutMKmB/4jHet2WkfO6Nf1K9cLh4B70U05x+mvtW8Ea9K/5vbGrXu/kM/LQppVzedUo31NhQMI8hxh37JA6G+jNC2Kjx09eIxY+AYU7Iy5TOxTxXhlRyT0mX2zIsarva1ifmDLhGRjwRQ5M2k3HGJOid7C/5UBdOSfgKJ2W4W/x8sB8QfNt7o2q66Yg3RH+reNJrsiH+IV4200hF1yCY0EeWYEy2eZm75Lt7qwX2h9xaJw7z27aLoNf2PI7P3Mv/QUGotZxDosMfKhEewFCT4LREQIuQET6nUkhu0W42TFXYHehg/bK/pYnsmG027icRHIPMTeA7pncH77VvkNXSUXUmK1qBX9Y9gAQFl+epKbpI/r3tc+6o1n74yMeXubSBlvxsW7OMaMCGTY4so4P7fvT6fXXhXx13rSfjNxIhdBr3miDsk5lqsIN1IwqakYIL50NMGYVRi3OKx2MhWzyrjaru9EC9dYnc5mRx7xuiaIsCPdjy30qnak8o3wpUA0zAzjxrH/+UqOTpoEoTtLh4o094YW2e14UcSlA==
*/