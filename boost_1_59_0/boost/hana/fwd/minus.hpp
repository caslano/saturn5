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


namespace boost { namespace hana {
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

    BOOST_HANA_INLINE_VARIABLE constexpr minus_t minus{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_MINUS_HPP

/* minus.hpp
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
*/