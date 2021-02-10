// Copyright (C) 2014, Andrzej Krzemienski.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/optional for documentation.
//
// You are welcome to contact the author at:
//  akrzemi1@gmail.com
//
#ifndef BOOST_BAD_OPTIONAL_ACCESS_22MAY2014_HPP
#define BOOST_BAD_OPTIONAL_ACCESS_22MAY2014_HPP

#include <stdexcept>
#if __cplusplus < 201103L
#include <string> // to make converting-ctor std::string(char const*) visible
#endif

namespace boost {

#if defined(__clang__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wweak-vtables"
#endif

class bad_optional_access : public std::logic_error
{
public:
  bad_optional_access()
    : std::logic_error("Attempted to access the value of an uninitialized optional object.")
    {}
};

#if defined(__clang__)
# pragma clang diagnostic pop
#endif

} // namespace boost

#endif

/* bad_optional_access.hpp
eJ/ENdFSS6txrcG4dW3y02oeuRVTuJAYLVI008VgO/WpGR21QBXSBcz++8RWlRS2H+zBxXnw52A6dp6WflUttkW1rv2bbL1zdyxOYjje2Fvi2YWFsCsrhZV1upaGSb4uP0tsrXtVTLBfFmEeIgvlzb1gtASoaQb0AvtQIEcamaWDw27jUGlLHZDammr/bZV1dv6fUsS7BniEVKKFq4oqc5xuct/wnZJjysK9HKHw/T9c+oWqJWHEQsqtOE82QLYau/oWFRYBq4btmT74GltR8jk14xPbMJ0N+2f7ZBxz4OM31fwXtIHq94e2rrDGNVm2fDWXyXzIYSTYKnXKtP5Ah/vKo1a0t9grNbiGYYv5NA3qQZDIwChoCqC5v+tLBgS3uk7MvY/twamZt13sIQPNVlnEWSiK7LiemAIfvsWaCfPpV53Bxw8FExHDt79+yBhd+VVhbFlU8TbTqTq0o7E+q8ZSdVRdlPVhM2ztjWhvAi4jFKO9D2zQv7wsW7t35efWP1BLAwQKAAAACAAtZ0pScMhOGi4FAABNDAAAIgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2xpYnRlc3QvbGliNTk3LmNVVAUAAbZIJGCtVm1v2zYQ/u5fcc2wQvYUOykwYInbbG6atsFcO0icdRkK
*/