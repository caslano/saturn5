//  (C) Copyright John Maddock 2001. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  BeOS specific config options:

#define BOOST_PLATFORM "BeOS"

#define BOOST_NO_CWCHAR
#define BOOST_NO_CWCTYPE
#define BOOST_HAS_UNISTD_H

#define BOOST_HAS_BETHREADS

#ifndef BOOST_DISABLE_THREADS
#  define BOOST_HAS_THREADS
#endif

// boilerplate code:
#include <boost/config/detail/posix_features.hpp>
 



/* beos.hpp
Iypzq0XYTZ670QpVLxifj/g/9TqhjUqcQK48ujXmSg5IVQ4Cix7/ZDTjdWOqlJZ8Cs1ADrRdJzdeYpyUWFZ8cEUnqcNcKdvaofW9zX34w3s/PEWu1eWJ2CtUhf5sGM65d7WkJKJpSuy1hIb3ZKEqtrFQCn1pCT0qXyGmHDHyvPEyA/icXLkS8LO60q/F5loG2CvfgdsLqQN6tPnW5URzfW3By1jlZlTNktHdysSj479J2MamrnLwLrayCpdvdOSMh6rUes2NgkkhidwlzXXCc9GHyWoDH6S+nvMEbYo0SjqoTmfWdaHUL7LtfHk4Mo1ln5ZAuFo3fFf4ow5RU0ns9rEbs28s4JaDDmrcbrKskYNSLeAiv2///trSe+2L0i+/sdsvIZ7WNXLHI8Ji1gbvFRNvWxY0rlhr5x6/Wu5ANi8wbH3VfCsoV9v5zXlzsarP+fU2WuwqVg1Lj4+LKe8dKsqp9K1qqjvFZuUhu8gbGHT3De0r4gm3WiBHVVnssdXqslguNp20yfSxycCgpmZTHx5FtMr3C57GUFOx63IydNUjcIkAfhTKLPBCjDBSxul4+kJ4EPtyUWjFKdfUnS8ueciSI40fTl59/kFJAHppu3rC3YyYcU3gXXuKgqa+cRnvjFT6AudWS+PAk9O8hUql03LLhuCe58s7Qdd6ORY6GiN8RztPTKi0GX9K8qhReYMNrQ+HGimplz5UrrVX
*/