
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_FIXEDSIZE_STACK_H
#define BOOST_FIBERS_FIXEDSIZE_STACK_H

#include <boost/config.hpp>
#include <boost/context/fixedsize_stack.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

using fixedsize_stack = boost::context::fixedsize_stack;
#if !defined(BOOST_USE_SEGMENTED_STACKS)
using   default_stack = boost::context::default_stack;
#endif

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_FIXEDSIZE_STACK_H

/* fixedsize_stack.hpp
76PmnHunzqhNmHpUZff8s/lg31kVdA3s0DH8hkqNMDp95e82XIF66+34OjbyNHYCE+GeSXVW9v3GPEcjT3Eb/nQIiFsq/lx6wPDU+pes/SeeUMJQrTYy7kfwSRY0VmTf2DMFdwuLct7yeN1bvBnGuvK6oAcWjRn3Ay+Vx2dOe19B7a/Ls/gX5iODttgnPLgtHKdVzQkUvQozgWJhpJJMHdVjEHSJdK0u0ALsPRSpBy2xKE2lBDfhdam5gVkQJvueeVQt6qx+R5fQ2YKBuT52wgrbiWsxM6D3/nE9A4boGe5QZrejz3L36wTDV7p26bO2PfkBWKmJ1c9p4NtNDNlDfAtYj1C13P3A+y/zKtUBUSQpctZKxP9CZgTHr/d+PeNeH/Rd+/ekGtRg0RXxxLVuQZU2iJxsDriT4UKqscHVzdcfLB3JAkAs5GChoq1WnRU3jH8WnJfO2Hs3gTqUFd9MTa0s2mGb6agW3lrCm9YBcvx8Z28NSVYiv+XJWUcggtJ8kM7pwoPzh5GXKFPbkadg44FIjUAcSzawQ85wChrJ9b/cJPIlD06AiFJi0Q==
*/