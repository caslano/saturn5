#ifndef BOOST_CORE_QUICK_EXIT_HPP_INCLUDED
#define BOOST_CORE_QUICK_EXIT_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//  boost/core/quick_exit.hpp
//
//  Copyright 2018 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>
#include <stdlib.h>

#if defined(__MINGW32__) && !defined(__MINGW64_VERSION_MAJOR)

extern "C" _CRTIMP __cdecl __MINGW_NOTHROW  void _exit (int) __MINGW_ATTRIB_NORETURN;

#endif

#if defined(__CYGWIN__) && __cplusplus < 201103L

extern "C" _Noreturn void quick_exit(int);

#endif

namespace boost
{

BOOST_NORETURN void quick_exit( int code ) BOOST_NOEXCEPT
{
#if defined(_MSC_VER) && _MSC_VER < 1900

    ::_exit( code );

#elif defined(__MINGW32__)

    ::_exit( code );

#elif defined(__APPLE__)

    ::_Exit( code );

#else

    ::quick_exit( code );

#endif
}

} // namespace boost

#endif  // #ifndef BOOST_CORE_QUICK_EXIT_HPP_INCLUDED

/* quick_exit.hpp
jg9tabaHNFx5Sebw3G6qDoR42h3ptBij2+hhMCwXY2DLsbQFfQ57fCJBnzsDGtYnzxd2E/6TxXoOM9yMz0FjS3W0KIwtj22XxvMcyzGwmSO5gox5wijeJ8Nk59s40C3YeDGg0WwSfJz70GhEA1Z+j5LNOT9fgvLJp1CDtNHjRIipaeE+ytdvvyR4OcD5TT64X8Bg0I4VgTe/9WLmTKeDjGQvptzH0xxaEea4QahxnTWpiPIpXahAPKjzTYfa9NzmoWzXYPfWXPf2gdypfeauw7xVMY0iacpv4KDrnl0sapfmimeshrPYpPjO3Ei9Duds9oq4ei20r7cHxuOzUunIKvDuVipdfRbP05yNdBx0SVGiTZyDNNQoMQGU9QoPR9FxreFcjw5FxzY7Z4FEl69M0/2URuezZZoIh2tZy9r9+eyrSKaDjtJrBs9tYm1D8Q/XNo5vl9Y2XhvP2zfq+T6kv47TeT5v0t/A6bxu0JRM4Rx+TVDnNxH/pxylx8LTmtivL5ubPNIc7AS3HLhjgOPwW6nsylF6bvq8JsZhVXY+I54TEHV+UazD7gwr3aS/i9O10iFeC6ez0hseB8qp6+qbQC7p3lOcMZ6vX0Jlv/8ovV67uymd6FtS4Rh0ivhtukytGfZSIK4eulfFikmwDziYG4vnCgdzY/FctVq/GbWB6F7QlOxpdrTZ1Ru8aRL7PrRwj9+7j66O9+colStEWJCHboXF8sJbJ8r/yWRsTIePM58Md0eflgrwaSlJpt2wyfK965iYlpJkWiVaK7ynov0jYg3tdrUpj5VPWJiHODUxZyL9l8ZnpNjhzxFt51MkQ6HCmbT3GLf/dZT+M7LdxUSTa2r8PKMalr1DLPvLVMZzt/YObhvo79/m2e31iHl2+zXEPLv9BmGHUYe78gB6S5rXMb9DaVspLddi077PaeertCbqR48VCucTXiD6Bje787pCRd3KhPr/bDXET2G0Y668uahSqxfZ9xR5IJUp53bjQ1sZ2mUMyzD5f45ljBed9ddbYvuBEDw8t1sc4uUCY+hTkk6dhwQTvg8cBWUygZ+XcGW4JR06qvE90yqtwNeq0puBE9COblkqrOCJ2sMu4LnYG49EjBzH0sx4cappWTJhn6mINnXHalsehQ/M5LZu78L36+4kXCWZCHCgs98wFncnWqBD7HeQT6vTYncxZldM4X1+xpJumKT/idP996j+jLxoclmEe5F/keqWi09pMA3qeybjqBz8VqRhVpbsvsb7elVt6Ad9/SXtUjzzv7n+dsxFbX1jX7l3tX7TkN9CYrLGfV9eEfbkOWff8lC2ueThd5eYqnG/tCremT5X7EP3U1lxNHNqcT05JTmkecHoSERL5Tz+SHipHgHfKcBgjihi+s5vsc5vVYS8y6UoovVOie7f8RxXRzLtGqYIspt3DGftNNfe10B+CqKo0c5aujdXWk/vRCD+UICr3b+W1PydXv5dRwb4UBfYxVCAZ7tz9DfyeEFAQ1YCff4Rtht+mNSsNbWs8fOp20V6d6dQrZSm4Bv+KKIlG7Kvq+hVHVPGgYRPT0VUBK1oQN9eh7JFIzNFaKzUuWZUzE9ToLq92niMDAehvFGoy8d5OOvB1PfxDi7W18jzBKA1fUCtrzfh21VzCpN860va59oT6qdc8TAM2BPXWEx9DhqOPxvLQYtU4tzosjnlGKJcvhyHrbHYfshRGhf1cUX7/uzxVHnbI/wWX7V//PRbD1Mhvw+JY/a9YLMsCnWwfGUG3p28K50mV2pWf3r1VpDvY6Lv8SSwYfvi5aiRra1DwKl/02eXZBurYN9a5POKNK9EF0cjrl69plHQPwvZ5vNQdCW7prp3icX1MKE=
*/