/*!
@file
Forward declares `boost::hana::mult`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_MULT_HPP
#define BOOST_HANA_FWD_MULT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Associative operation of a `Ring`.
    //! @ingroup group-Ring
    //!
    //! @param x, y
    //! Two `Ring` elements to combine with the `Ring` binary operation.
    //!
    //!
    //! Cross-type version of the method
    //! --------------------------------
    //! The `mult` method is "overloaded" to handle distinct data types
    //! with certain properties. Specifically, `mult` is defined for
    //! _distinct_ data types `A` and `B` such that
    //! 1. `A` and `B` share a common data type `C`, as determined by the
    //!    `common` metafunction
    //! 2. `A`, `B` and `C` are all `Ring`s when taken individually
    //! 3. `to<C> : A -> B` and `to<C> : B -> C` are `Ring`-embeddings, as
    //!    determined by the `is_embedding` metafunction.
    //!
    //! The definition of `mult` for data types satisfying the above
    //! properties is obtained by setting
    //! @code
    //!     mult(x, y) = mult(to<C>(x), to<C>(y))
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/mult.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto mult = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct mult_impl : mult_impl<T, U, when<true>> { };

    struct mult_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    constexpr mult_t mult{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_MULT_HPP

/* mult.hpp
gZYCxm/mAQ+h5YA5s7nrcJsa/JyyCU2+RB65AhLBILMxtPXAGrn+yHIf4Li02HeczxlQ0WKh402grLeYAaMCKjAEgWO57PGTe/fu2Z7LOu/OT83O627nO7PTf/O2d9o9p+dG3R+q9T1AH98yR9IdRno2B1wDNuSACCJnI7V/9fxrr3Xv3knHfNF9+e5s+zIHjY9NdnmPsfvwUWBMxz5uLDyq3tCfQ/+OG3sNWXzsWpPQtIcT03LdVIXkzS0PC97443HOG2D7Amj4Jh8avslCS/ADRhkD6qP5nP4+bni+KpBDDSBUx+wUvHv99t0PhS97z98Uvzu76J4Wvu2cnpy9Knj36uxdYb3TTtGbwaue+ab3dvD2vF9YW5UpLvDurKz+Re/sx8KX708u4Du9RkIjo/IwYo0tjcUa7JjFQ/YMOdlDXgNl+fXXZhfkfv+bL9r3UBThw95boIe8yVOhU0a+N3YmC1AqqNZBVdo+aDrPj4TadjyQ1pmFyplZQ38RIXQCE0sKanpUSgsU3SYoeheKQ1XQcjQ9IK/A098WTiB0H/dIl/sBwQFFRn9OuMcD0RBoQZsPFxNqvYkK3Jk5n+S7Of4ifXUtOhK2kq5NrYiDmgGlEUX4ihBDBce9COerzsvTk1cDdu24Lki4EG9U
*/