//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_UTILITY_SOURCE_HPP
#define BOOST_COMPUTE_UTILITY_SOURCE_HPP

/// Stringizes OpenCL source code.
///
/// For example, to create a simple kernel which squares each input value:
/// \code
/// const char source[] = BOOST_COMPUTE_STRINGIZE_SOURCE(
///     __kernel void square(const float *input, float *output)
///     {
///         const uint i = get_global_id(0);
///         const float x = input[i];
///         output[i] = x * x;
///     }
/// );
///
/// // create and build square program
/// program square_program = program::build_with_source(source, context);
///
/// // create square kernel
/// kernel square_kernel(square_program, "square");
/// \endcode
#ifdef BOOST_COMPUTE_DOXYGEN_INVOKED
#define BOOST_COMPUTE_STRINGIZE_SOURCE(source)
#else
#define BOOST_COMPUTE_STRINGIZE_SOURCE(...) #__VA_ARGS__
#endif

#endif // BOOST_COMPUTE_UTILITY_SOURCE_HPP

/* source.hpp
GmxHOkVLkqdpOQf+3tNDuVxLHUPVIxb7b0SEYNRrmJe4XDcdB67kc/txRaedidYaoZmUJH4pXsa3emFLJ8UBYVHkuSzUjrYFWtQUGoSKvZVVRGwwBN95vFNto7LggcxC8SAsKO2W71fD5EdIzd7zbY86n/Ld/MQGB7sPgFXKYudwonluAok3Cx/ngbWyU7izp1af0iHhzw+oTOQmkwR8LzezhVtVDIsWGlitllDePQYIMv1v2O56X5bSUq+bB5UgGXsFahZgRBv5tQHWnwJnWiNOK/W4epXXRBvb0LUnPD69qLtMNU1mCBskmAjKvzfLE/fBwM76xIvFV1qwxDWzi6wq+U8mtYk+oMR4tMjeyc+tCHgkIQH/2QeGEGy5vFyK0msGwDE8Z+rDFqM5EUg1tg8PkPhjvnJ6zwGuEB+a7ZTSVUU8AlSUHMwNl8dUT6ZC/efS3zKNm85QZKds1E2CGOogjZp9TUM6R2nDX/X9IGXPPCTEcriVnck8+nZSS9e1IvqEYdLuiGU89Bz0LhM8mkMcFQdc9hUyBowGKpHHL+fo10p8MOxJiBijzA==
*/