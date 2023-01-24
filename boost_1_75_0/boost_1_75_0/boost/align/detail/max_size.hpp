/*
Copyright 2014-2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_MAX_SIZE_HPP
#define BOOST_ALIGN_DETAIL_MAX_SIZE_HPP

#include <boost/align/detail/integral_constant.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

template<std::size_t A, std::size_t B>
struct max_size
    : integral_constant<std::size_t, (A > B) ? A : B> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* max_size.hpp
dWgSaz7FFbHKe/QCAO0FQ7gcrr9wZjA1g30ABNsJWg9p1K6ukeAbXM+Xrayxj97KlXgHrQ6lNY/yDJohB0jotkms4qRv4mZPl7wGT0t2Go8AdfoFZAxJUl8BZap4jVcwvgOcK68N30vAJFHZ9A5c5Qe2yhbEVvwBV4RO0km7wF+HSKTAgYWpGBeWUEaMCgqTkrBD7K8TdpAb8WPT/sOFXeRG/NSDVmD6ATf7zVSsoUw/VOM000PINJVu5wK+FSwWcxRzFIkazK/hfNV58ykjruhfMfc7kwlXMzI6JXVFXDjM/3xip2XCgIag3foz/gWJnqYgYUqfBnoFVWCTyY9Z5VkpBXNkCnFBkJHRXzEZceXOJSaJO539PfRd3gfHlG4KwsQcxbeKVs3jG57PBkXrATMTD4l/ydxGZQPAeLuVD2CNN1WiE1OJntzN813B3X9ZsFAi4bqW9vihhglhf6+8or3w5TWtwq2HOVpHU65xIydZ4Bjc3+Y73MyBUErvuYZXj/E7dvS9SyBfDepqd8Tlxjm4qgeumgBJ9LzSUe6Kyy//idcvh4AH1fVP7C4W088uAiS3Du3xVUB7h8VuJkZTZ3DWjL6ewTJF/5WB4/GrEFfHYr1O//aGVc1YY/BJ+gJc0aw6kiuvcveVsxxoVankaR8osKUP2GSX5XjhwoPuicvOScD8shZqFJ2EAZcZ3AROpp7Da8pQDCqJHrfc
*/