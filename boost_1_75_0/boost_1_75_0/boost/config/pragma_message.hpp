#ifndef BOOST_CONFIG_PRAGMA_MESSAGE_HPP_INCLUDED
#define BOOST_CONFIG_PRAGMA_MESSAGE_HPP_INCLUDED

//  Copyright 2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  BOOST_PRAGMA_MESSAGE("message")
//
//  Expands to the equivalent of #pragma message("message")
//
//  Note that this header is C compatible.

#include <boost/config/helper_macros.hpp>

#if defined(BOOST_DISABLE_PRAGMA_MESSAGE)
# define BOOST_PRAGMA_MESSAGE(x)
#elif defined(__INTEL_COMPILER)
# define BOOST_PRAGMA_MESSAGE(x) __pragma(message(__FILE__ "(" BOOST_STRINGIZE(__LINE__) "): note: " x))
#elif defined(__GNUC__)
# define BOOST_PRAGMA_MESSAGE(x) _Pragma(BOOST_STRINGIZE(message(x)))
#elif defined(_MSC_VER)
# define BOOST_PRAGMA_MESSAGE(x) __pragma(message(__FILE__ "(" BOOST_STRINGIZE(__LINE__) "): note: " x))
#else
# define BOOST_PRAGMA_MESSAGE(x)
#endif

#endif // BOOST_CONFIG_PRAGMA_MESSAGE_HPP_INCLUDED

/* pragma_message.hpp
DVqRZ9BreJLaAUez0eOo1UrUPVKFkMRe1CF5NCfyYE00BGrkrRPbCRq206MZvL8XQz84Z+yH5gdVtIP0wz2QeeJBIhuntDb7lHhLZmGytTBuRmiUqEoeySzheOE2jtgYIlklFkr9crlSJLtVmPZasZx0tGHD0aJ3OwrlUmkcNUjQUBEa7dBkJsdcjK5pNNA10avRNTbXZXJM1wjXiyyGzEuQYqmjeIyT41QGZzAypGEl5+4yEyjO9UomNzxHyDE1hoDO3p9Ff0xgObx6M9i4ac5NmuwArGDPpcHacP8+oUgMSQE5XwmpMRiS67CjQF+Inc2OGtcaXXe0uus8LW4ShSAoe6R12EAVRpEv5A8E8oOh3FjofO51OK8g3BxpzquJLgvrea35dbGW/GCuNxgMePzrvAZK+jQt7Ao7HXqlJ9+tkdOioXDUiDjCRiw/Xwuk1+HXYV7kzjgv+v9FRWWEHv8eZJ5Yp6IameigMxQ2kymkXB1RAiWlx2XEswVBUk7PXpBBKBYXefxIHfe6xxDw2AZGFDId9KRZUzxlNz8+Th8/zB8/TVXQyZupCjr5JFVBJ5dQQWPS4gWToGxLI9gatgBNtWHJPDZ2CcvHMJqRylVtWVQDvRi/txWdxjhXOC82SoYcVVdqzY4Pdb+zEXB6oWe512+4vRU+t7fLX+Ztxbo34el3bw00Botym0LuvIqQO7wyUhZqw3ookdsf
*/