#ifndef BOOST_CURRENT_FUNCTION_HPP_INCLUDED
#define BOOST_CURRENT_FUNCTION_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  boost/current_function.hpp - BOOST_CURRENT_FUNCTION
//
//  Copyright 2002-2018 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  http://www.boost.org/libs/assert
//

namespace boost
{

namespace detail
{

inline void current_function_helper()
{

#if defined( BOOST_DISABLE_CURRENT_FUNCTION )

# define BOOST_CURRENT_FUNCTION "(unknown)"

#elif defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__) || defined(__clang__)

# define BOOST_CURRENT_FUNCTION __PRETTY_FUNCTION__

#elif defined(__DMC__) && (__DMC__ >= 0x810)

# define BOOST_CURRENT_FUNCTION __PRETTY_FUNCTION__

#elif defined(__FUNCSIG__)

# define BOOST_CURRENT_FUNCTION __FUNCSIG__

#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))

# define BOOST_CURRENT_FUNCTION __FUNCTION__

#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)

# define BOOST_CURRENT_FUNCTION __FUNC__

#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)

# define BOOST_CURRENT_FUNCTION __func__

#elif defined(__cplusplus) && (__cplusplus >= 201103)

# define BOOST_CURRENT_FUNCTION __func__

#else

# define BOOST_CURRENT_FUNCTION "(unknown)"

#endif

}

} // namespace detail

} // namespace boost

#endif // #ifndef BOOST_CURRENT_FUNCTION_HPP_INCLUDED

/* current_function.hpp
EwT3z7iLUMZQZU75IeQP3FEKt/KaEUqOpvf+Hx0DzfSBa47sJx0x+P5IK1WP+a383PmQHHH0E2BPZfwhMxwapGYx1iYRBjTbrBrO3HJLVsQ+AoLzT9Uh5c4E8RrQs/CrPDDZjxMyH5nqHsW58rA3UCdl1EcEr8vmgPIOh6V0oHmEuJJofW7o8LtHY5dWmfkgyJVOvjpBcRQihkWEv7zkmMkNoVMRlP+C2m4YSV2d155PFq+9K85h2xYrVcc0pLxkeRa1VcU2ZlyRDws7Yu/wG01nbTgPxalis0kPtnSyLU0sBupq1r7vby3QQ1qPLIcFndbn2Y0dBTCXmXWdQZPtz8+5R5tcN1p4c294Q0cveUXtz9m3anlLLIqi+mBkXnJZu5eR4CT2Fr6mXFmBEOWsVdqGYAEzTztuP9W9HjMA1jntebc4AMealtKRil1xHg29MUnRVUbfWC0PbCc6PAcHDu6+c+PNHTmkLcgrEpayv7h1Ib7/RnzhplZM9c/WAMmlIcpmn+u0UaGVJFd85d2TX5c5Vs0y1ToczvdueMmtKrV/aqack8vdgDWM05OZUU70Rw8KnsCoL4lMaqPv2tTytygm6IDxEmVYqm5yWggxJzIWRnsqveSu2VxA4N8iMmxonlmu1y29PQ77F61AkbGZ/o2ImQr/0wUewt6pbGBrDH6W8aQIHN4UuSEMCANpOkSb5GK+lWmmqzfkkv/I
*/