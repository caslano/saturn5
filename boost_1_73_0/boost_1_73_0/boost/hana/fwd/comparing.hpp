/*!
@file
Forward declares `boost::hana::comparing`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_COMPARING_HPP
#define BOOST_HANA_FWD_COMPARING_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns a function performing `equal` after applying a transformation
    //! to both arguments.
    //! @ingroup group-Comparable
    //!
    //! `comparing` creates an equivalence relation based on the result of
    //! applying a function to some objects, which is especially useful in
    //! conjunction with algorithms that accept a custom predicate that must
    //! represent an equivalence relation.
    //!
    //! Specifically, `comparing` is such that
    //! @code
    //!     comparing(f) == equal ^on^ f
    //! @endcode
    //! or, equivalently,
    //! @code
    //!     comparing(f)(x, y) == equal(f(x), f(y))
    //! @endcode
    //!
    //! @note
    //! This is not a tag-dispatched method (hence it can't be customized),
    //! but just a convenience function provided with the `Comparable` concept.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Logical `Bool` and a Comparable `B`, the signature is
    //! @f$ \mathtt{comparing} : (A \to B) \to (A \times A \to Bool) @f$.
    //!
    //!
    //! Example
    //! -------
    //! @include example/comparing.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto comparing = [](auto&& f) {
        return [perfect-capture](auto&& x, auto&& y) {
            return equal(f(forwarded(x)), f(forwarded(y)));
        };
    };
#else
    struct comparing_t {
        template <typename F>
        constexpr auto operator()(F&& f) const;
    };

    constexpr comparing_t comparing{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_COMPARING_HPP

/* comparing.hpp
yDm9Y+jRRjL5+fQrIuEUGd/fJXnXvRmNRwOI12OT6Y3tGSCKsWFBI1igx12qcI6iLEvIreSqoxGcjzcYQeG3GqSnUBiM5OENVMr2WYsMMCMvuWSJqSdU5712/33LcH4AcagKxbplLN3494wpXFBFKNDqMDEQiJgCC27o9Zt91pGpoUEcgGMigOorhdpMxAYPRpvaqnR6xHBaDHKhZA4q8mnCTYlFF2aCpFE1U55YQgoEBTtTwZjxTtKIlNhyUbAPBzyc75LfhLYkZmjaN1UoDiRYGvtqp4zJhmg16YwHKjH80sG/d3BncWgKqmMYiEQ+9+SlmtOX33wr40USnTfiHw+iWKU5R/8F0a5cKxusKXSWspIRgABB/otFHJ/i6fF21MFy5oit0N5IIVGklUMj+e3N0XNMKdOjIzQEPQrhizmYYpNVanVmj2yeTZ4W+TAdYjZ8IussMdDifGmurvRPYEmVlPGZ3PU0qctE6438tbVp1puqTW2DI+9SBY/S9pjR5euCh8qCrfy/gVWSaxM1l+xh5oaH+fJOqMSjq/epxJ0zoLxbV0NsLDvn2slyMwqM0sqXULfn6/G0AslOYCEoAYjh+JXYBKTZAQxijrUFqDkVpCwzAM7RG5arIMYTQDkHzDDb4uiPqshn8o6r
*/