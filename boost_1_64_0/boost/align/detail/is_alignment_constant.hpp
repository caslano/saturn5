/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_IS_ALIGNMENT_CONSTANT_HPP
#define BOOST_ALIGN_DETAIL_IS_ALIGNMENT_CONSTANT_HPP

#include <boost/align/detail/integral_constant.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

template<std::size_t N>
struct is_alignment_constant
    : integral_constant<bool, (N > 0) && ((N & (N - 1)) == 0)> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* is_alignment_constant.hpp
mo5AeVriwrGzZ0uUOCUZINmQ8JrWaOPZ104LLO7erKJMiM8/6wMZ8k1CvcloajiJbUhshLBxYvrn1yuBtXAZ0EfHtfRMJUl1AlQsw/6UHObie1ox2CVn0GpCWX9rQgQXviQGyvDOLAY8hUb2OLsLq8zqd6NEBYNgFBnDSAE3xmheVor9OvbHWg6aJSar/aEoIaKm5SooTZaeBLwRAdlaMxCPIRV/Ifv4kh5LDu7Z6+IpXPEt/J6mgr4oriHJ2rFtuJdFKNPznngqc04ZJw36TTXoMLf9c6sDLL34regh9I0Go/OgQh22DrGi/6rmq9qHCIDFpahz3UkNMQjQALAd1TDZHh15q8b+8uY2OkVxMH7YlW+WvviOOrJuT16sUUUP8TOHentwX+dj8WeoJroT6KaSO4CklanEECIhJPG4YqQNvZ8lzad6FVa3Z12u0wF/7yN6LyIyeiUF3ts3EIPAStg4aT4t16yE6mbzWVReMwerIAowtn8zsi42U/naOM4nrUp+/4nCKX1Or7NlokiUWwt/fgl4BEE3+fNl1MrmHlr3p50k7XD6PoC6nA==
*/