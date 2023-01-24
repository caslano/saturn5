/*!
@file
Forward declares `boost::hana::make`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CORE_MAKE_HPP
#define BOOST_HANA_FWD_CORE_MAKE_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-core
    //! Create an object of the given tag with the given arguments.
    //!
    //! This function serves the same purpose as constructors in usual C++.
    //! However, instead of creating an object of a specific C++ type, it
    //! creates an object of a specific tag, regardless of the C++ type
    //! of that object.
    //!
    //! This function is actually a variable template, so `make<T>` can be
    //! passed around as a function object creating an object of tag `T`.
    //! Also, it uses tag-dispatching so this is how it should be customized
    //! for user-defined tags.
    //!
    //! Finally, the default implementation of `make` is equivalent to calling
    //! the constructor of the given tag with the corresponding arguments.
    //! In other words, by default,
    //! @code
    //!     make<T>(args...) == T(args...)
    //! @endcode
    //!
    //! Note that the arguments are perfectly forwarded and the form of
    //! construction which is used is exactly as documented, i.e. `T(args...)`.
    //! However, if `T(args...)` is not a valid expression, a compilation
    //! error is triggered. This default behavior is useful because it makes
    //! foreign C++ types that have no notion of tag constructible with `make`
    //! out-of-the-box, since their tag is exactly themselves.
    //!
    //!
    //! Example
    //! -------
    //! @include example/core/make.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename Tag>
    constexpr auto make = [](auto&& ...x) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename Tag, typename = void>
    struct make_impl;

    template <typename Tag>
    struct make_t {
        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) const {
            return make_impl<Tag>::apply(static_cast<X&&>(x)...);
        }
    };

    template <typename Tag>
    constexpr make_t<Tag> make{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CORE_MAKE_HPP

/* make.hpp
WW5apmWOaPoG2vya2qLGDEeMGuKX/yT4UR0v19nm+QdN0hymn1TZPU8RMPuVfPLgdlW5cXV40AAf1UGFoo7vCNVhLJ2Kyr/HVx8qX/BRBPt1aIr5EYCT+Txr+bb9tNTUl0W3Shg39hAfglD+iueAnXiZtMP3r4bIg8IEZDwv7NHEAz/LtwgtgR3w1e3YaCF5SOB0AWnUSVFpeedPBrUK8/U9DA3c9E+QrRrvT/n1RJmDsLNvIbKNzm2DEeaSHMTzcPNX9hSm4+WHOeGJg4D3wK0YDFV6h2UWk0jESrEVjmG2N7a8GjG4EVsOIl2/9cvqW6p7VxdIdSWPnlhJiLAc9HK0WTGUT5UklNN3Pc2uNTc+ItxHsAt5ycbqrWbfW7xvzp/ayBCcZEs+sRZ6OFS8KFxZL6x1a2sW10ZNskHdrcmDG2GqeaKJrJev72cMMRmg2Zb+pR0SGtIaWT/6ge+mAulnqbX9gu+aJkCkeqbIg9Jrnujiy9ae18+ZFx3W/Wb97/s5zY8PZBBroA117zdFtat3ULT70ERUEcrfql1o29meWSiDduR9keO1YwE8zzeiysE3xEV48eoqLqE6WawPqNLfv8juvaeSVaEcJU1f3I3dbF9068I6WHlnw9D3zMrS25TH6MBlInc1/eokSI7VlQqLvyoR3JHG9+TMD2d7PKjrIYKenUr6o/qzUEPyIZmeOR8hur8guL1xsBwY
*/