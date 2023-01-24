// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#include <boost/config.hpp>             // BOOST_MSVC.
#include <boost/detail/workaround.hpp>  // BOOST_WORKAROUND.

#if defined(BOOST_MSVC)
# pragma warning(push)
# pragma warning(disable:4127)    // Conditional expression is constant.
# pragma warning(disable:4130)    // Logical operation on address of string constant.
# pragma warning(disable:4224)    // Parameter previously defined as type.
# pragma warning(disable:4244)    // Conversion: possible loss of data.
# pragma warning(disable:4512)    // Assignment operator could not be generated.
# pragma warning(disable:4706)    // Assignment within conditional expression.
# if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#  pragma warning(disable:6334)   // sizeof applied to an expression with an operator.
# endif
#else
# if BOOST_WORKAROUND(__BORLANDC__, < 0x600)
#  pragma warn -8008     // Condition always true/false.
#  pragma warn -8066     // Unreachable code.
#  pragma warn -8071     // Conversion may lose significant digits.
#  pragma warn -8072     // Suspicious pointer arithmetic.
#  pragma warn -8080     // identifier declared but never used.
# endif
#endif

/* disable_warnings.hpp
45o2vOrmB73VsYly+MmgydHvFqun+WqVUNqp31MD3qfe3mN/e8Cb/Wn5HvydEjrPmHoticI/CjTA+3MVjcqzO4MXx12LTzVrTcRjHopi1gLBY8dSWnW1mpVV/8TSH5jS+/hgbcFf996UhhaQKB3LMv290K8n31yrD0ZZh964rJ58dLeFQIQARR127Y3/KHNsydLABd1SYGDgF/z6Y3gDDbWZO7R3ycjdI6265h9h++eoGxqItxq2tvqvj9z+WSmDv8hdQ2f7EgICv+a/pwmQ/wdYc/4B+lf34OSod1Qe7+ZtL/JmvWTLjoWbm1mOpsD0ueA3n/Rj9ec6rE0e/EwCmlZe0ug+jNakqDiFhblfeaNIvdnlEuZNKNLigsHAqigBAqdbZhxsFenJ3pz2BtvX1kSx9Wxsq70sSxuaAZ628ooY8y2OuOAG+lchgvFDSRwkxTMZNjybZwIqV1CigXzae4Q9uaibRSXYuf2zmK72lL7JigP/jY5ObYqKXMTW8HhsTUvY21fuLVMry2UxMYhmrdIe9/0NWdsbDKn/T9n+q6UgEV6w7f5DX5OvU1tMj/zFixftL//HrOr9f5pVcQv+zf+3z0iB8XNeEjc1P2hILStpJX371Swy0YxIHZFeGsVRTaBJWyINvOLpfK5MHIyjD4x0e1XS+s3ZIE84P8dEgDdshnPxg1N/qKRRteMhvVMzX0C+yZyjsuGitVEz
*/