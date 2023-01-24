//  (C) Copyright Jessica Hamilton 2014.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Haiku specific config options:

#define BOOST_PLATFORM "Haiku"

#define BOOST_HAS_UNISTD_H
#define BOOST_HAS_STDINT_H

#ifndef BOOST_DISABLE_THREADS
#  define BOOST_HAS_THREADS
#endif

#define BOOST_NO_CXX11_HDR_TYPE_TRAITS
#define BOOST_NO_CXX11_ATOMIC_SMART_PTR
#define BOOST_NO_CXX11_STATIC_ASSERT
#define BOOST_NO_CXX11_VARIADIC_MACROS

//
// thread API's not auto detected:
//
#define BOOST_HAS_SCHED_YIELD
#define BOOST_HAS_GETTIMEOFDAY

// boilerplate code:
#include <boost/config/detail/posix_features.hpp>

/* haiku.hpp
5rz8MpV8ccahaCkddCrlJuXVF4fIv1sXl/gFUPDMpVKELH7bmMIwB5tdzCQDD4YZ/AOptLejpHp5GYCWffMB/5utEwu46cLPvzeGlYXPl5TKZJKVhCVe5lLMovsPr2BcdUx67iBiKOY9hj7wVRkgjqD2H5XlsAAJS/OXov+l9musiBjS3eK2BaxAwlI6L94h4pKKX1H7L2efo7+oQMSldrqsyriW7nIxk8ujmMnR/yWnMZO1Uqn9QitkVrJeBZDsIkROdVa5QcUUR6qYUaOtQcKSKA9rZliSWXvh7KpMt9vz7UxLkLBMBN6KGZYE8lIKSMywy6mDbANrZtgV+K/kORIzLCZOTuWzinsbqWIibcjQWJVZLCX+w+ysOY/af3FF2JzuFnWK/x2CK/XYKFyCnOo3ev8GE5ZZaaSKEUwaOE3iy+1xcyYpCBO6W962gwkrXMQMl1kB4ZeIA9Tp4+Y9d3BXmLWDr5FTLUetbzNrT/yXfIOZPAxU1Yd5vmP2DR431zdUzj1IhhQyUS9bMGEFsGCFMsN+xw5gsbFqvwX+NSSGMxn1OMSENW7FYvSg7+ZXTEaZ7aVtj7P6hh4cDbnJPDoimRU2YobtzZid3bc4yBZmoTZnwlKzYBIezzy6Pu+gM1Pm0ZAkVvINZnI1gOHmG/cDOZotmHxXsfiWY/VtsyojWfrAlO6WZZK0r8bkuy6fmcxtySwNKWYm8xwk
*/