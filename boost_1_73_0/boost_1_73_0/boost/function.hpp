// Boost.Function library

//  Copyright Douglas Gregor 2001-2003. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org/libs/function

// William Kempf, Jesse Jones and Karl Nelson were all very helpful in the
// design of this library.

#ifndef BOOST_FUNCTION_MAX_ARGS
#  define BOOST_FUNCTION_MAX_ARGS 10
#endif // BOOST_FUNCTION_MAX_ARGS

#if !defined(BOOST_FUNCTION_MAX_ARGS_DEFINED) || (BOOST_FUNCTION_MAX_ARGS_DEFINED != BOOST_FUNCTION_MAX_ARGS)

#if !defined(BOOST_FUNCTION_MAX_ARGS_DEFINED)
#define BOOST_FUNCTION_MAX_ARGS_DEFINED 0
#endif

#include <functional> // unary_function, binary_function

#include <boost/preprocessor/iterate.hpp>
#include <boost/config/workaround.hpp>

// Include the prologue here so that the use of file-level iteration
// in anything that may be included by function_template.hpp doesn't break
#include <boost/function/detail/prologue.hpp>

// Older Visual Age C++ version do not handle the file iteration well
#if BOOST_WORKAROUND(__IBMCPP__, >= 500) && BOOST_WORKAROUND(__IBMCPP__, < 800)
#  if BOOST_FUNCTION_MAX_ARGS >= 0
#    include <boost/function/function0.hpp>
#  endif
#  if BOOST_FUNCTION_MAX_ARGS >= 1
#    include <boost/function/function1.hpp>
#  endif
#  if BOOST_FUNCTION_MAX_ARGS >= 2
#    include <boost/function/function2.hpp>
#  endif
#  if BOOST_FUNCTION_MAX_ARGS >= 3
#    include <boost/function/function3.hpp>
#  endif
#  if BOOST_FUNCTION_MAX_ARGS >= 4
#    include <boost/function/function4.hpp>
#  endif
#  if BOOST_FUNCTION_MAX_ARGS >= 5
#    include <boost/function/function5.hpp>
#  endif
#  if BOOST_FUNCTION_MAX_ARGS >= 6
#    include <boost/function/function6.hpp>
#  endif
#  if BOOST_FUNCTION_MAX_ARGS >= 7
#    include <boost/function/function7.hpp>
#  endif
#  if BOOST_FUNCTION_MAX_ARGS >= 8
#    include <boost/function/function8.hpp>
#  endif
#  if BOOST_FUNCTION_MAX_ARGS >= 9
#    include <boost/function/function9.hpp>
#  endif
#  if BOOST_FUNCTION_MAX_ARGS >= 10
#    include <boost/function/function10.hpp>
#  endif
#else
// What is the '3' for?
#  define BOOST_PP_ITERATION_PARAMS_1 (3,(0,BOOST_FUNCTION_MAX_ARGS,<boost/function/detail/function_iterate.hpp>))
#  include BOOST_PP_ITERATE()
#  undef BOOST_PP_ITERATION_PARAMS_1
#endif

#endif // !defined(BOOST_FUNCTION_MAX_ARGS_DEFINED) || (BOOST_FUNCTION_MAX_ARGS_DEFINED != BOOST_FUNCTION_MAX_ARGS)

/* function.hpp
xdfoF5A2RbAK8jXidslCstoEqb8OWN5HeCK6gORVOSVmXuGizseWEYQyMo9foygwMc6M94DkeAAAEI381DJhRt4WRHb0HdRR//jZ/PTxM5nN0refnjVQY2s2+/mQVql2DpQABFB30EFKgDey+UTf5A0udLvTh2RC+9wy28+0Rm7Gqw38zMcIxtwA3aAVqOahILhDnPkECUVANC+B1Ft/VEEpFanqVnFp9ksBIcNNUe2jsXdM5MEaWhV3lVEHaZ5TDLyvC7ujgq465AbdYsxlpmS+8q1xxzN0rBmhDsMoSoCNcwks5XlGeJ2PuDb5I6DLNnnHRPGIBRMD/7mFmgUSs/ZjcZgzvATq4UgafAnK8ZNJV3VwTGwOgv3BeUD5YyG6bfh4lAZHRmnw1VG6rUn2xGiVOYMjzRl8gzmleuebmKNQ8vxPeUOWJQcYQ5ZQP5YvaiKQowA3K6RdCd9bwSRLRCgUWDmjcYuHrhhkUW2swTgFiEWWkT83SYpFPhQMLqysbUUu1cSiIkxVN6pmfP798Q69KD4I97A7mvz/oM1N/iFg5/c3sk0NpPlVBBoB4Suoku+bMqtC/RAGQXAPhsrkuRRuqlMB4ZYT2s/6X2RlXOCG/Uao2CsG80573JLJxWkWtTmXESpgUHIzDP/w
*/