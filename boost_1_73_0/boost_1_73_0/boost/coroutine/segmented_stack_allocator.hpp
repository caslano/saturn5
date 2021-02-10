
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>

#if defined(BOOST_USE_SEGMENTED_STACKS)
# if defined(BOOST_WINDOWS)
#  error "segmented stacks are not supported by Windows"
# else
#  include <boost/coroutine/posix/segmented_stack_allocator.hpp>
# endif
#endif

/* segmented_stack_allocator.hpp
GVtTzsWmJfzSU1pSUjV1v/Sv5eTMhML96nq+e+b5Xryw4meJFvTvhgldIVp5fVXeoTpWDcNs32EbQQV9l+OKpN+ozjhut2RT11wo2UuHCvJ0DaQ7ROP2BkyaHPOqfADZpAW+YR+03CxrryNsBPvOriE7m8TzWQBfXX8+sWZUYZOVJm6TJLwC1vbTjr9unS0LmtndpnlwFYQ3QRKaotMGKDfbaheDME7O5p4fJ55Z6qzNkbHx6isq03cU5rPGVr2j2AbrnYvO/Mw9Ty7mwVgjJ+7sy/x6EsR4RdAK1ng/6mpbkazXfyvVQTSZgOtHIfays9kLBXhBPJlduOMJDIb7WyiDN/Vx0K9a/wFQSwMECgAAAAgALWdKUouHbLO6BAAA0gkAADMACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX0ROU19TRVJWRVJTLjNVVAUAAbZIJGCtVW1TnEgQ/j6/omvvi6Zw1lUTo5dLHa4YORG2gNXbiilqFgaZhGU4ZtBYl/vv1wPs6easMh+CtQ709Nt0P/0MvRnBq5/2EGrcwYtP0v0SfHBdG80a+Zmn+nmDJPkG/R8a3uD6A6HG8Gj1LdmGH7L6BludVTLEemfek+QHwt2YJM2/sTG+Scwr
*/