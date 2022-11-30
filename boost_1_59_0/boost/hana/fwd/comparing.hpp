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


namespace boost { namespace hana {
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

    BOOST_HANA_INLINE_VARIABLE constexpr comparing_t comparing{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_COMPARING_HPP

/* comparing.hpp
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
*/