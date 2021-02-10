/*!
@file
Forward declares `boost::hana::not_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_NOT_HPP
#define BOOST_HANA_FWD_NOT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Negates a `Logical`.
    //! @ingroup group-Logical
    //!
    //! This method returns a `Logical` with the same tag, but whose
    //! truth-value is negated. Specifically, `not_(x)` returns a false-valued
    //! `Logical` if `x` is a true-valued `Logical`, and a true-valued one
    //! otherwise.
    //!
    //!
    //! Example
    //! -------
    //! @include example/not.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto not_ = [](auto&& x) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename L, typename = void>
    struct not_impl : not_impl<L, when<true>> { };

    struct not_t {
        template <typename X>
        constexpr decltype(auto) operator()(X&& x) const;
    };

    constexpr not_t not_{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_NOT_HPP

/* not.hpp
SoV5PEGoojcqFUdRdTpPEKrra1ouGk6cDXxSnl/BwwxN3LkDKyH8f3QNsa6L4zPJgYim+RNEYR74NaRBMHd121aTopoSQXhtLBQxIt93zwe9/lmVOohzhXprCNZ2YYW8NhNJ+/13MQkXVi+surO2+NFI/38pgSqU7S6Fb+G9rSZ3EpmKtomCWyA3OrQ63KzqrW+mxBDu2I1o3NBnH/9p4z8H+M8h/lPgwLgpYKbPwEky6vEO+ejC8W4rcJFApCIPCZgFHISQ1jByZbX1+Uf0oJB7ljZ8/trGbhzxeoes8d6K4E0F5lDIVGQPBbeAQQS0NVgkrliLSZYRIP/OGm4kUa+CG0nSa4UfCefG/UfpCbI4WqK6Syk1SX5+X5Ls3CpnUkF/6nWmAPsC1DfxNvTPwC66MHtnndN3L7rmRd/sDX4cXHTfbCCAnanlTXjIwsjybCvAAOeRu7A5m1vRNFyOyKZKGIDReftWhGg7XuSDRN2GEZ+la7dE4LoTUiUbfTxQFEBeIUi0Ldk4ACFUAeUY1CgjxZkMCplyy+ZBKMoBK4ec4WkUiixvMsuNpv5iMhXnakYOBmBjLQItowRCWS2GjIHmGDVPMjXCUzRLmqWQ0EVr6MFrqN0xB/961+3+1K0YyVG4lBj5HiAfMaMX
*/