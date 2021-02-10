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
MnHsXIxmayx5R6i8lorf7oUMhnAgjSZQELLvctwACLzMBUOh3VRn43pWlpaDQ4vqPsewIppAqfk+4A4BLFFwXA97BQ/0thXU6hbMkHAHo8laNMzkoAKcAeR4kWazOIqCWZrF0fzc4jBsaFCfRav259tWTOFa2fnf4+kA5BUiyYrCrnGGbbU1y/kGeUSU2fOe+0m656tQQAQso6ZpTzW/6d1szZrCGWI4jYE2yjMkXyzjNJ7F88TxaffiSfC3/2ExDxyvKR0rLzO017fUh7TRY1SJKMd0OIF/nLtSopuyeLk7N26KaxyWcbFaJQzx4sJo97rh14wm4iHqI0yA7tMDOJZIdU3Lew/QR3ayg25IgBWJ7mD67aS3B+fC0XxChSLn9rrE9wsBZVvc1RJcY/5c32Zv2Q0vH4PTwHlTxd2Iu611U8z9bQW/WuhsRkSYgvz02lgHWXxiwQZoO1xF5XgUdJ3sXsAvarVqRu7txnXH6RkFmJgGYRAJHNGvr85XxyuFmbn/0Q/n/ttwHqbnjm/Yh9THxf/MOzQGyyA9XUbw0Z+fBs5ykNquJKzS9D8okV6VfdvKDjVrhWUNT6OTKD6LstisVHLCqVoWjpIgAH+exPgmebu8jxiMkOFIk3tz3T0wbg8I47/n/wJQSwME
*/