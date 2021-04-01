/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_SUNOS_HPP
#define BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_SUNOS_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>
#include <stdlib.h>

namespace boost {
namespace alignment {

inline void*
aligned_alloc(std::size_t alignment, std::size_t size) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    return ::memalign(alignment, size);
}

inline void
aligned_free(void* ptr) BOOST_NOEXCEPT
{
    ::free(ptr);
}

} /* alignment */
} /* boost */

#endif

/* aligned_alloc_sunos.hpp
dAyVhNSNMhcDXYGuhIftelxH6dnhG3+SJtY8lG4IPri1joTdza91FC6/3WIA28Agy/hPVgtMajTprQaurFhxPwcMEmqdAm/0SEP7o3LjQG9dQkH8Xvy84ByOjP5XB9anfCfYZsBqxWSg5t34HeZPZiDqhuOmE8MK0uizrQ6bqO/PLWAZha09DlaoTPfsdunwm1o4RwC5SwVyYQCsgfRPbvAg81HMnGy1nHOkmZT2WV8HPoysCshIUAemtEnRXH7OBqAgaypiR59FmXMF3aiztegVJAYiG+vDWC1NRrOEmdHNxwxvUK2y0yybElah+qgKQuy5RdBwhUgialCF4PEEeKMnYh8njY8EfKKo0LuEbuEMd1kW43fYwSYH1wwiDQgbvQhZUZlqKRk+/v1twThcRtzkRa81dtRv2QOWAfNste2IpwI58fHttyglHhG6pKXr/HsAq94ayVgLYHrzu1QtvA2yFYB1eIw19bAmqT9jGjHSEWf8sAFfdN3jndCDWqMH5ApzFHmIdjpUmjWSHRpIK+qa9Pw8zbdadwDdSxe0YL0RqQwnhJHW0Av6cQ==
*/