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


BOOST_HANA_NAMESPACE_BEGIN
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

    constexpr mod_t mod{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_MOD_HPP

/* mod.hpp
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
*/