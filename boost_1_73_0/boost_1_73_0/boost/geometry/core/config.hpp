// Boost.Geometry

// Copyright (c) 2019 Barend Gehrels, Amsterdam, the Netherlands.

// Copyright (c) 2018-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_CONFIG_HPP
#define BOOST_GEOMETRY_CORE_CONFIG_HPP

#include <boost/config.hpp>

// NOTE: workaround for VC++ 12 (aka 2013): cannot specify explicit initializer for arrays
#if !defined(BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX) && (!defined(_MSC_VER) || (_MSC_VER >= 1900))
#define BOOST_GEOMETRY_CXX11_ARRAY_UNIFIED_INITIALIZATION
#endif

#if !defined(BOOST_NO_CXX11_HDR_TUPLE) && !defined(BOOST_NO_VARIADIC_TEMPLATES)
#define BOOST_GEOMETRY_CXX11_TUPLE
#endif

// Defining this selects Kramer rule for segment-intersection
// That is default behaviour.
#define BOOST_GEOMETRY_USE_KRAMER_RULE

// Rescaling is turned on, unless NO_ROBUSTNESS is defined
// In future versions of Boost.Geometry, it will be turned off by default
#if ! defined(BOOST_GEOMETRY_NO_ROBUSTNESS)
#define BOOST_GEOMETRY_USE_RESCALING
#endif

#endif // BOOST_GEOMETRY_CORE_CONFIG_HPP

/* config.hpp
OfwigjlyOr7WQ8H/mYJzKlkgKQxMWeDmUlF8CK7jSMY5yd1BMP9dBJmkArUHCJrI9VyNpEAsFxIWiCEKSCL8SYUr4Xi3R1B97BPMRMBxkpNC7ImqFNrMI64dQhy/kdktjhwpyTOSWt5yBemhWb3BxkQCXaKSPThHAgvvRsQuxZpYhLc8DTD8oK9AQJhc65BFwhZZgBbgtA2Bolqa8xzFmckdPzBTok0z986YRBhDjLWMUVSEOV4zKTya0wRUmiXXmYgU9UNGnQ9HA9hhP3mzawf1s/rvYHw1GvXR3yIPXJglSUj+CQMKJN/B+cnoctAnP8mYA58mDuh6lGv6hQl6C+uIG9jtoM++xXkFcRFhtKdgEokwxBgJdFmglYbn7HVsqf1e4RILdBg2YeZUZpd87LnomBzcuUDaYx9qbW0QFwO/t9kdpWVYinWmLXz+eaOfXthWYOMnqYzLPjacX7wajJ3Xk+F0MB38c2ppbstQybtFqBynZtYvI0sVGEYXL5zLN+NT7okwnIeFmrchEH5OEZGpF1LAQFqXDQJFLAgTBAEZJ8DNBHZHvMw4lyAwFiLQs2K52oaextIiOuDAPpMxrkw0XTc+mnCEbirnRO2vrnt7Frh4o/R8MpEqw/iaxWSBKlwXw7tfhOHt5kr3
*/