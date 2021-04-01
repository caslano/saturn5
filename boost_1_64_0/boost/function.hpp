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
LWdfuARLC7iHVkC3ZtUf3C0U5pC4qu2HgY+GK08TzFnfWYvEhjB1xz7Vh/6hxG0ZwuUtkBHkK7gCoCa1ABKJ//2lsTI3LRTmUUG8P0abJlbcDmFea3+wWxO15KjD1A7sZSbJ+nEL94qJAzfB8fUkZYse2kvKnR1cxToGzV0ccMlWeRJUTXKKgkKe2nHdQSQ4Swq/xxH+mMXvpbLAj/tR9+oyNCmUmmaMOEgBQ1aol0d+edsctJCArxLqLBmZRv8Q8+1r75uAv4lsAKc9Bx/K3BFoB/pUJDCVEnnAbFmBwsmMTZZPOKV7nTHW3XExpMIDUAUaeXV2YnQlPl7jFOlqyGDju/m0ry8e9rtc3gg7Olvy5RPT8iw4hJ2mwiN/3iBZzmtyZtxWCVk6ZMcW6tBPn37/rGZkNTFhJjhRuM+8rkXScv6wZ2tngBO8TheQahXbAuFxjf7yCvRpMVkluc+AClGStHAXnsY3SKSEKPkr6cDsukv5iI2siEYGkk+WGnrOH3GwBBOt1A1I8+1ArVlVP8Regx41ekdGy5mSEKIdFz8vStGSh5xmTffbsw==
*/