
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if defined(BOOST_USE_UCONTEXT)
#include <boost/context/fiber_ucontext.hpp>
#elif defined(BOOST_USE_WINFIB)
#include <boost/context/fiber_winfib.hpp>
#else
#include <boost/context/fiber_fcontext.hpp>
#endif

/* fiber.hpp
8XqQ5c5MxMN8T62KXRjWLFBcKDveYHlWfnZd3S7LycmOZNsweJsiPm2qoiDkG5BdRQ/LETWF4pGY8pNgAiXXGYIGBcG+l0Nr7LBKH2YgmtE44/VHy1TaYQOug31IpUZULW0B7jAWZ9KTaP0AVGp5xunNK1s++eIBZVRmd9KZqcgjU0HXZqLJ/riAzrzIYVK9hQ6kEb9Vsr534w5uYvyOuOklT6ndfAmu1gFe0oFEXtWbV7EWwdKPh7EUwXTVBrWLx/wj9zE8BvmX0XV5EoY1k4oYrWW/8YMO7TJQ9sXoTMzIccEmcwENPG/Ym6UdvOK+6X249+GWJkeA2I+2pO+YQmOkyqsVwtgNRSZnP8G4oFnu5Ut3wYxqhqvZCoxEWD6TxE5RJZzFrhGkzT5OS4Xq95XGgj7vx6JZQdwD7hDlhBjNqUvprW15oMU2TxZ9D9ZDUJ3toSXmMaMo79AzGbYY+LZ6E/opV4wc1tpoho+u+owD6u77qd/nTR0kxACK2qWUhPHsVPlNJgnJJ+OiEE712bhg5O7pXMsnV8DDNTrcteH2ekKzn9KZzZDxyA==
*/