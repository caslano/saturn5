/*!
@file
Defines `boost::hana::compose`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_COMPOSE_HPP
#define BOOST_HANA_FUNCTIONAL_COMPOSE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/create.hpp>
#include <boost/hana/detail/variadic/foldl1.hpp>

#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! Return the composition of two functions or more.
    //!
    //! `compose` is defined inductively. When given more than two functions,
    //! `compose(f, g, h...)` is equivalent to `compose(f, compose(g, h...))`.
    //! When given two functions, `compose(f, g)` is a function such that
    //! @code
    //!     compose(f, g)(x, y...) == f(g(x), y...)
    //! @endcode
    //!
    //! If you need composition of the form `f(g(x, y...))`, use `demux` instead.
    //!
    //! @note
    //! `compose` is an associative operation; `compose(f, compose(g, h))`
    //! is equivalent to `compose(compose(f, g), h)`.
    //!
    //! @internal
    //! ### Proof of associativity
    //!
    //! @code
    //!     compose(f, compose(g, h))(x, xs...) == f(compose(g, h)(x), xs...)
    //!                                         == f(g(h(x)), xs...)
    //!
    //!     compose(compose(f, g), h)(x, xs...) == compose(f, g)(h(x), xs...)
    //!                                         == f(g(h(x)), xs...)
    //! @endcode
    //! @endinternal
    //!
    //! ### Example
    //! @include example/functional/compose.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto compose = [](auto&& f1, auto&& f2, ..., auto&& fn) {
        return [perfect-capture](auto&& x, auto&& ...xs) -> decltype(auto) {
            return forwarded(f1)(
                    forwarded(f2)(
                     ...
                      forwarded(fn)(forwarded(x))
                    ),
                    forwarded(xs)...
                );
        }
    };
#else
    template <typename F, typename G>
    struct _compose {
        F f; G g;

        template <typename X, typename ...Xs>
        constexpr decltype(auto) operator()(X&& x, Xs&& ...xs) const& {
            return f(
                g(static_cast<X&&>(x)),
                static_cast<Xs&&>(xs)...
            );
        }

        template <typename X, typename ...Xs>
        constexpr decltype(auto) operator()(X&& x, Xs&& ...xs) & {
            return f(
                g(static_cast<X&&>(x)),
                static_cast<Xs&&>(xs)...
            );
        }

        template <typename X, typename ...Xs>
        constexpr decltype(auto) operator()(X&& x, Xs&& ...xs) && {
            return std::move(f)(
                std::move(g)(static_cast<X&&>(x)),
                static_cast<Xs&&>(xs)...
            );
        }
    };

    struct _make_compose {
        template <typename F, typename G, typename ...H>
        constexpr decltype(auto) operator()(F&& f, G&& g, H&& ...h) const {
            return detail::variadic::foldl1(detail::create<_compose>{},
                static_cast<F&&>(f),
                static_cast<G&&>(g),
                static_cast<H&&>(h)...
            );
        }
    };

    constexpr _make_compose compose{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_COMPOSE_HPP

/* compose.hpp
GjTTtkZ72MzolDbToJk2M9pD1qI9ZC36IeLZhCE9O7tK4+6V9bZ5TpBh81KvK0ffTwKnkqk2HjKlaaZMaZopP/dppvxomik/mmbKj0Ez5UfTTPnRNFN+kmmm/GiaKT+aZsqPppnyY9BM+dE0019rmilTmmbKlEEzZUrTTH+taaacaZopZwbNlDNNM+VM00w5g/Zv+MDkqU/CX/jYwkEPigvbesiUppkypWmmTCXTTPutaWZfNc3sK7SHsN++9QJf7t9IfKfqZ5kgr7Vk73WDrk/xLWVzj4Muo6/6Sg5mYwKbtnvGxnjND+M8dCcupe4YNFN34jx0J85Dd+I8dCfuIfhmroETjSX2GOw1T6pqyEfKPcSD793ZFU6k2uFb4a/Leu0mv/qvlo+J/XP5LV7lU8783TWUhymfvBua+ww5SHHfX27x9tCl3h66pGmmLmmaqUvJtCIlFG1p/WRaMU0badBMndM0U+c0zdQ5aA+xzuTTOfebEr4lupQyE/InXZO0I+1IO/6njowF+O1IkBUEgJygDCgIokEk6AkmgClgEpgDloCdGrvAeZCxILkDkA3kBq3BRLAcvAJmgLngZEHuAfvAGXAOnAU5CtEWkAvkByVBs0LUAzqA3mACmAQWgClgKdgJ9oLT4Egh6gQFCtMWUBhkAhlA/sKKXhK0BT3AK2AyWAVmgblgMdgPDoHvQUA++AJ+qWlLow2WdIuzZPU5S4o96ciBtpYcOGLLk8NsyXSXtp5mT9IWR35pbUvhON5FyWHLjOqWBMVbMnUfOYWrjuTe5Mj+nI7vXeEw0Ar0Br1AFGgH2oLOoCOYAOaAVWAcmAXmgSXgS7Ab7AI7wJ586pvhx0DDTfx2ke1IjgaOTKhsy+9PWPLyXEfWE5dUmOXI7Em2ODcdOfYr10IdqVQQftez5MZeR15YRx/pe7mWjkwfwPs/0x3ZXR//xd6l4hG2jMF5bEi05c1AR/yhfXzSlhHPW9J7ji1r4NHkfnyfa6ktx1s78v1qeHGF5xJw/3SEsXrVll37bMntZ8upcPjGQsz0H9gXdciRJS9ZEjPGkul1bPnVsqXjLkuu8qwOSxzZsodxKGrLwTu25CpM+SdtebSyJcOetmTz3+l7G9YlTluyjwAo935L9m+j7DzaW8SSnCMsWVzRkZq3HLl50JaWVR25NsqWjN8inx/bEkO7023hfZgPKVvDlvgf6c8uR35eZ8th+nXroiXtj9tyczrf9rtkSfpstix/D1lfbku9PrZceMaRu79b0je/Ldtz2rJ5lCMLJqIH88FKxvyYLc/NsmRSV0sm7nakRA1+X+qsLQOO862kVxxpsZfgjr7O57lvXnTko+yOHHqOWH+zJQVfh6e2LRnq2fwmMWOTi7G4BI8b2PJad0fq+TtyspIjz39vS99WtsxfQd+IBe7k4C3T1sQSXBv8MzrA+CesceSnu47kQpa33BKpXdWWOpw3XKftc9lT/RT9K2XJttLUfxue7aDcXUsKfIZcjEDmHEdejoXn8x3JHoOuMlbhmx05u1FkE6gRysy1pyNZuiEz8Y6Ma+pIRCaeM9SSjp0dyZMLPWxtyWfpLHm1ryXHjjqyrhP9+JpvKQU50oZIYVqSLSU+dyRdPUe+nGVLa/p8YrQtHwzkOUmOdOxuy+3y/P4uY3cReT3yMWuIk9nDMRrbEkY8VdaWtcjAtdeYk+10ZHR7S45+78i8quwD5jndsqBrlxnn5ZyR74t54OcgdLO6LWeRpVOd4fNN5I3+3ypuycLxlsQ+5sgnFbBVjP+iDfBygi32YkuWUccukjHfXuC9BPYB9T1G+YqWrEe2qr9vSeBW/m6JLjN+X33Pd4cacv8NRwI=
*/