/*!
@file
Forward declares `boost::hana::plus`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_PLUS_HPP
#define BOOST_HANA_FWD_PLUS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


namespace boost { namespace hana {
    //! Associative binary operation on a `Monoid`.
    //! @ingroup group-Monoid
    //!
    //! @param x, y
    //! Two objects to combine with the `Monoid`'s binary operation.
    //!
    //!
    //! Cross-type version of the method
    //! --------------------------------
    //! The `plus` method is "overloaded" to handle distinct data types
    //! with certain properties. Specifically, `plus` is defined for
    //! _distinct_ data types `A` and `B` such that
    //! 1. `A` and `B` share a common data type `C`, as determined by the
    //!    `common` metafunction
    //! 2. `A`, `B` and `C` are all `Monoid`s when taken individually
    //! 3. `to<C> : A -> B` and `to<C> : B -> C` are `Monoid`-embeddings, as
    //!    determined by the `is_embedding` metafunction.
    //!
    //! The definition of `plus` for data types satisfying the above
    //! properties is obtained by setting
    //! @code
    //!     plus(x, y) = plus(to<C>(x), to<C>(y))
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/plus.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto plus = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct plus_impl : plus_impl<T, U, when<true>> { };

    struct plus_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr plus_t plus{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_PLUS_HPP

/* plus.hpp
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
*/