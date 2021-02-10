/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNMENT_OF_GCC_HPP
#define BOOST_ALIGN_DETAIL_ALIGNMENT_OF_GCC_HPP

#include <boost/align/detail/integral_constant.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

template<class T>
struct alignment_of
    : integral_constant<std::size_t, __alignof__(T)> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* alignment_of_gcc.hpp
7NIxX+8FBpiqPzv/ZBaJ4Of3IyvwuGM6IQqIWZ2/uMV42UgflB/0ig9jF7sunvFIt6zSj8fecmI8tn09rydyCa63LY5ibxAz+a4FDfB9fXVlRoee2nad7eBSwQzE+3RblM0MZoy//I223x092v+hLt1bHgLafmydEKiBpw3bWnr5HUOXYPm9PyCOu0usRHrBXW5WcVxtqW3I2jF7ktFe1w2TIgOJ3cADF7UlyDYWsB2CNjRWQXVDVuk2m+cNOSYXQVOGy9+xOcpwCDO1B2K5qBPTPBJhvFMrudf4MMHEcrktCSR2OQ9BEHm/Uu8vao0u752/Onr8fP95NkVpV6gV6mVoTVQJY7T3O49RA7AQmW9qSmUWhwBrtokaMOFozR/DyR/qxc4vL6N8ZFzCfASWt4mQWAsssUOercytN1cHPIexxm8a8K/OzovX796fvszevrv02rGJLBZ0JBXi1CXQjuKCH+wQf2/FITmeHdj7LQyTwe63lA8j2aaS3d6TGBF7CYeHkcmrFZKY5nQ/sl2eLdCsgviKig0qx0TdXNebwITIvqS4lKz0fo/7zZVq4ETnTeM9AYF1jvwu2BEP35+fjNANGtFeChSOhjhOGhOiWcTMZN6fAKJcgR4KjHRmyIOIZx6Lpkt9hqU+y96o
*/