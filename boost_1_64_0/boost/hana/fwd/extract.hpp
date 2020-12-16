/*!
@file
Forward declares `boost::hana::extract`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_EXTRACT_HPP
#define BOOST_HANA_FWD_EXTRACT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Extract a value in a given comonadic context.
    //! @ingroup group-Comonad
    //!
    //! Given a value inside a comonadic context, extract it from that
    //! context, performing whatever effects are mandated by that context.
    //! This can be seen as the dual operation to the `lift` method of the
    //! Applicative concept.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Comonad `W`, the signature is
    //! \f$
    //!     \mathtt{extract} : W(T) \to T
    //! \f$
    //!
    //! @param w
    //! The value to be extracted inside a comonadic context.
    //!
    //!
    //! Example
    //! -------
    //! @include example/extract.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto extract = [](auto&& w) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename W, typename = void>
    struct extract_impl : extract_impl<W, when<true>> { };

    struct extract_t {
        template <typename W_>
        constexpr decltype(auto) operator()(W_&& w) const;
    };

    constexpr extract_t extract{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_EXTRACT_HPP

/* extract.hpp
8Zc8jUj0xoLA9qaRDv6qg0/0DJKTqoa0DftjQX/+20K9bXvXW3QZjmzRBC6zP2Im0J5qf2SGqTsDQFt80qUpoCObULz9kXa39DLKJUwbtVX23cmjjolxNvRziEZzxdzKFYCxwrJEDwK7RWCmGjheBPKd+xQSpRtCl1rocuB8+JwjHdEaCJmj1u9zXGHap6UHoSf00InKjSJUTDDJaNTnndYx7b9Q11d3Ck8+DFkx+mVhA+vAnPGEGLaPdyvp9P08AmhhCU3SV+Tr+Kdc/hVup3SZ5o2mHduh9SKW8bfEIcnGFgTCV1nkVG+4GhuhEaZXUyEpTB3UPYw2xiHsJkwwho38dIcQ6LNB/mfESfjImofBjx5FR6yidvrfGE6jVy1M6TyCdKnhldlyKjq5s4ytAMupDfNDK7MhdxSHyp76nfYP8/MZ6E95RfSEcv0v6bb6txetG0lqML9M99X7jf9DNf4nk+KHM7ZdnoB1J68nxhQSllQbBQ3QmGR7vJLjyyYIEn6TZ2RkwPiZ8Y/yaTX6qeRfSPkXfkACinVyjU7cN1CKtgNGOv/9Kh4+/gZe8nrny0YBJt/Em+x95sBPwTeu1qmuQ3Dh06are19DCoiD2a3V0Y2Ws0tz/WxD+IqqloPN71AYkvQhSVEPxmImXZkZ1UaH/JJD9rmHWtc7F1BBBHVqhzLWessJ2kftIdpsttLs2rm+GHGQ4F15Z519bgcD2vxDrS4zlDmYSZmDKV+RI3f3Hpd32X+8o7XGWBKxz36WSA24A3r7Cio7Kp2LF0pbhBeuIJOx8Y0PAhmSLFsZ7pX6cCn5wBeOqxFBDKBY17iVe39OnZhHG21wMe4OlkTWnK3FKZMcSO1WVnAcW3dF6ETa1otRO8YH7RUdrInH3InLmIVuKVOUVEwlLY0rqYxKusqtXMq55LpK/rbmq7EScriELFEC12Ju42aux1oXoT3mzo22wtby10vrQW9rSmkbT6ivlCvKKqSyTHFllVJZV7qVHThkuSBTjLJ+rpcF9RBU1oMIgyaqapSHvmT7qhuN5YRvEHTI30NRa9xRMiEJN2KZD5mPh4CeGMN0N7zliyeYrZ2DHaZnIezrulotJW50/TVGqplT1KyCS3Ur193Ohc3CPEVhsXJyuJxSLqeAywCEf52m6E4B4q95nEA8zeOIsut+SH/+J/9ozZ684qd+baD1K4Tnig5CQb59E9t3ml3Uw+wNzI+VjZuxyEbijssITSVyjvTEl+gKym4+bvBtDczJVLdUtpW8fwZvqA5HN9/di4GTX0LaYTwbsBVwEivNygcHyvZmkS3Lm1QQ9bDCGIUVi/UU5uEw28e7dIGyrOqTqZR/PolAwOE2n1Hvwaw7qwkPjsFvPiTp9wVv+mViBrr8VxvTlRwqNdVGQI6Jj6r9aCstHgdbf+Z/hAf+3qiarWB70URzolep0xDIgPILC6kSsLtwevxgalRbNiqgzG2Lh8eZVobHTrxIDxqmf66VMVZ+u2sI7SQYxwoV2HQXeZOvoKsJR7ZqBO8yvZ6XSJ81Y+tbuVWlt1h4X7Gh2g0og0rF6jI9RquLahVhWWiKidEfDYXy29cBnCzTsvDIfcp23meyux3cM17lvnWqbQHkl0Ot6KxvQJ4/elTkeRqQMjFeY4ClqENjoXc/wzPDcDqGZ2+d/Gboj+1txVTqg5g9tWwJuDiKn0cO5BbthlVCGoxCPJNI8AZPAZ68jWOq5Erb5vUH/RLqcIZcRxOroMQkIy4Cls8LHUldURl1frl9i8mx7ujYwFDWyUFZdefLs232xyPuaIC3DWigD1iVz8fs7fxEWLUpprxEOaEjaYE7UQaKypFN1SVEHq/MHrm798U=
*/