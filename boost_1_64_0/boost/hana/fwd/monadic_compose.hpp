/*!
@file
Forward declares `boost::hana::monadic_compose`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_MONADIC_COMPOSE_HPP
#define BOOST_HANA_FWD_MONADIC_COMPOSE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Composition of monadic functions.
    //! @ingroup group-Monad
    //!
    //! Given two monadic functions `f` and `g`, `monadic_compose` returns
    //! a new function equivalent to the composition of `f` with `g`, except
    //! the result of `g` is `chain`ed into `f` instead of simply passed to
    //! it, as with normal composition. `monadic_compose` satisfies
    //! @code
    //!     monadic_compose(f, g)(x) == chain(g(x), f)
    //! @endcode
    //!
    //!
    //! @note
    //! Unlike `compose`, `monadic_compose` does not generalize nicely to
    //! arities higher than one. Hence, only unary functions may be used
    //! with `monadic_compose`.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a `Monad` `M` and two functions @f$ f : B \to M(C) @f$ and
    //! @f$ g : A \to M(B) @f$, the signature is
    //! @f$
    //!     \mathtt{monadic\_compose}
    //!         : (B \to M(C)) \times (A \to M(B)) \to (A \to M(C))
    //! @f$.
    //!
    //! @param f
    //! A monadic function with signature @f$ B \to M(C) @f$.
    //!
    //! @param g
    //! A monadic function with signature @f$ A \to M(B) @f$.
    //!
    //!
    //! @note
    //! This method is not tag-dispatched, so it can't be customized directly.
    //!
    //!
    //! Example
    //! -------
    //! @include example/monadic_compose.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto monadic_compose = [](auto&& f, auto&& g) {
        return [perfect-capture](auto&& x) -> decltype(auto) {
            return hana::chain(forwarded(g)(forwarded(x)), forwarded(f));
        };
    };
#else
    struct monadic_compose_t {
        template <typename F, typename G>
        constexpr auto operator()(F&& f, G&& g) const;
    };

    constexpr monadic_compose_t monadic_compose{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_MONADIC_COMPOSE_HPP

/* monadic_compose.hpp
1xe2Y+qj021RPYt3J5nMiy1I9LLaQqk4fDtnca8O96mGcgFrloh2I7AHY13QfogNS66tW60t+lWuEq+5qdTDG5/E2zh5ONEDy2mBmBI6bxNLf99LOniRWWGf0qdSleK9Ww9EjNBg1gseakq2T6xFOCn2+n0lpWI9WoDkeQA4NX+q8CEAzZ8K4yHpgg2LBu0rfCUl4le36+akzqM1BDbXYFP6OPakIL459eE65T9pX+7eMskPZvAoZPjVw14Fq4FI9XMn8qTQbfE3oK5Najkv3GCIzcYiiGx7+8T30w3h3N4eROxGTzQC/o6AUpEygxSMLr8E3yT+FhdoT5mir/aULRLoCTL/nlpIlohczNJ/PLPW0GRIG/k01DWEGHlFU2sYieBSr27hTeRdb+zGXIhhfTW/Vyy61mj4MxY604opRGhAD638uDZicix+CFHe2kiso+5NSYVSfGJBf2MX1yg3uakBsxfL5a1G+O8QDlVVdswot8GQT468xNB3UjleehQQy9KNBs7icNroNV5sJC5DIPnCigwxKP51CJLmsnTzr37xvWiODC6GtGLnIZCmrhZxjolFkldNMUrqgZD2M9BLhlW/aITQ9K8018WrNCdhabWdZ883e8IVZJIN1pDG8sBKtb9f5xkdeVQ3IynWXahvac8nLusZcltXe6c9xuvxrCJPdt2cW85lMlF6sc51uKhNXMiFQ/VhmVCqBSYLf752NhWZdy3V+Q6aSAdVbO8nT7Z1vGPJdbTA9ECqyvyKTcSuTnWweLQavOpQD8OMpGo5IJSVcMHSMI2rJ2t37n2lIjFNvjYb1g0BEzIF99YMfW8Yon7xSGQgvDxNV376LXdnXKnenYSKHUb1M9vn0cLHROXdUQbQZyHMJ7yyzlIvMk2Wae70GaAdx2kul2lIuZBaT0Irk5y7paL8oqPaHDAxwLZfE3VfQkC52GcYD/7tRcbk+QhHzgz0VxAmFXke5N6lsCRnR5rRkiakpFWKY1PR997RUn4r45KMuE8uNOKCiOMJ455gkAUy+kooy6fmPKtxsSNa1Q2HqdNmPX3VIODryJyPHIvfiJH5vKR4tjRax8WcYaNXh9JG6cH1mhsMEMQjRfqhcXDZNYDOQ41iREy02ncPRSJIsZD2Trl+RDKXflG0moZDspuIo/5HI37LEeQwhEBP/b8g2v9Dsv/qIZZxaxT1sNQezeWlFUPa7oV/poorTfqUua191CEEtHSbQ9kIIOzGnSmfKA4Y5CcD4QGTLl0SQ682On0mYkrlUqkyMVsZbVYX6qPKEY8d6IUGEHYgnNdq8babC9IDKyZGG8fotLtYys1XUknbsJdyiGq3fu3tDwj0iTwcs2AHW5qja0neknPAsZg9VIhLJxriPzlv0S8xZYKO+mPq9qHANKPAKSiQ9yXZ4olsLjVyta4RfQ621IP94g3/USWqLUbZF2tQ5JZfKVsu1Sb+Tf7+vv77cv9oeaXDnR7kA7DRJyXrHQOMe0tYCNukrKCsXDpwvdRv4Mz3B5OYo1O0DNAnqs390pCxdscPQ5CJlmEeNXrdb6iv5pRZ5p+txoGhI9PIOTCO3DcyAn4l1s95ty4C2oxNzdaqvnkeiG7TopqzqFCNi0Cok7tCU4A9dfe+Gj++bYJ+H8T9BnbA8eQuH8wib+GHlFsghsOURgD45ULg9AssadntU9sUEjb6N70nsox7BD3LyrXsqt+CW8Zk+nvu5Wp8qZq1DPsyM7FZE0A5Wh1/bFLfBljSt6rxin2ZlrR6M9EtZMXtZVKdnbfsYExVXHB4hCzjtG0Kk65XVbzGFKEqtfELcbVSXrHNK/lVFw7kpjsScU4DumNFL6TwMZ+tlVt86kw=
*/