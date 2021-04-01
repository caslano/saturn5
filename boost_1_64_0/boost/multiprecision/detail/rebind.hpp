///////////////////////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock.
//  Copyright Christopher Kormanyos 2013. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_MP_DETAIL_REBIND_HPP
#define BOOST_MP_DETAIL_REBIND_HPP

namespace boost { namespace multiprecision { namespace backends { namespace detail {
template <class value_type, class my_allocator>
struct rebind
{
#ifndef BOOST_NO_CXX11_ALLOCATOR
   typedef typename std::allocator_traits<my_allocator>::template rebind_alloc<value_type> type;
#else
   typedef typename my_allocator::template rebind<value_type>::other type;
#endif
};
}}}} // namespace boost::multiprecision::backends::detail

#endif // BOOST_MP_DETAIL_REBIND_HPP

/* rebind.hpp
sdnKnNCCmvi0RIVLeT0mxH6yzfyY5ysTJMJqldueJReCBGwJhO+/mBlU6WsA//3ORDYfq9i7Hl6JtIIYQlkRfRI8n9w9BfhZDdyRsNniYRnSV9QA9hcUe82/i7VZ9qrLB+GLDLw23rd5lDamsr2cjL0QrUjQtKwUqu7aJWWNx0HT8uBtJYFDEoNghk8ncNmAcUM0gZ7bNA+tC0J33ZolPmUSAbqsaQR6/kixcXj9g3gWcKkalXzdg/07l0be/cddAcJIWa07obto0LBGT9AKBabUHrHQ40xMcQG5UhZM/QKEn2bvsgQGqwqguhmxMflygrJMaTP3UJXrJ3JDHKyRvTQhE3UaeyxwQhBYzytPfOmpMK94KmIMTGw16eP3nCRfK9hLok1WWnZdlQlXcFhOiOZHdpS8rwW/m6bnwSnE8cjrsc0SB5ZiWPG3vdHtkMGi9mzuctXRBi9MciRVZvyZ15B7h86TLbWj/poTlyuq7csxxsRlYC8sT3B7elRUyhubiqGdp74Zc/oXg/Zwse9mew5ke7iT9phUFA8UpiozCUWXARkwfmaLEt3hMA==
*/