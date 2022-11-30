/*!
@file
Forward declares `boost::hana::mod`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_MOD_HPP
#define BOOST_HANA_FWD_MOD_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


namespace boost { namespace hana {
    //! Generalized integer modulus.
    //! @ingroup group-EuclideanRing
    //!
    //! Given two elements of an EuclideanRing `x` and `y`, with `y`
    //! nonzero, `mod` returns the modulus of the division of `x` by `y`.
    //! In other words, `mod` can be seen as an equivalent to `%`.
    //!
    //! Cross-type version of the method
    //! --------------------------------
    //! The `mod` method is "overloaded" to handle distinct data types
    //! with certain properties. Specifically, `mod` is defined for
    //! _distinct_ data types `A` and `B` such that
    //! 1. `A` and `B` share a common data type `C`, as determined by the
    //!    `common` metafunction
    //! 2. `A`, `B` and `C` are all `EuclideanRing`s when taken individually
    //! 3. `to<C> : A -> B` and `to<C> : B -> C` are `Ring`-embeddings, as
    //!    determined by the `is_embedding` metafunction.
    //!
    //! In that case, `mod` is defined as
    //! @code
    //!     mod(x, y) = mod(to<C>(x), to<C>(y))
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/mod.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto mod = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct mod_impl : mod_impl<T, U, when<true>> { };

    struct mod_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr mod_t mod{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_MOD_HPP

/* mod.hpp
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
*/