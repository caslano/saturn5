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


BOOST_HANA_NAMESPACE_BEGIN
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

    constexpr equal_t equal{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_EQUAL_HPP

/* equal.hpp
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
*/