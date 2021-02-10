//  disable_warnings.hpp  --------------------------------------------------------------//

//  Copyright Beman Dawes 2011

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//--------------------------------------------------------------------------------------//

#ifdef  _MSC_VER

#ifndef _SCL_SECURE_NO_WARNINGS
# define _SCL_SECURE_NO_WARNINGS
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif

# pragma warning(push)

// triggered by boost/detail/lightweight_test.hpp
# pragma warning( disable : 4640 )  // ... construction of local static object is not thread-safe

// triggered by Microsoft's own headers, so disable
# pragma warning( disable : 4820 )  // padding added after data member
# pragma warning( disable : 4548 )  // expression before comma has no effect
# pragma warning( disable : 4668 )  // ... is not defined as a preprocessor macro
# pragma warning( disable : 4514 )  // ... unreferenced inline function has been removed
# pragma warning( disable : 4710 )  // ... function not inlined
# pragma warning( disable : 4986 )  // ... exception specification does not match previous declaration
# pragma warning( disable : 4711 )  // ... selected for automatic inline expansion
#endif

/* disable_warnings.hpp
mY2cKdU4ppX1dJSGV8DaidxV3rRHq0rz9hPQHpwFV0F4HaSh7VGj9ECPXjwagT+JQ5xQX6awx0ToIdkw7fCMhNsd5z9QSwMECgAAAAgALWdKUnTJd+0yBgAAQw0AADEACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1BSRV9QUk9YWS4zVVQFAAG2SCRgrVZhc9s2Ev3OX7FVP1TOKLSTNmmb5jpVHeWsiSJqRKqpJ85wIBIMcaYAHgFa9lz63/sWJCMruZnkQ+mRSYLA28Xbt7sIr0b04B+7gpDh6ItX6n8pLtyHRavG/Edm7v8vSNMP1P1h4RXuX2HqlA6rPqQn9FWrPtDYr0p7W8/5OU2/wtwVO8n/TnnxVcqPGOlW9uvPTX3XqPelo/H5CT36+eef6CE9Pnt8NqEXQitZUeyk3srm/YSe537kt1Lc3oZW/joh6UhU4RFgUipL1hRuLxpJeK5UJrWVOQlLubRZo7Z4UZpcKalQlaTzaHU5X/57QvtSZWWPc2dasqVpq5xKcSOpkZlUNx1MLRpHpgAC8HNlHTBbp4wOYV6Sk83O9jDshKisIXEjVCW2MCcclc7V9tnpadY2FXZympvMnmYDFWHpdp/s6hLe7MQdmdqRM9Ra
*/