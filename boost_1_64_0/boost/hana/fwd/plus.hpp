/*!
@file
Forward declares `boost::hana::plus`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_PLUS_HPP
#define BOOST_HANA_FWD_PLUS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Associative binary operation on a `Monoid`.
    //! @ingroup group-Monoid
    //!
    //! @param x, y
    //! Two objects to combine with the `Monoid`'s binary operation.
    //!
    //!
    //! Cross-type version of the method
    //! --------------------------------
    //! The `plus` method is "overloaded" to handle distinct data types
    //! with certain properties. Specifically, `plus` is defined for
    //! _distinct_ data types `A` and `B` such that
    //! 1. `A` and `B` share a common data type `C`, as determined by the
    //!    `common` metafunction
    //! 2. `A`, `B` and `C` are all `Monoid`s when taken individually
    //! 3. `to<C> : A -> B` and `to<C> : B -> C` are `Monoid`-embeddings, as
    //!    determined by the `is_embedding` metafunction.
    //!
    //! The definition of `plus` for data types satisfying the above
    //! properties is obtained by setting
    //! @code
    //!     plus(x, y) = plus(to<C>(x), to<C>(y))
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/plus.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto plus = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct plus_impl : plus_impl<T, U, when<true>> { };

    struct plus_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    constexpr plus_t plus{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_PLUS_HPP

/* plus.hpp
ao91bQJzBFPZkEZ1XFG47H4JhHjM/9VayAabItoiv4eE3iO37VgHJ/ESWs3VzG/ZfoM5QRI7XPv/ueHiCqB64tQqs1u+U5I/Ni2/fFjyKk94KAdgB3Xm7MNrvAvdiOCr0SDtkwRXt/3aWJkGLN0N3wULf9Cs9+ULaCMsoEAfl6B1ViS+IfN2wJv1g7+1ufeApXFmNRAEZOsr54hUuWaWfpEjI3I243BEcO0Y1j3HgWgwMeJcTFpkCv+JO5ySvVmbDENorhaY+cLgbOtR+q1KNMOraSNEUziYj6Hahk94OGzMqmFcDYEEzX4f7R8fvPEbPmKW119fTPwxXOqNZpcvlKyf59Q6DDnFKCug/gKFG7XpyiapAhk9FXDpxAkAbHP/FxT1jGkiAdocRPPle9zN7qPj47paMW56PtAmn8O2rC40uvvoawIoE7bP+I1qdyzSlHXfvS66tq7SWyKFKnFarwj2fQmrV+ooSN71R+T0qJMKDoodi+i9fFevq9AfAimhbJsCCrYAM71yPzsiI1mcUNFyP3kV4iz9S+NyCLI+lRl2W6RsDb3ckfUe9A==
*/