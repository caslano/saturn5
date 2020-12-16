#ifndef POSIX_TIME_SYSTEM_HPP___
#define POSIX_TIME_SYSTEM_HPP___

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland
 * $Date$
 */


#include "boost/date_time/posix_time/posix_time_config.hpp"
#include "boost/date_time/time_system_split.hpp"
#include "boost/date_time/time_system_counted.hpp"
#include "boost/date_time/compiler_config.hpp"


namespace boost {
namespace posix_time { 

#ifdef BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG

#if (defined(BOOST_DATE_TIME_NO_MEMBER_INIT)) //help bad compilers 
  typedef date_time::split_timedate_system<posix_time_system_config, 1000000000> posix_time_system;
#else
  typedef date_time::split_timedate_system<posix_time_system_config> posix_time_system;
#endif

#else

  typedef date_time::counted_time_rep<millisec_posix_time_system_config> int64_time_rep;
  typedef date_time::counted_time_system<int64_time_rep> posix_time_system;

#endif

} }//namespace posix_time


#endif





























/* posix_time_system.hpp
0TUX6GeqQ5qu3hiVJKU25KTn7diG+jUiFIwHDkCC+UAiIjk9WkNoYS8SNqC1wJcOHz8Y0MjbWxnQfD52tOkc+cOb0YA2PUUGtBwR4QItwXmVyiRIJ0JNigJBl6m1gmSwc3NYexYiKFBVTgOMJYL5PVxNTgnlClGmXhnKhobuR9TSoLRucKO7XdJN+UHGQlt+OB2vELH3T2aRp9QRlEe/GJBM/98f2F2+3+jOd2kJvekBQf8D1lDR//4Hdpf/6935L62tW5TdmGVB1aq9aDUNr47mqKgwR9FrOqp2cQa6XTJMVpkSYpAh2pkil0HVoh2wJOLvPKblkBQe0or7yPeBaZBjHKSmkYBYD6etWa4pLCDUfJoxpPUHnLnT1yNGj7UyI8u0ms4HR1AlN2DCKIlNFHVynsMGhwaIZOS2B8khHxC41nBl9UMP8pgxey5m3CzNlbZ9QDfHooGOeWT3psSISFQCcr5VtQqCuNhy4dAMKfvgJIQcfkHqtgSxJkGC/VTFmsRq2nUBixLAb8gAfq/WC/gEsCphP08RS3RszBnTN0vb9iYlOYA2Xzd3NvUyndPorDzNsWvD1aprZyjJr9u49vUhbWOXWxu7i7axi9oo7NyXvzpkI3pWlWr2UV7alkFlGq32gtWq4IrHEG710qvUUwSfLt2tr7i3+FfM9ve3etRM9mmP7hQeyFwWLINLRgEgeqnqvGtI+2+zW/+9WLT/NlP/CcP4Q6+otjwNU8Nj6j/RhlReG1bdPqRt6HNrQ7poG/pybUhTGz563zYVby1zCayIeSdbTf1v9qeASM5fNb/HhZg+HZk6jiu6S0oJCSG0wtCXpshjSwYCEyE2I90JQIR9UYAYOICrHWbU6tLspgfa8JAJ7LachTxkTJqSf7kzpxRMohVNZBj2QXgbsMkFtqwBXWKWSl40x1xh4QAIVRD93Q4A8BRf6kmlQQiAkaVqonX0hRXWDvr33Yvy/12xEP7tsbPs+e35DXr/jUFALv0p77/TUh9O8kMcuSXXCJmUWPEY1gosPkI9QXlr8XT1BMXU+faEkdnrYNIxkYHS3+hSM8/8csui+tVVnXAsnhHAXGA2+0jFOkiRm32Ai5t9O+jTH4FFCcPZSnBWdS89aWDqjhd5oSKxqKWZbw0UpaUKwBUrkLXD1FJlQ4DOhPPiDoQ908L7fyhA21ZITo/+A047kB5FFwhZsS+/YoLT0i+9ZrQG55LD77kgTxfC6tKX0yE2ae1BE0xqSnvwhJePqXSOvOFa1B5cvJy0B3xw2JFyVsbHofcgkZpg4W7qK7isTQxod59dWWw5aQmg1bChpApSRfDanWpIlCui+Xhh5p/q/12n9GYFjxldOqXtklIavnalwGwFGToDiTzTIyg+0SNGRRGKxcglil/98q7w9kYX3ko1wPVfFhR/xRIUr7d2h+IZX94VHq934bHc+L/4JW1D81etgsilLFyqVr2m33bqN6BGO2UcaRZPllg8pUn4WEIxQK/pCWqHlq2DfQOUkjV1WEgdH3GDd6zlKsZ++YCwn/RJ+wkX5RUboAAwUE3qDgY6e1+rYGbO8WK7ooF3rvmhB9ybf7Vp/h2eAs3//f270/y7ZfPxDTVW98PMAN8REgYRKddL4tAqott8Rkltpjs05rlYcSVL9lbCLTuVWQITgwNAmgXarbEWG2xcQLvPfnfuDt9QHQGYE4A5RrMabFtD8LKVXoIuTveHAnJooqGIN0u8A+umOU9Ipp/riUvx/VwrdQpXL8Z6Bil5fLQCJSKbxLKJwUNjP8nN6ZMImo+gOcJixm62CyVIkEcJGMPA0wS/+xnhEacaeQcFGHlRBDsoydRc9Ee5g4o57aAa5Q4=
*/