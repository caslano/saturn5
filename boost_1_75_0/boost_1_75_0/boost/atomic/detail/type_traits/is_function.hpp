/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/is_function.hpp
 *
 * This header defines \c is_function type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_FUNCTION_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_FUNCTION_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS)
#include <type_traits>
#else
#include <boost/type_traits/is_function.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS)
using std::is_function;
#else
using boost::is_function;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_FUNCTION_HPP_INCLUDED_

/* is_function.hpp
TAIoV6itTPqK9NnyCqz7V4iV/S1fgBYmxZcFnDrQ0swZSnU+9XNXTZ13EwYt3mQ2ImenDr1pewfWcWf9lrrVCroVVnM19YF02w7MSw4/dpI8yJbtudF0XXvahxoEq9KNzCLNzYP2dJHhiCG0lWeOlZ6legtVY86Ip2OOJbXJDIRg4VN3VlFP4VZib8lGxcZqOcmvcRkEDS28M6SR7dx0kr0tC2mGUo7ByeSH8cZ0ME7xIegWqRztJd2E/4PalWDDsNer+HMwszmpuUAvRjXqHNo82jxq7YJVDcB0RZYKVQhFEFUQ/RDV6F0i+XJZudViDDwbpSbUJHSt346qsCtUcG1IquIMWeY5RdlAZNRl8fi+SeoVBD2RNJGQmpYCIla42a/OZD4EN7YTPpVlPAl6Oo7+CKfhpnYv6oNQ0bU9A1tEni/+mHSCjz+4suW2cKDSf7Jo8ajdOQv5jbNw2rZ00mIC4NvwYcgQmwFGkPwhyF6Ysp7xIs/b5w3v1y+yo3pnR1By9ESnu4GiUwWo0XGyjG7gS87+NXv9+uWiHn/CL+bDhERHZ+LgNu9nwrzepMsCeJSoetqq155yVK7v4uTNkeeqvvjdqx8goxhXRGNf7PWSBZdt3qZ+y8nge78eUgoFffTbYADZnbwaG6aaecVZEOozbbSsydknTxH0VyLOvTEEUTWvRDSS6jkkiSFiNZLZHO05Hb6FhbXVN2Ju
*/