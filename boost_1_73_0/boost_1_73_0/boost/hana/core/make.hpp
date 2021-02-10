/*!
@file
Defines `boost::hana::make`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CORE_MAKE_HPP
#define BOOST_HANA_CORE_MAKE_HPP

#include <boost/hana/fwd/core/make.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Datatype, typename>
    struct make_impl : make_impl<Datatype, when<true>> { };
    //! @endcond

    template <typename Datatype, bool condition>
    struct make_impl<Datatype, when<condition>> : default_ {
        template <typename ...X>
        static constexpr auto make_helper(int, X&& ...x)
            -> decltype(Datatype(static_cast<X&&>(x)...))
        { return Datatype(static_cast<X&&>(x)...); }

        template <typename ...X>
        static constexpr auto make_helper(long, X&& ...) {
            static_assert((sizeof...(X), false),
            "there exists no constructor for the given data type");
        }

        template <typename ...X>
        static constexpr decltype(auto) apply(X&& ...x)
        { return make_helper(int{}, static_cast<X&&>(x)...); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CORE_MAKE_HPP

/* make.hpp
skEy6w3b7bdOu3vGnXz0Nrh5zmihbky73vsM/1WQpptRBX+RfkQa3tMwnjcvh229Bc3PNelY7Mby1p/qYrMRVMbQsD16IIaEwLEgJ9WaAv2ZuFeotcW3bbLmwqo3V1itRk5GM+ymJos1FCboJEvRCQhKh/XN8TybzMPIy5vEJ5mhGvRYYXPEetwiQvve4/c8xtSy0Q5E5KcKw8XP163km85iW1wmYx+9+92l668INhwHclY/2BUrX9+VuNSs8TLJu/aW4zNOBzUU0nfqEuaTbNGJKkpaRl3OsSmqmIgCGB3Usu6mUkrWpz9hhuKqa15lDYMac0VQOMutCyoWZwH0sL5Tk+0jTZusS2vFJBd8J2q9SvMEnUVfYWQwjCMxCt/5U6+FYnGrT3JyhniuXqPm7HS6ZCNEK+dgmCmUN/QGoxUmgMpU0wYiSqZHnVrLySBe0Z1qFJ2SZxgpQOsutVi1zn5Xdf5M8/gMW9SrHYjiuoSo63X98/edBZ6S4lIf4sPaU0mBDXO0B8a6ohWnT2tWhuTsgnbEdEXLUpX7g4BMUK9BLFzbpk2YfMBO2RsvvnSjuI2PamlOpRU8ZWRLUTTRbw6HtKg241w+ocrgXQ2r7XJ7KdeMH7GxO7We9+XIF/XCyf2GMFL8PHEhLmIH
*/