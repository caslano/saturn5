/*!
@file
Forward declares `boost::hana::div`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_DIV_HPP
#define BOOST_HANA_FWD_DIV_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Generalized integer division.
    //! @ingroup group-EuclideanRing
    //!
    //!
    //! Cross-type version of the method
    //! --------------------------------
    //! The `div` method is "overloaded" to handle distinct data types
    //! with certain properties. Specifically, `div` is defined for
    //! _distinct_ data types `A` and `B` such that
    //! 1. `A` and `B` share a common data type `C`, as determined by the
    //!    `common` metafunction
    //! 2. `A`, `B` and `C` are all `EuclideanRing`s when taken individually
    //! 3. `to<C> : A -> B` and `to<C> : B -> C` are `Ring`-embeddings, as
    //!    determined by the `is_embedding` metafunction.
    //!
    //! In that case, the `div` method is defined as
    //! @code
    //!     div(x, y) = div(to<C>(x), to<C>(y))
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/div.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto div = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct div_impl : div_impl<T, U, when<true>> { };

    struct div_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    constexpr div_t div{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_DIV_HPP

/* div.hpp
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
*/