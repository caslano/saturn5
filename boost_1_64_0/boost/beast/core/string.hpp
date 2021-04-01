//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_STRING_HPP
#define BOOST_BEAST_STRING_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/string_type.hpp>

namespace boost {
namespace beast {

/** Returns `true` if two strings are equal, using a case-insensitive comparison.

    The case-comparison operation is defined only for low-ASCII characters.

    @param lhs The string on the left side of the equality

    @param rhs The string on the right side of the equality
*/
BOOST_BEAST_DECL
bool
iequals(
    beast::string_view lhs,
    beast::string_view rhs);

/** A case-insensitive less predicate for strings.

    The case-comparison operation is defined only for low-ASCII characters.
*/
struct iless
{
    BOOST_BEAST_DECL
    bool
    operator()(
        string_view lhs,
        string_view rhs) const;
};

/** A case-insensitive equality predicate for strings.

    The case-comparison operation is defined only for low-ASCII characters.
*/
struct iequal
{
    bool
    operator()(
        string_view lhs,
        string_view rhs) const
    {
        return iequals(lhs, rhs);
    }
};

} // beast
} // boost

#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/core/impl/string.ipp>
#endif

#endif

/* string.hpp
6vvYivUwCUJpWUUs8GTfGR94laGcFKI3IPog/+a0i8eXdkgsFmYsPPVsrlcKaH0EgWm11iQT8q2QriQyLUzDeTpWKbsjsyYth/qYROdDaY8OyXRA0ngUOqM6yPIAzQ6XnnXvS9aUkUlCatqu6iBYHdutLYEfcL/NPBTElkdt/4CElg9cxlMFjHvtWC08k+AJCbU6u1q+2Q6fcirf6dfV6dP/rueP2ew4zoo/1z2BFbVXwP2kSDrgW9fjBU9VoA9VgT3+Wj+uw2C1dUFgabljhmySoFv44vaKYWGhYE3KNxQuhR5K+2pcbC1+qWp02FHXCsn/GG2T2+b8NaBaLfyKCpJj5Yf0HIDy0Wcyf0ImFl+1C1+AAu78Edsda1UjlHf+JcoHuJ9FhHYJrQ2z7jT0XCEZtrmcwK61n/Kyz/lPTYGqLmM04LnSMOCgVCPw/xM6j39otztC6xl/CCmX5vZBYegkHCKCjQkTKt/IUJtPHN/g42jlldR7fPrPWky6DqE9QVFlf/iGahf7k4QsLjr9Td/l/g5rehNcQzxzjPJCzT+oaPquUrpUlki+6Q==
*/