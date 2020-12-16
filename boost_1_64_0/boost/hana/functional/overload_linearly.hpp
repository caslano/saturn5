/*!
@file
Defines `boost::hana::overload_linearly`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_OVERLOAD_LINEARLY_HPP
#define BOOST_HANA_FUNCTIONAL_OVERLOAD_LINEARLY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>

#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! Call the first function that produces a valid call expression.
    //!
    //! Given functions `f1, ..., fn`, `overload_linearly(f1, ..., fn)` is
    //! a new function that calls the first `fk` producing a valid call
    //! expression with the given arguments. Specifically,
    //! @code
    //!     overload_linearly(f1, ..., fn)(args...) == fk(args...)
    //! @endcode
    //!
    //! where `fk` is the _first_ function such that `fk(args...)` is a valid
    //! expression.
    //!
    //!
    //! Example
    //! -------
    //! @include example/functional/overload_linearly.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto overload_linearly = [](auto&& f1, auto&& f2, ..., auto&& fn) {
        return [perfect-capture](auto&& ...x) -> decltype(auto) {
            return forwarded(fk)(forwarded(x)...);
        };
    };
#else
    template <typename F, typename G>
    struct overload_linearly_t {
        F f;
        G g;

    private:
        template <typename ...Args, typename =
            decltype(std::declval<F const&>()(std::declval<Args>()...))>
        constexpr F const& which(int) const& { return f; }

        template <typename ...Args, typename =
            decltype(std::declval<F&>()(std::declval<Args>()...))>
        constexpr F& which(int) & { return f; }

        template <typename ...Args, typename =
            decltype(std::declval<F&&>()(std::declval<Args>()...))>
        constexpr F which(int) && { return static_cast<F&&>(f); }

        template <typename ...Args>
        constexpr G const& which(long) const& { return g; }

        template <typename ...Args>
        constexpr G& which(long) & { return g; }

        template <typename ...Args>
        constexpr G which(long) && { return static_cast<G&&>(g); }

    public:
        template <typename ...Args>
        constexpr decltype(auto) operator()(Args&& ...args) const&
        { return which<Args...>(int{})(static_cast<Args&&>(args)...); }

        template <typename ...Args>
        constexpr decltype(auto) operator()(Args&& ...args) &
        { return which<Args...>(int{})(static_cast<Args&&>(args)...); }

        template <typename ...Args>
        constexpr decltype(auto) operator()(Args&& ...args) &&
        { return which<Args...>(int{})(static_cast<Args&&>(args)...); }
    };

    struct make_overload_linearly_t {
        template <typename F, typename G>
        constexpr overload_linearly_t<
            typename detail::decay<F>::type,
            typename detail::decay<G>::type
        > operator()(F&& f, G&& g) const {
            return {static_cast<F&&>(f), static_cast<G&&>(g)};
        }

        template <typename F, typename G, typename ...H>
        constexpr decltype(auto) operator()(F&& f, G&& g, H&& ...h) const {
            return (*this)(static_cast<F&&>(f),
                    (*this)(static_cast<G&&>(g), static_cast<H&&>(h)...));
        }

        template <typename F>
        constexpr typename detail::decay<F>::type operator()(F&& f) const {
            return static_cast<F&&>(f);
        }
    };

    constexpr make_overload_linearly_t overload_linearly{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_OVERLOAD_LINEARLY_HPP

/* overload_linearly.hpp
7EfYRxVcNWXzI0X88ZGI4wF3ixiJXyGVbTqobO00cV7tbiv5hnAe+GJPW6q/Z1sp9eMy8nkq2++Ternfx1Lysc9HTeU8dbZnfoW9wCV8+p1YfUdHXw1xDjyQkSliuuM2+tUPDcQGFsjFemKwoqbK2hxX2fgm3G9s2D96op/GCru9tpg6RIuBNdpNJhb99EaiK5dH4OgzG/HzE9iQgn+I5dOohXrk04T7srOIP+bhfM7L/I5U1tRO4raboLot4ZJ7krIJN7WtbFqqxudXYjCjg0at4FWlbrur8UC4vIVkl4XaOE8qvZDKjptL5lxchhmUOa8Wv1uUJTwR3aJFyo6F35aHArYD1NArFsPTBBFX4O4eX14kxQOFWJJTwP+kyp4jX+8kS84X/DlGkmDZB1vJhzE1l6P0eqzamHxUvXT9hX+3igS/WpX9xu1SHH9iekPsGWZhVarqbjLHX8x6yR2EP2c7+yNO4GVBlXXAtKzLAXXMjPMZV/tiU7WbskKpbXc0tY9Qt8owg6YjGL9NluKXVwNbsjD6S6ZIyrEb/WaLy3WcMCcbiyTvFSGcOmqsCsUI3LmoGs+80Q/aK5t6XBL074M/lss1NpcQIWGSLwdjdeWYOJu/ZPyei2nrdvgTD4hBR2Ol7Dj1LPuqxvn7+O9DVOP4FO4PLq9NmFXWuNBDCiLfFTW0KE7YmGZiX7mDGNiykC7iwJn5wEbzEaFUaSyRhVy9oSi4+dFpPENsJd9A+ntNeyv6rYgTGjJ+mcr67ddcHmKJ/sDFNa+OUjPZPVGs2PFNxcXEgrsMBt9S8W9ECQTgY1zooHnrUl5LxeWUsfrLUjZHlqJ0y7a1wBd8N4cRcn8xkaRskkC+1F2Sh/ntp+z2NQbxm4y94CW6Jifo73VJFYn3rSnmetEmrOel6M/U7UjfpnD+rUkWXZiTwHAG9lsL0eUyY/3dUFnZQqpx5Bj3R7JqTLIUNumPyl4fJy4b3Dn/UETc9xFf2KFskJ+T5iMf/hzW5FpOhgt3xCq5p7LfY9VGdKSGfRn+2CtELpoydId+ambiLgsEt8BeDVa1n17c56bKrlypGvE31Mbx/WLwiUGc9knEsR8lSwj+sD6/RWzDgRfDrji0Uynb+UpdhOQG2qHPYSPxc+e8H6rO9EoVg7tblH1uhX8tVJwHfyE+gzbSPlzZ+2mcz4sF3o9RjYK31e6XkwIz0TGHASK2Yn9kiFXoaHFpAYNVmwQqgu3Jmsx9TzU297CUfDPEee5WIc464H8ujH7f3VjyVTHX+OGJ+UqNMPSXJY/Vc/8cknl0PdH1ZkWkjVeqWvZ6JjCyfhv6OPfbewydoHXwm4g948z+TWJ/JCjb6aKyU9G0/EuJaWcO3waPuS8rcT4/xz5PVKocHRw7VtmRF+jvJoFmj9Gf8+GPNdfUpvyW9L6hKjuVW6JZxSh1cyL+iFTJ5zxOHWwSTryM0Zh0S6muY5Ta4sl5VV8p10fc5we53+zVkOV6lW1DVYsfq9SCvGIfPkY9OpCuvrWk2mq6bwgQiKzLeV9VbcxAYQmi7kA7Zd2pdrWgmJaGJAzjsT7YCQskeC7abUe71oDcWCd9LNVGnf0CXZH00FqBk/WFONxdvVxhhT5eFXvaXmIkEoaZSvinzFGtJlPM0oAVIj6xXXRzmjqgP+O/x2z+A+t+S04jzS9n3SsEX1FFw/7zPOffVzFYN0xttH2rslQa92yqGg3iVXdiC4EBTHKOOvSXVFd74j3JIt5wx1b9DROXc+NVNgU9rHs1kXzsw/3LvTqBjfjpqbKnmcaJriIJmcj6yyVZvBYK4RcjRGU3dWGfk4Ari2FmqEBUGRGXHks8YK4Q9fsJpAaKvek=
*/