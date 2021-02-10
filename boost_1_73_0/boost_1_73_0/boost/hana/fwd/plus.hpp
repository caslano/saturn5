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


BOOST_HANA_NAMESPACE_BEGIN
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

    constexpr plus_t plus{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_PLUS_HPP

/* plus.hpp
H/0arouKvcCwbDwCjdrYXnsWkBlt6OB1vP+1xlz+H9iP0EggUmMteVWqw1JJItYGgKetR8YnHviVuVKuHYvYcmXFKFh4IgNc9apJphdAOJoGmCZXXZZXOtza48xJc7GtALbPIpMSiNaeseMgkwM4hlF/nbtWKEcqxlRg/r7Kxoe21SHCbbNQ0tkigIkmE7LUMEnbxpsgyvuZIyfr+O5l1pDiDYGV5JVObUFq8myXmBHreacTJAtc3iuRzHPeNtYBkKyjqxlL2tf09kvOCnLF+OUxfh2nwGJm5Br4a+dwWmtvtUdaAUMk4wR8q4fg0fV+1d3S0kxInyuTwaoEN7UpUzz0UaGlRNuPU/9apqJpxgRtkrcsm2wl7mtRVpP3dAHqdWbiILKJdLoiqDWda480Otkteqql1W1RleWW3mNKP9CTYnsJm6JUNnUAiyrLoIlUsVYOuEtmI+5W23wecLIa2Jhb0SLgdRpMai+32fWWEx2qtHg52fBWN7ZKDRU1+vjQGDoRw91nlZaXpuc6bc8fH1ZrjI4Ogo6hN9K2ZbTlO+Ow3qzTpL5fvNx4B5mImozzGMnkvkCa6/o9FJXJR1PMmsoiZqlQt6lDKeAspqdpqtF03swZt0rxGFbSsiMzWw75WDuw4Xzido0WF55W
*/