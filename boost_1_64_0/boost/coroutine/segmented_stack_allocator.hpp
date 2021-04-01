
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>

#if defined(BOOST_USE_SEGMENTED_STACKS)
# if defined(BOOST_WINDOWS)
#  error "segmented stacks are not supported by Windows"
# else
#  include <boost/coroutine/posix/segmented_stack_allocator.hpp>
# endif
#endif

/* segmented_stack_allocator.hpp
yhvTlhtqMx9T17+c9puonj2C/sXMSsZtHWkCCRjhJjX6ln/aoNEJBlEKjDzZ+eQc5LU7ixM4PRNK8rwfOAMm3FjTTLAOyBEfqWsnbl0Vfbn0+hraPDNSj+sHH3jRIYIhhabwvpagq+XBesLlKKx56fkMf8nuj9bY8esi8Q/5S0x6NVzAsoo+RonI1ihESlXuVbp+GhbPYZnqWlu3vFEqs8u7NwLUP85SJYQh8YWX+OYyvCxquS6tA3Eo4Cjnc7UIgjucX9Xz3xKQWRsOhO9EhnAnMQdYuOrXV+O/4bUbBd3iRrKvB2b3oA93WdXz4YAGLkhKik6GzPQ1TFPLmjzrL5exAO/Fpr3qto7B4/VTCko7i167pXNtlJwwUfw0S+HeVI8mUhNfQD9PXBqwdU159Qj5wisjHzBoxNZXZ9o6Na8ChUMlz7tk1AYzP5XLSzXf80Wd9WKA8r5euDk4wnG4jvdTL3dScAxrZqKSFqKrDFIc1ggmsZVojZViIihSPvPUhjpv2PuLk6PqDE17SbghXicO1d4VkmE4iQvn8DcoBXk4Szh+SZPyraK9fQ==
*/