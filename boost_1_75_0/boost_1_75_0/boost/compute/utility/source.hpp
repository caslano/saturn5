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
tVtbV9iHnd3hZZGl0SPhzUT8G/VKd9B0vROLNobLvsTB/d1yekWfuuiBaf7M+ZxGTmd77nlU2ULlqtMrYmrho7nt9KCP5pWh2HGr3V5rFUkeb9QFl6iCftx8Av14gN79S8v1/6HKq1TU8vL4wGp4XLQpZmttRqyNkbagF3jD+/rhU74eVnfPaa3V1oC90ukIDzhvR2aHorsiEyZhTIZ4O9fvPB79UL6uuJzH6CyqrKMysbzs4wX7zsblwQVwtw4/r5uty6mnq6Sft56o/6C3/sbt591Umaby9vKyr/FRn/C4AOgGcuKUOPS4neYROHyWcTd+xWvF9DXU6+9GF71GbFHJuTxcpSPF6Guxs0LxW2PbI81Ozt7p9tt10oBXU+W+z328wm40RA/sHxs2FLq0GsK1EVdeL+vStvjf+SLd/MXHmf/9eHB4LtD23VqtNPzvDPv5gY/zfj5GlX+h8u7HjT+5saelfSK6URQzAwB/8l97XzJBlt+rrv+2vs1pCo86LeGcszxyj5uvIhJjOn7zjHQ8M8DrL0+V9VQmB6KSk2DqRJu3ic0eH/BstT+nsf9hvOl1rddYjfZvnK5weJfTr4mbSDm58I+dLVSWlXWS82gc4ypxxBvHBwZYx3mMKs9SeW2gjD/3+ftv8NnPvC8bxeeVTvwV/SPnVyH7fBJcmlwk4HRyf+tn7G9bnvWW3VTZRuW6fNnfDtQL/Foe
*/