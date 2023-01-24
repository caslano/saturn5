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


BOOST_HANA_NAMESPACE_BEGIN
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

    constexpr mult_t mult{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_MULT_HPP

/* mult.hpp
qCvzod3VSL6PoTWbyrKWwUk3acAjfxUXmMcHjH4aC3WIsXlQ0pEjk5J6h1qLMO+Qbpm4J7lYSsf76yDIWLq78aI83IJSs5pqin449utjVg5IEs3RUzJzy9OSG3zOHh50NCyeYo6mEh54Lh32zuMT6kXgO3lkJs9vuIdFrx5Rjq2rNC858YDdqCHNYEf540jGhXBqEq/vlYJo8ZU6nqhTvsY5ydC8tAghuk+8H5efi3UOWQb1rjb0vaYJnb1z6ZnFA3xHr3c329/5VThPOAepxqf05tLt2fmuaRAQKbdnau09awialv/hNrHRxNXVnBpUy1Cou8CMWmtdlHKwqxJJVmF0Mu6O8BWJNavQ1/KMYCrOLz0u+ZKqmBI8bjE5AnJrjlvSf64fZdOj6SkRcV+tQWxUA59SnqgP0bhaYdyc/TlDGEj3jgNFCRHN9VBQy4ivXcgQE8PgT9sYVu/kHakaHF6manHf8oLm3yM5Tm4Tgb2SwQI+BDPUT9HUtRkG2P50R7MjmtSgxz8YyIshbCiLHTASYwWpqtXmaHnjC7rvYbYBVLIPjZIHCpsrE+3HhygqqY3kWbaV7/yKhADL06OaCivWg4SFeMXLXDoxUcnFsoONE8vv0p/f5grx144f6pw8L8Ti14gud8Iay/RANYoYYAFmSYOENuUqBP1BQT3wdDohQ69tqNFJi5Sd2MXzgkWrQrdOUSDJp11W72uq
*/