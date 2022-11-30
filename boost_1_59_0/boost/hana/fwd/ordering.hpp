/*!
@file
Forward declares `boost::hana::ordering`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ORDERING_HPP
#define BOOST_HANA_FWD_ORDERING_HPP

#include <boost/hana/config.hpp>


namespace boost { namespace hana {
    //! Returns a function performing `less` after applying a transformation
    //! to both arguments.
    //! @ingroup group-Orderable
    //!
    //! `ordering` creates a total order based on the result of applying a
    //! function to some objects, which is especially useful in conjunction
    //! with algorithms that accept a custom predicate that must represent
    //! a total order.
    //!
    //! Specifically, `ordering` is such that
    //! @code
    //!     ordering(f) == less ^on^ f
    //! @endcode
    //! or, equivalently,
    //! @code
    //!     ordering(f)(x, y) == less(f(x), f(y))
    //! @endcode
    //!
    //! @note
    //! This is not a tag-dispatched method (hence it can't be customized),
    //! but just a convenience function provided with the `Orderable` concept.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Logical `Bool` and an Orderable `B`, the signature is
    //! @f$ \mathrm{ordering} : (A \to B) \to (A \times A \to Bool) @f$.
    //!
    //!
    //! Example
    //! -------
    //! @include example/ordering.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto ordering = [](auto&& f) {
        return [perfect-capture](auto&& x, auto&& y) -> decltype(auto) {
            return less(f(forwarded(x)), f(forwarded(y)));
        };
    };
#else
    struct ordering_t {
        template <typename F>
        constexpr auto operator()(F&& f) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr ordering_t ordering{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_ORDERING_HPP

/* ordering.hpp
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
*/