/*!
@file
Defines `boost::hana::flip`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_FLIP_HPP
#define BOOST_HANA_FUNCTIONAL_FLIP_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/create.hpp>

#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! Invoke a function with its two first arguments reversed.
    //!
    //! Specifically, `flip(f)` is a function such that
    //! @code
    //!     flip(f)(x, y, z...) == f(y, x, z...)
    //! @endcode
    //!
    //! ### Example
    //! @include example/functional/flip.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto flip = [](auto&& f) {
        return [perfect-capture](auto&& x, auto&& y, auto&& ...z) -> decltype(auto) {
            return forwarded(f)(forwarded(y), forwarded(x), forwarded(z)...);
        };
    };
#else
    template <typename F>
    struct flip_t {
        F f;

        template <typename X, typename Y, typename ...Z>
        constexpr decltype(auto) operator()(X&& x, Y&& y, Z&& ...z) const& {
            return f(
                static_cast<Y&&>(y),
                static_cast<X&&>(x),
                static_cast<Z&&>(z)...
            );
        }

        template <typename X, typename Y, typename ...Z>
        constexpr decltype(auto) operator()(X&& x, Y&& y, Z&& ...z) & {
            return f(
                static_cast<Y&&>(y),
                static_cast<X&&>(x),
                static_cast<Z&&>(z)...
            );
        }

        template <typename X, typename Y, typename ...Z>
        constexpr decltype(auto) operator()(X&& x, Y&& y, Z&& ...z) && {
            return std::move(f)(
                static_cast<Y&&>(y),
                static_cast<X&&>(x),
                static_cast<Z&&>(z)...
            );
        }
    };

    constexpr detail::create<flip_t> flip{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_FLIP_HPP

/* flip.hpp
gw4S35Br7FCeeIi2vg9v5hG/j5gHb/DvjX5DXnoSJ0cSfxPblOL+nPArO3OcCv3JzzO3yMHLoY+kJ75gjDPCx+bMCZ47yrOw+RmgbWSMTuIjEivgVysxt5mCnuJTWjDvyrmA2Lsqdgr9qImvzosfjyoJv17D7zNG5z4kRs6MLiRSphF5neyM++PEt8jmR9jkJqOJx15lbk7ME0u5idnQp0Dk5SI5Tnzi4lvka89ik9DBSsSrC5lPD6dvrc9YMqAj8Sf3zNxGvE1+oo+QQ6bMLfR/G7Hg78WZy+6gT2vw3fjFyP7MY/Ij88hRow745oLYcdqe+Bu2ug12oSYywvPqMG4l3iSuyYXfRGaqhJA7DyDGQ65kHXPU9cToyNnRhcgaerp0OXEVwtjpS8ZpCP4D+bpxhr6QG7HbEsOtgMfx5JGIS0Z3x54wN8n5OvEKOf/xxIn9ytiS+Vs3ziCfiG/pVZmYLZF8QQB2fyxrKa9gIzaQE69Bnq0QsWMZcm4NyPEgo9HTsJWdmZdkozw68kkXfM5R4q585F4ukFMayFz7I+Y/o5jTPU3OOIhYsCjySVt34CP2+DO3OYI+U+5R6o+jrp8iyBNlIa/SjFzX09i8PW6+jRxVEWJR4tgGU4kp1mBf0a/Q5cRO7ZCp41zfzHs+rA+VLcw8n5xY4frEaNRTaRNxbWlsJbaw/1DsTkbyCh/gM8cS5+ch50O5n/i7JGVj9pFraIV9aEfePgk7OhF5w8anH4L9SMfcK5I5J7YqaChzO559mzZejce+haL7weS249Bxcj/t8hMPfEgf0at3mRdfq8bYES8OO0FOhLmsu8GtyC7uY651pzv5XfL8eZDDd/i/cwNkeRnzAPo5CLl8eRM8X4lMMzdvcYhxIkfduxuyWBQ9GEi/Qok3yIWGIoN7mNtNq0hcS1/iwBQwCywC48FMsBhEjEaGmHN2qsjzAsAv2E/m3tkYg2GZsBvED8+Riwqk/T26MTfEvs9lHbDXS46MOYuer2A+35+4Bjm6t2a+LItaL1/BeSfYDw6Ds2BXFuWfd3PeCw6BE+A0yJQVuw7ygAJZ1Vp0Ic7Fsqp15m8ew//9HR36BttwmXyV6/uJDToQP7U/yJiiC7/+jZxIXfQkHl9o4bO3cD6PHSVuW46PdNeRb4WpthJH0F7VVtrE89RzBvkhA+RTliKXQcR0l5GnXvjQrz5mbufmcBjTgaz/dXBjCHSq3hZ0PQE5uYsdZx7UnjaN3cNY1CDPcxc6bSgwGJ7Bq2V1sZEJrLeSAwjagz5uRZWn0Kdw5mOsnwQ3w7+E0p4e+GtyiemriPqIJcdZzjFFiJmxCyH42iq5WHdmTHoFuJvy1R7KAuS4B7vfaGVO3CMf95NP3YQdqyXYriD8dxH0Nz9VPkGcVQC70Y35VUF4At9GFqLtzOnLw4cwbFnLItR7Ep0pSnxpExtzzlyEOLoY158ghihG/cjf6uLU7+YhKY50G2d13GTHFPut0o60I+1IO9KOtCPtSDvSjrQj7Ug70o6043/u6ELu281FHNJ5iRT5Al9eI8CXqzDyGTqPUdDIXbj5BL9A9gSvJSfLusvQxszdmTs3fIprrDNEs/bR9dSDczQ/sp+sH3mqZaz/HP2BXBA5qtMDWdONZ/9gFfaZbSQny36VXFZyOzvx7C5ZVXu7cu6RNbndvfm7edYHPzOM6xEg0u0L6KzriAW9sqo6JoJpWZPzODP4ezaYA+aC+WChm9PR/FjMOZPmyZush+UexN7KPqz/sae0F+tO6TaxJ2UieYmm5A7fJ+c2nH0mjVknzE1u44LFOiw5srnU3cCSBeTwFpMzve3uSyxHjoz8VTzrCYHkfb8gDx4=
*/