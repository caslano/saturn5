//  (C) Copyright Brian Kuhl 2016.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Check this is a recent EDG based compiler, otherwise we don't support it here:


#ifndef __EDG_VERSION__
#     error "Unknown Diab compiler version - please run the configure tests and report the results"
#endif

#include "boost/config/compiler/common_edg.hpp"

#define BOOST_NO_TWO_PHASE_NAME_LOOKUP
#define BOOST_BUGGY_INTEGRAL_CONSTANT_EXPRESSIONS

#define BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE
#define BOOST_LOG_NO_MEMBER_TEMPLATE_FRIENDS
#define BOOST_REGEX_NO_EXTERNAL_TEMPLATES

#define BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#define BOOST_NO_CXX11_HDR_CODECVT
#define BOOST_NO_CXX11_NUMERIC_LIMITS 

#define BOOST_COMPILER "Wind River Diab " BOOST_STRINGIZE(__VERSION_NUMBER__)

/* diab.hpp
0ZD2EaQmQL+a8L9mxf+pet6FzMeQhFeoHSnd8akd6WcvWyfp/VnyIXyrACgkDjvkAoeEHNUacgBd4mA2IEmq/wUwwRvgUvgKsXUw+kQUF+bZMfHxYZsrormRjE8d6nMQ1rNSJVFZYfMrxP6JvDfAZNRfEoN19BUea+ZRyLwH6Xev0Fg7TBFCO4ozHCn3+2iNyGX+mzFXsrA4GxMpv06f0JA7H7+S/u5xz7OAyfXYRYxPCT3iDsmG5SqlRF1o17aoB5SEuMMR1zsdMbESCPwC6Jk2gbmRLNaAvRW9ujYz/jttln9B4e9Pc/nXaWuX34ilZ3E3xb45V0vk/ctskMfMsB6HwjMc1pPTYH2EhSUYEBXFyTPD+tAM6wsozH+VwbK9aoX1BRauT8GahV6Pvcp1xjdD5tuQHnqVjI+kdkGX5v0Lufw7ufyQXJ4hl5fJ5W243AbDL2DN0QdvwHj806tpruGOlEXL8P/Cc9mi9AvhVce7LO7XDHLZg6k2PA8Z4Wcqcv8sPUfiEbRL5AhvbOREJn9h9Il0/lHcOA4FptN8kM4O5WfWg8MD84tO4Lg4JG0QiS44KjcpG2SaU5u0DSrNOZr0TY4Q7kGtOFf0SxFZUyKqpkUA1c0qk+/+mZleFFR0P9wQL8wqq9z+MxOf+CQUXvgZ21Of/tm0/SrLtR37gK4KCF5cxtMBymnMFitQOGNqywIoBM5w+d8ZK+wT
*/