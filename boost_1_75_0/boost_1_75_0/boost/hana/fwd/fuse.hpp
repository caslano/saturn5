/*!
@file
Forward declares `boost::hana::fuse`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FUSE_HPP
#define BOOST_HANA_FWD_FUSE_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Transform a function taking multiple arguments into a function that
    //! can be called with a compile-time `Foldable`.
    //! @ingroup group-Foldable
    //!
    //!
    //! This function is provided for convenience as a different way of
    //! calling `unpack`. Specifically, `fuse(f)` is a function such that
    //! @code
    //!     fuse(f)(foldable) == unpack(foldable, f)
    //!                       == f(x...)
    //! @endcode
    //! where `x...` are the elements in the foldable. This function is
    //! useful when one wants to create a function that accepts a foldable
    //! which is not known yet.
    //!
    //! @note
    //! This function is not tag-dispatched; customize `unpack` instead.
    //!
    //!
    //! Example
    //! -------
    //! @include example/fuse.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto fuse = [](auto&& f) {
        return [perfect-capture](auto&& xs) -> decltype(auto) {
            return unpack(forwarded(xs), forwarded(f));
        };
    };
#else
    struct fuse_t {
        template <typename F>
        constexpr auto operator()(F&& f) const;
    };

    constexpr fuse_t fuse{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FUSE_HPP

/* fuse.hpp
/2/ylzJjZqozbVZ6xuw5mXOzsnMeyc1zuefNX7DwUV4fM3RYbNzw++NHPPBgwshRoxPHjB2XNH7CxORJD/1/S/f/8r//v+vH/xmKQb6SYkj6ogCBAH9bFH97WCL+ydB+V/zNwT8OjbHoNUGRCJApBUXyaxwmxwuKVMBk5KcDUgHpgExADsAFiEf9AqQN9wstno9uwvhbAeOEbCFNcAnzhRQhV3AKk4WRQoYwE/lsIU+smwwORwkIXYThKE8R5qLdfNTlCnMYrjwhFbkRQhZyLtRn4t9Y1Gfjap6gRm8la9d6C0GYgRGzkBq3tlyfWivrv0WqGAZIASwBvAL4FHAUcAnQ7UOpQvMhj/vpzPlRXZpwHAG+agDF53sANcjXA2jPXEINPhEUoZ/w+lJAGPKRn/D6YkAU8kaxfjcgGvlEsb4MkIx8KoC9cw7IRH6RWL8XUIj8KgB7nx+wBvkNYv0+mhfkt4r49xP9yB8Q6+mrL0eQrxbx0/d1a5CvF+u/Ivq3gf5tvP/XRD/ykdt4PX3zNAp54zbe/xuiH/lEsf4g0Y98unh9GJCD/CIRHx2FX4j8WrH+EGA98pvFa/rIzFbky8Xrf9OYyFeJ430LqEb+tIjvB8AFqtvO29PJi6HIh2/n9XSIdgTySrH+KOkD8rHbOT46hjsB+cli/QlAKvIu8fokYBHyy0V8dD7gGuTXi9d0vP1G5LeK7atJ3shP
*/