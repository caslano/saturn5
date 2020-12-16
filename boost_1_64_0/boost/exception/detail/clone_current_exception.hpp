//Copyright (c) 2006-2013 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_81522C0EB56511DFAB613DB0DFD72085
#define BOOST_EXCEPTION_81522C0EB56511DFAB613DB0DFD72085

#ifndef BOOST_EXCEPTION_ENABLE_WARNINGS
#if __GNUC__*100+__GNUC_MINOR__>301
#pragma GCC system_header
#endif
#ifdef __clang__
#pragma clang system_header
#endif
#ifdef _MSC_VER
#pragma warning(push,1)
#endif
#endif

#ifdef BOOST_NO_EXCEPTIONS
#    error This header requires exception handling to be enabled.
#endif

namespace
boost
    {
    namespace
    exception_detail
        {
        class clone_base;

#ifdef BOOST_ENABLE_NON_INTRUSIVE_EXCEPTION_PTR
        int clone_current_exception_non_intrusive( clone_base const * & cloned );
#endif

        namespace
        clone_current_exception_result
            {
            int const success=0;
            int const bad_alloc=1;
            int const bad_exception=2;
            int const not_supported=3;
            }

        inline
        int
        clone_current_exception( clone_base const * & cloned )
            {
#ifdef BOOST_ENABLE_NON_INTRUSIVE_EXCEPTION_PTR
            return clone_current_exception_non_intrusive(cloned);
#else
            return clone_current_exception_result::not_supported;
#endif
            }
        }
    }

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif

/* clone_current_exception.hpp
M760a7S+3N/NnnxDSL4j/UC+e9OrGixfP5v0jjYX9F5xAb3TGkFv96n26P2W6BX8APr5XFrD6Y05NUL7rU0Obb/Cto1uvw+72pNvbpyQ749VIN97gxsu33Sb9P4UK+gVfwr0rm8EPadNer8ies8cBXo/DWo4vdVJ9uj1JnrLU0E/SxtBr2tSBH2ZcmqovnzaptH6srmLPfn6xwj5LsX6fPzMhsuXYZPeX5sJesc/AnpnNYLeoc726LUiel/WAL1XBjac3uU26V3rEfR6Ib3L6qQXcv/rFKIS4qwY+Z0YpJ4nPMmA+idE/Stg1hgRqKzz2pCV/m8aSb+A6B/G1enez+qmHzle1NediBPN58SHH8vkRxp5x3PYxCJulHxuFGarMFqw9RqMMcYZNtiKWD8TOzWuft5tSqMXrsYeqq6bESv9dzo2jv4Sot+tPVREjwbQn9hI+p2I/uG4KpDfqJt+ZP041OEk6sdat2Dr4HFolngbbEWsn6EdGlc/O6MEI0WJUD83V9XNiJX+jvaNo3+iiaDv7gL0mzaA/tBG0s8n+vmno/yV9ae/I7Fx9IcR/bnvgCI0tUE/sn72SzyJ+lnoEmw91Aeq5cZP62YrYv2sb9e4+okiRtrDMGBUflI3I1b6HRtJ/x6noL8JrUlXN4D++raNo/+SQ9A/LRbl/7j+9Ds2kn4c0b8pBuVvAP31CY2j//saL9J3xKD8H9WffsdG0o8i+eOhGo3EHnVfiw6Rv03j6K8h+Y+C6hnrutdNP/L40LLNSRwf1v4s2PoKpw2nDbYir/9aN65+TvwkGHnjK6ifouS6GQlZ/7ZqHP3fE/1z4bAOzo7rT/83jaQ/jOgfbQL0i2zQr2X92/Ik6sczJwRbR45As3x4at1sRV7/tWxc/bz7o2BkXTzUT44NRkLWv97G0e9E9Lvj+PF21/rTn9hI+qt+EPRXdUf5G0D/nfjG0Z9E9H97uBLkT6qbfmT9HBN/EvVz7XHB1l7QCCPDBluR138tGlc/ycRIOgwDRlmXuhkJWf82kv7OY4L+QbQepDWA/o7mjaP/yfeC/igXyt+5/vSHNpJ+X6K/wQn00xpAf0dc4+i/9J2gn4T0y06pF/00IX+c9jQivURCVr6tyspHny5hm+GAJz2lG0wHdnmZjKt8+iBnwoa9XxPy/nVsBP66VFXq/F3xWR38bWxR9Uvw92NMBP5u62qqvxeqa+cPzJ8nhT9yC5hCXJV5KQg2asjM/QmOkjin0fpHYATDgYPyTIY0eKtpKt0n3H1AfE2Irk9IrqyI/iQfNiMnlG/BtIYe0ht+rjTFmUlBfe5E/kC7YJTPKItGf6CZ6A/UTNx/+7YSgw5lor6jv6+4ukJeDktg107dgN8Yoow2caZ326OhXONe7o/8noWzmXIaPxIX7j0L+uEPCTabL3t3kfx3XvhItex6XniWMbUFfFuvDg6iqis+7uWrg1x1BX+vrKle2NThCDRnf2yEN9pAnZqD/UxoKrjIltxkUjB5jMVIr52AXz95fOPrL+xtfUcb/Y5ZstEebFDda+LF7FkEiUXT4JmEw28DF793OxzVf4f/4dtGR73kDgcBcIVPeAKevx5TiZNEYuElEGBv0fvEZw57tBX0095ieqi5A0picAc3Xlz+u1WoJZAcWMnh6POqr6M4rg8xrSPpgtalQOvPRgitgRqtIYrWGUjr9W+stBJRwC7gLqSRO+ES5M7/WpFbROQmA7kEC7kij5nen+IkveejgN6VIfQegeTqJ3+W9PAmC9FcRjR/PKJoNhc045dup2j/MWgJ1el6zXTHKrrnI93AUSvdVKQ7mOnu85G+4sc+H11xHfQhANED5hleJoPA3zQ=
*/