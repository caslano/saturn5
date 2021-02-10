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
E+C2jS1GQ9kADRtsQVIEB4Mf7I2NsYZs7S0dak1CZlMbrEBtQEmBqg/j1AlIm/h8lqJyYRPuOmArAQnxMWoV4F0n88H2AtYC821OSgyxLr3ERayXAg9UBgttGgbfpWC3pMjmYL0FYIGRkaEYzuwOSjQ5BKHYiGhA72SVpHzJ9MOSjJNtojA6wRYk1jYNGyvoNkmqCT0McUFE3PVmsD5qG9oaWRzeY+f3277GAZatTyoYRorlsHAKrVFcyuaJSzOEAnJTT6FcNZA8ZG9jIjvnomQp21xsa3ORt0lodaNo3djCVus45T4sWVp8Qt5uaiaqqJZySKNtQxrlQ0r9RBEdhHPLtvua6HUN+2rVZpEfOtPyfM3AxBUlZQkjRLtsDEbeJEy4ydzGTCNPg7iaogQsyB5pnOFjEk8FBFIzCAyD636/wcTvkoH0mUR2bvnRsvt/M/v2Hmr0Ufe00SeVCz5M79MvU16wmIT6qtVfCgX95fepobDQYbYsZwI1HTe1ssC7t5LQvQFH9zRy0sVLMTP7HaGQ2K3nMFWbXUNtEGJLB1xc0WibKpLo/NRKbl12Sj5x4Cy5QtMNhPcqK8hp81DbutKHLqEwJLsEHqyEFiaAQ8+9ISasVb81sNinsgn3qVZDW04DkUURuB8SV5u+
*/