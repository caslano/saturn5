//
//  boost/assert.hpp - BOOST_ASSERT(expr)
//                     BOOST_ASSERT_MSG(expr, msg)
//                     BOOST_VERIFY(expr)
//                     BOOST_VERIFY_MSG(expr, msg)
//                     BOOST_ASSERT_IS_VOID
//
//  Copyright (c) 2001, 2002 Peter Dimov and Multi Media Ltd.
//  Copyright (c) 2007, 2014 Peter Dimov
//  Copyright (c) Beman Dawes 2011
//  Copyright (c) 2015 Ion Gaztanaga
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  Note: There are no include guards. This is intentional.
//
//  See http://www.boost.org/libs/assert/assert.html for documentation.
//

//
// Stop inspect complaining about use of 'assert':
//
// boostinspect:naassert_macro
//

//
// BOOST_ASSERT, BOOST_ASSERT_MSG, BOOST_ASSERT_IS_VOID
//

#undef BOOST_ASSERT
#undef BOOST_ASSERT_MSG
#undef BOOST_ASSERT_IS_VOID

#if defined(BOOST_DISABLE_ASSERTS) || ( defined(BOOST_ENABLE_ASSERT_DEBUG_HANDLER) && defined(NDEBUG) )

# define BOOST_ASSERT(expr) ((void)0)
# define BOOST_ASSERT_MSG(expr, msg) ((void)0)
# define BOOST_ASSERT_IS_VOID

#elif defined(BOOST_ENABLE_ASSERT_HANDLER) || ( defined(BOOST_ENABLE_ASSERT_DEBUG_HANDLER) && !defined(NDEBUG) )

#include <boost/config.hpp> // for BOOST_LIKELY
#include <boost/current_function.hpp>

namespace boost
{
    void assertion_failed(char const * expr, char const * function, char const * file, long line); // user defined
    void assertion_failed_msg(char const * expr, char const * msg, char const * function, char const * file, long line); // user defined
} // namespace boost

#define BOOST_ASSERT(expr) (BOOST_LIKELY(!!(expr))? ((void)0): ::boost::assertion_failed(#expr, BOOST_CURRENT_FUNCTION, __FILE__, __LINE__))
#define BOOST_ASSERT_MSG(expr, msg) (BOOST_LIKELY(!!(expr))? ((void)0): ::boost::assertion_failed_msg(#expr, msg, BOOST_CURRENT_FUNCTION, __FILE__, __LINE__))

#else

# include <assert.h> // .h to support old libraries w/o <cassert> - effect is the same

# define BOOST_ASSERT(expr) assert(expr)
# define BOOST_ASSERT_MSG(expr, msg) assert((expr)&&(msg))
#if defined(NDEBUG)
# define BOOST_ASSERT_IS_VOID
#endif

#endif

//
// BOOST_VERIFY, BOOST_VERIFY_MSG
//

#undef BOOST_VERIFY
#undef BOOST_VERIFY_MSG

#if defined(BOOST_DISABLE_ASSERTS) || ( !defined(BOOST_ENABLE_ASSERT_HANDLER) && defined(NDEBUG) )

# define BOOST_VERIFY(expr) ((void)(expr))
# define BOOST_VERIFY_MSG(expr, msg) ((void)(expr))

#else

# define BOOST_VERIFY(expr) BOOST_ASSERT(expr)
# define BOOST_VERIFY_MSG(expr, msg) BOOST_ASSERT_MSG(expr,msg)

#endif

/* assert.hpp
5qF/tD2OZfXntW7VEsl8v8rq7dcQeXyMLWqAl//Ihfnlcv8ArZeEdTSqrY+qkjf7TFKZCHxCbANvKkcDJf1uJ+m0JdR5oSvMdOfnKXW9cG+3SIMFn0d9CLEsbaP/MK8MnjzMzp/y+Xiikw9XLAa4W/j8zxK/e0avfG5whm57xTPZhVOCYJsRkSjh4UunfTQ6UZgUfF/gAi/Z3CXOg/UHQwnWbSde0XIOhvyhJGjbdZZoffXOZnd1YcLXvDphFBOkVyZcseBxAoHQ+26NBc3Qc8bEm69IWr1TpBnWZBcFFizVHigGQZ8JfKdkfCZRu/mOgfe3Vmqk1O7Q7kStVxOFdO74aO+VsMafComXt8j7wgp6qZxmVT7guj7zB/sQ1nECBS17yCqobjNh3KE/VkAs8TfwKtSaXBRYvO+qlPMbfBug6mh0gZRzOqns+P4vs2BfB3ZpWvbm1ObOE9ZxiRHusV9jR/FcbjI59zwQoM0urCEuHTze2IEx1TE/AtfOakcrdXLy6ahDKCT6/d1VGgDBOEQozoqzXxPyqgiiWDPYmPN2VdCAZSWSMZDKEg==
*/