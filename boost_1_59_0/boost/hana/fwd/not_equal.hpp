/*!
@file
Forward declares `boost::hana::not_equal`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_NOT_EQUAL_HPP
#define BOOST_HANA_FWD_NOT_EQUAL_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_to_fwd.hpp>


namespace boost { namespace hana {
    //! Returns a `Logical` representing whether `x` is not equal to `y`.
    //! @ingroup group-Comparable
    //!
    //! The `not_equal` function can be called in two different ways. First,
    //! it can be called like a normal function:
    //! @code
    //!     not_equal(x, y)
    //! @endcode
    //!
    //! However, it may also be partially applied to an argument by using
    //! `not_equal.to`:
    //! @code
    //!     not_equal.to(x)(y) == not_equal(x, y)
    //! @endcode
    //!
    //! In other words, `not_equal.to(x)` is a function object that is
    //! equivalent to `partial(not_equal, x)`. This is provided to enhance
    //! the readability of some constructs, especially when using higher
    //! order algorithms.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Logical `Bool` and two Comparables `A` and `B` that
    //! share a common embedding, the signature is
    //! @f$ \mathtt{not\_equal} : A \times B \to Bool @f$.
    //!
    //! @param x, y
    //! Two objects to compare for inequality.
    //!
    //!
    //! Example
    //! -------
    //! @include example/not_equal.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto not_equal = [](auto&& x, auto&& y) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct not_equal_impl : not_equal_impl<T, U, when<true>> { };

    struct not_equal_t : detail::nested_to<not_equal_t> {
        template <typename X, typename Y>
        constexpr auto operator()(X&& x, Y&& y) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr not_equal_t not_equal{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_NOT_EQUAL_HPP

/* not_equal.hpp
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
*/