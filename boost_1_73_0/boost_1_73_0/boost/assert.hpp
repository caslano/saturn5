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
1oOXid/5M+fX14HBP3qAFngReKDzXBgwKrVzrhFoXogYpcEEuIEETaxFRAshweYIqSgQJienF0fHr3swz0WcE0ajajC5qosEcn6FoDFGcbWAqLi2oFKSJuxEGEt4tRVKBqQawaIuDUE45bwwCvgVFwWPSA23kFtbme1+P651QZb3ExWbfrw8epDbsj3FBVlQ8gZUZcEqqA32wPH1oFSJSN1IrqDNqo4KYfLerSmkSCZ9pcFgURAUiQk0C5MRpq1neo4LKrJWWDcYJY3TNM9VeY+RXEggaa0lqSEXEE+iyME9qGWC2vP6Qy81tN70rv2XK7m1NQElyRLo7k7haNqFiBthevDx6Pzw5P05fNw9O9s9Pr+AkwPYPb4grDdHx3t034I0acDrSqMhzRpEWRUCE6/w530uMIXWtYHJETlSpiKrNXe3TZTVZXoOFosgVmU/I9PqyN+w/+l0LDez7Q6A5CVuw4FG/Gu6R+uUZpFJQiGN5TJGxwN06+Sa68UcYB12gagufIabwYCOyTOkkJ5h0cBcyV8tRHgnxiJMFfkYuSY6pc9wheMlw5SXomi2l7rZcJMNmJG8avn+hWvERk8xDH/MMGS/dYgD5dXiaJOjs7P303Dy9uR4P9zbPz0/3IbhwJPe7b7ZDw/e7r6e
*/