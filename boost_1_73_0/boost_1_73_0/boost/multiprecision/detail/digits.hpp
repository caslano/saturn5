///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_DIGITS_HPP
#define BOOST_MP_DIGITS_HPP

namespace boost { namespace multiprecision { namespace detail {

inline unsigned long digits10_2_2(unsigned long d10)
{
   return (d10 * 1000uL) / 301uL + ((d10 * 1000uL) % 301 ? 2u : 1u);
}

inline unsigned long digits2_2_10(unsigned long d2)
{
   return (d2 * 301uL) / 1000uL;
}

}}} // namespace boost::multiprecision::detail

#endif

/* digits.hpp
JruuoxZ4GgvjHVgEF27/g8hdk4wrEZ4GBUfH40pKJAGmG2L+pMuATFDntGEd0tYtPw0s0nlR8ZgSRLp0U5WWaEP2jGOusRw2LuieYjrbMCCIIoF4v3qajBybMXKqGqH3EkYwrxR+FAlTAeryc5N5epPih6zFQSCt4WSGwK+vsQODkkHARpjdMzUJZhvNsUcyOhb1MQxc+5eZEBefo1FHtXxOMcHIsybsjEZV3rqFNGpS2qJRE2XTbScaRq2vsTA/bdFtk+Zo3JPiva1SLfLIs6ahP98KhcFnr0BZE2WKgnUYp7w7xmyT8h0sujD64sVLXXBXmIjorGJkzAVG77wAOyH80f3oYBBDHRaHLxPvHIoL8K3qy7ffcvz+J8Vijd9flN87tT+3a/9arT2v9755XDt9XDn5saw9pSf1ymP56PTTWvXpTeUlCqtIayY/5WVbPPn46fvVmxr8Mxze2Js3iszAZZ4piyEv3oQMBSk+vOBXEBvl/J8pNqTz7tDE4DpUM5hInEDxpqfh/L6KU9rRPEEyIDxZf8qOL8CwHbsy98RIt/8EBZLbaUz3gl5E3nuEliomzeMRfnVRVQeoXIDctEwMR9UO2JQKnokMJfXD9ICY00+VKWTYXY0r5qk1M/rx1ABm//DopNmd6Qjn
*/