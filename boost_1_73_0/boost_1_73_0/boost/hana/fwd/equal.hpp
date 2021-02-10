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
63Keupej2GgCAxnAH27JUn4qm08WuHINJseYkXxOitb18Aw06J8biVZ3V0WX6Dhgo6f3pXpiGaN29CcpP/LBDD4SpN6l5WPs+VEFmfkek+GfiUyZR/Y0bQaBaNpS0ZLq6sQzCwjzQcMoqqub2UGYH1BYoFWJea8PenAR9FMjTah2NpBtVcOi4rKGtXLhZBnJXXQuV6gnf9OigbVhtG7O6G+/Z+ndElqsgjw1yjkph6birNJkNwzsMFZsSNNyX3pYnGDr/vSMOcn62nx1URVm6WpYl17Ahh+m4M7FAqsyr2RF3hads0jurGIWHZ537zifoN2AqDrrifk0zpC4N4KrGjGyCfnKAH3QPRWClDemkyLVwAdO6lwQucZnzyCoFXtg2UJa2qirGYMrR1U5WoWi+0ZlbVbYCCA2KnPd/wPLXPERFny/pIrff0GV69pkzPdOxRTyKaVDQJi1rBjChJIbJu11aA6jn1YMtfSBxpPl6hITyxXDGeFyEv02Gg97/VPiyfMe8OTx+cXrs17nbfcjd/tdTXXjXoNh7/T3LCX1wITUfQR8LCkeOQftZvOweErW4FFV4Jadn9Xt8LhseTt1kFY5dhR8D086+3/d+ysnauPK3WfOGeDEzVOJCjQ2pv4OOIauHzhIl6ISK2bx
*/