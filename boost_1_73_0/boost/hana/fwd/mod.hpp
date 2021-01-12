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
qn2qaW4WRQ0XeufR2FjngE27UtPa2b+UFSOJNeKaLHTayrgxbGTcGIrhc1AC/MywlXHbRsMA8R1BlMaNp5Ogin3To/I87pOO0TB2sCICVoXWMAasooWcUAPnmFUyAMSfUsD12h9kxMKQz24GguzF4uyepzc4hutyX866/A+j7VwSNHPJu9y5JFKki4k2xDgn0TTp6/80whwP9kG6V2JGXe+eZK6hl6kGakbANBxFlovr0rOU
*/