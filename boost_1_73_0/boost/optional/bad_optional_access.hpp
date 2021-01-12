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
C7nxQX2/gDc8Zl+Wn5qd6soXJ3OlVKXkys/tZl93bF6as4gmZV+m9uUP58hYIuinDsL1sAar6HcRjPuph/Z2WZLne/G2+G7twYjtWSR/Mw/y2Gs/IVu8wIfKmc7bIV4AZJ9n3yILbC/W1XuoejR6VNZFg+kkxzXgvYGpiAOjmuiz96ENlpd2tM+zd1pkvpzPOe3hPdsu+l6L8xexJWe/LJBBu0EP/Saw0Za3K4H84v/ZnmsP
*/