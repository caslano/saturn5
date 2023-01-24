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
ukZhvCehzX/Op+mNbveKBs/8VTak3TsC5XqnELqsSH9/Cua6BXOYrEevCeMY8atYPS48zySJ75yCelT9Cef+YmzWH2zsuQ3SzjTXee1Wm8laY+djRtkfvP16Dtu2EQ5ZkWf8OPTNDwWeMEwkzmf9yZ07bauwoOeyAfnFpSO/j55l+YERXBzePh46cOefGXyhx+zW0u7R1NkxAIBXpKIOqY/xkz++0wIa+D7kQLK5wFPDCqfFDML6aAJ47XJ1jWm1q1qg7RwHfrx9gsXqYHK3aQr44eX7bKtKHE4nHTBUtbP5eP22TsK43DmrBgPVUmd3CYcrC0rdfl29h/Ea8sS3VYeQuTPEcomNhDySU1C2l0Z6qADwwIJO0K2PMH3+0ks8NbCsWM3yOc74x/JSMB/eOMAlJ2HsZ14cxIU2EOTo/tGIk5MD2RZOALI5bgpsjN9J9njCS0nkkzwRfPjlECYjhd1NpF06ATw3/iOmK0j2RJGmcSpbf2/m+pWwiyDwiSwR+X29BbqViEGa05MxR8jW8zQmj73aUbOa8p/AiyHttX0K7NrrWB6RY/KydLK11N0tTM9he7Q4RCoP7L/jzu1Q8kimp8HRFc3Sm1kb1bJ1/EIPVgAm+yUNdlc1Bvoyvie6i63Nd7zpaXA6FppKWbpjU9HXD7+NdLBhEvWyynTU//UObnfGEVXC/eck5V+HhJ6pB7eHEGcda7uH0oP7
*/