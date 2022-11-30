/*!
@file
Forward declares `boost::hana::mult`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_MULT_HPP
#define BOOST_HANA_FWD_MULT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


namespace boost { namespace hana {
    //! Associative operation of a `Ring`.
    //! @ingroup group-Ring
    //!
    //! @param x, y
    //! Two `Ring` elements to combine with the `Ring` binary operation.
    //!
    //!
    //! Cross-type version of the method
    //! --------------------------------
    //! The `mult` method is "overloaded" to handle distinct data types
    //! with certain properties. Specifically, `mult` is defined for
    //! _distinct_ data types `A` and `B` such that
    //! 1. `A` and `B` share a common data type `C`, as determined by the
    //!    `common` metafunction
    //! 2. `A`, `B` and `C` are all `Ring`s when taken individually
    //! 3. `to<C> : A -> B` and `to<C> : B -> C` are `Ring`-embeddings, as
    //!    determined by the `is_embedding` metafunction.
    //!
    //! The definition of `mult` for data types satisfying the above
    //! properties is obtained by setting
    //! @code
    //!     mult(x, y) = mult(to<C>(x), to<C>(y))
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/mult.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto mult = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct mult_impl : mult_impl<T, U, when<true>> { };

    struct mult_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr mult_t mult{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_MULT_HPP

/* mult.hpp
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
*/