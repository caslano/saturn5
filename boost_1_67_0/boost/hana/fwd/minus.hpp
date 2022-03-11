/*!
@file
Forward declares `boost::hana::minus`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_MINUS_HPP
#define BOOST_HANA_FWD_MINUS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Subtract two elements of a group.
    //! @ingroup group-Group
    //!
    //! Specifically, this performs the `Monoid` operation on the first
    //! argument and on the inverse of the second argument, thus being
    //! equivalent to:
    //! @code
    //!     minus(x, y) == plus(x, negate(y))
    //! @endcode
    //!
    //!
    //! Cross-type version of the method
    //! --------------------------------
    //! The `minus` method is "overloaded" to handle distinct data types
    //! with certain properties. Specifically, `minus` is defined for
    //! _distinct_ data types `A` and `B` such that
    //! 1. `A` and `B` share a common data type `C`, as determined by the
    //!    `common` metafunction
    //! 2. `A`, `B` and `C` are all `Group`s when taken individually
    //! 3. `to<C> : A -> B` and `to<C> : B -> C` are `Group`-embeddings, as
    //!    determined by the `is_embedding` metafunction.
    //!
    //! The definition of `minus` for data types satisfying the above
    //! properties is obtained by setting
    //! @code
    //!     minus(x, y) = minus(to<C>(x), to<C>(y))
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/minus.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto minus = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct minus_impl : minus_impl<T, U, when<true>> { };

    struct minus_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    constexpr minus_t minus{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_MINUS_HPP

/* minus.hpp
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
*/