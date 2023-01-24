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
1mzt3L7svpz7w1ouTgfyB0EH1xvigkumJ5UHvFxk5YxkjZ5bZ1fmiA5PDAFdPBuSpolergU+TXKjEkrZrjmuMNfc1Wy2YUMXV6kFEQlstu2wj0tgQ8z0xBb4cQ5uWNXFvqFweuHpG1rpm7BPw89+G/tnK8w+dUiW1oaVDj//3fo7+PdpBemp59kQ14Tv49wrDd0iMoNDRQojT32jhyBSXlpDVQrfE2FvpRyA2RkuGQpjec6GspXZTNlMOUwwptysbLNh99/v/KOD4QoT7UN54BFZcbkaidVs/2HhYeRQ8G/C7/cHLP4fg9HB+cG44E+tP9vHbJznncVkz+8zzwf4bRLRoMcxr8bLagOEdz84qN+kZRXKV2remO1W4mG5l/IfDcOpAQiDF6flef/dWLnTk2erJrbnqsOfsouLlzRzBzebxJ8oQN5drs1JMS6TREkPIqyKWrgexd5P/BzJU5XZwtnp9852PGBUfE2yHbB5objdGHqpowRrRopv0X1+1aEhQc/Owsxxi+71Cf3HHKP2ot9e8yUfRjluk8Lr4Mpf/d7+HDFeT6AJ0ywG0abl95xF/KYYJ9N0mbmTeWpmrftDRIAPMXSM2Wt0U8UqW6V6zREwqeBMKvfi948v5B8eRDHYvnr45+RNS6N4Qhhe3u/NguIK89P/GG86cju+NMQkM18Ow8v9t6032uw020J29ogupuW+Ow8ieFgEKKCs
*/