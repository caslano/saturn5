/*!
@file
Forward declares `boost::hana::equal`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_EQUAL_HPP
#define BOOST_HANA_FWD_EQUAL_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_to_fwd.hpp>


namespace boost { namespace hana {
    //! Returns a `Logical` representing whether `x` is equal to `y`.
    //! @ingroup group-Comparable
    //!
    //! The `equal` function can be called in two different ways. First, it
    //! can be called like a normal function:
    //! @code
    //!     equal(x, y)
    //! @endcode
    //!
    //! However, it may also be partially applied to an argument by using
    //! `equal.to`:
    //! @code
    //!     equal.to(x)(y) == equal(x, y)
    //! @endcode
    //!
    //! In other words, `equal.to(x)` is a function object that is equivalent
    //! to `partial(equal, x)`. This is provided to enhance the readability of
    //! some constructs, especially when using higher order algorithms.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Logical `Bool` and two Comparables `A` and `B` that
    //! share a common embedding, the signature is
    //! @f$ \mathtt{equal} : A \times B \to Bool @f$.
    //!
    //! @param x, y
    //! Two objects to compare for equality.
    //!
    //!
    //! Example
    //! -------
    //! @include example/equal.cpp
    //!
    //!
    //! > #### Rationale for the arity of `equal`
    //! > It is a valid question whether `equal` should accept more than 2
    //! > arguments and have semantics matching those of Python's `==`. This
    //! > is not supported right now for the following reasons:
    //! > - It was implemented in the MPL11, but it was not shown to be useful
    //! >   so far.
    //! > - It does not make sense for `not_equal` to have an arity of more
    //! >   than 2, only `equal` could maybe have those semantics, which would
    //! >   break symmetry.
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto equal = [](auto&& x, auto&& y) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct equal_impl : equal_impl<T, U, when<true>> { };

    struct equal_t : detail::nested_to<equal_t> {
        template <typename X, typename Y>
        constexpr auto operator()(X&& x, Y&& y) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr equal_t equal{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_EQUAL_HPP

/* equal.hpp
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
*/