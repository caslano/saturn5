/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#include <boost/config/abi_prefix.hpp>

#if !defined(BOOST_LOG_ENABLE_WARNINGS)

#if defined(_MSC_VER)

#pragma warning(push, 3)
// 'm_A' : class 'A' needs to have dll-interface to be used by clients of class 'B'
#pragma warning(disable: 4251)
// non dll-interface class 'A' used as base for dll-interface class 'B'
#pragma warning(disable: 4275)
// switch statement contains 'default' but no 'case' labels
#pragma warning(disable: 4065)
// 'this' : used in base member initializer list
#pragma warning(disable: 4355)
// 'int' : forcing value to bool 'true' or 'false' (performance warning)
#pragma warning(disable: 4800)
// unreferenced formal parameter
#pragma warning(disable: 4100)
// conditional expression is constant
#pragma warning(disable: 4127)
// default constructor could not be generated
#pragma warning(disable: 4510)
// copy constructor could not be generated
#pragma warning(disable: 4511)
// assignment operator could not be generated
#pragma warning(disable: 4512)
// struct 'A' can never be instantiated - user defined constructor required
#pragma warning(disable: 4610)
// function marked as __forceinline not inlined
#pragma warning(disable: 4714)
// decorated name length exceeded, name was truncated
#pragma warning(disable: 4503)
// declaration of 'A' hides previous local declaration
#pragma warning(disable: 4456)
// declaration of 'A' hides global declaration
#pragma warning(disable: 4459)
// 'X': This function or variable may be unsafe. Consider using Y instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
#pragma warning(disable: 4996)

#elif defined(__GNUC__) && !(defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)) \
    && (__GNUC__ * 100 + __GNUC_MINOR__) >= 406

#pragma GCC diagnostic push
// 'var' defined but not used
#pragma GCC diagnostic ignored "-Wunused-variable"
// unused parameter 'arg'
#pragma GCC diagnostic ignored "-Wunused-parameter"
// missing initializer for member var
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

#if (__GNUC__ * 100 + __GNUC_MINOR__) >= 407
// typedef 'foo' locally defined but not used
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#endif

#endif

#endif // !defined(BOOST_LOG_ENABLE_WARNINGS)

/* header.hpp
kExRh4/yBvyEWrUXkBjYKAwSHkMtHpCKOJqGvWc5uY6oL7tPQ/dqR49niLMSJnTYC4oacU8NAUu9nFyIWRrPWyh038HH6iI0IiwTmiFyh7w7q2dzK+6e88CbL+YsF51HEUs+mEnJq9vbwkKUyxkhONMAfQYoBsb/WkIk/XshH8+f2a2PcpfzxpLbfdnwqKPsO7RSXLOOFKt+Vu6DrH1EFCmvUjPhjqJ6IcflwlRqD++WzkGm
*/