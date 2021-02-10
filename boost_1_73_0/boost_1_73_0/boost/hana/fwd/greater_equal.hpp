/*!
@file
Forward declares `boost::hana::greater_equal`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_GREATER_EQUAL_HPP
#define BOOST_HANA_FWD_GREATER_EQUAL_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_than_fwd.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns a `Logical` representing whether `x` is greater than or
    //! equal to `y`.
    //! @ingroup group-Orderable
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Logical `Bool` and two Orderables `A` and `B` with a common
    //! embedding, the signature is
    //! @f$ \mathrm{greater\_equal} : A \times B \to Bool @f$.
    //!
    //! @param x, y
    //! Two objects to compare.
    //!
    //!
    //! Example
    //! -------
    //! @include example/greater_equal.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto greater_equal = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct greater_equal_impl : greater_equal_impl<T, U, when<true>> { };

    struct greater_equal_t : detail::nested_than<greater_equal_t> {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    constexpr greater_equal_t greater_equal{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_GREATER_EQUAL_HPP

/* greater_equal.hpp
832eb8bkXK2NkGu4GaaD4Szr38/usuXobtBPZ4PspnWOz5SRP3vc7fy+qwUdePfK4jfDC8foMXX2H8nDaesse4Xqg16POL4H0oWDy2t2Ae+7vEI7umQ1ymeaZ9l7QI/EjX665PmY0RRX0I08+7bYOfWUB2j3L+DT1ccr+IDDp6sEBswoqWEepFlJ95TAZxFXvubs5eXSyy8JyABMX9ahFrny4O06bJmTgHOtuDReCmAehPTcqRXeKAMhl7BWWkJ/Mn0Yjf9KYJsrnlOQnS3B57bUAnL2LMFJLtVzFaNgLoBdozsGF8oHDFgGZc0lYksI0m08xSB4pr0F9syUZisEYgHyEAr/R7fLS6eRfVdY7rt8v/3LPGyanTwgiQ3bgS0CBAullwmQZQIbK9SaRkwILhblSiufJwc2CGVE1zrwUmuKhX5K+oq2hHmdnoTMoEDGKtDgrfEEtc3t5sgQ80hR1qUzCIR5QCNhMc0JlNhOLhrHne8h6pzGBP9UmgNfAdYgGThL5zCan8GKeeUTWI4WN5P7BSzT2SwdLx5g8g3S8QMFux2NByi9QjAH8qVw0iO4A7UptJKixvx9V7fVOleG61JIOCP1Mi9DWVzmZ/SgOlTicTEYzdM/74bZt8X0jYdGhUI07naA5pSordKC
*/