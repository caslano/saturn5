/*!
@file
Forward declares `boost::hana::while_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_WHILE_HPP
#define BOOST_HANA_FWD_WHILE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Apply a function to an initial state while some predicate is satisfied.
    //! @ingroup group-Logical
    //!
    //! This method is a natural extension of the `while` language construct
    //! to manipulate a state whose type may change from one iteration to
    //! another. However, note that having a state whose type changes from
    //! one iteration to the other is only possible as long as the predicate
    //! returns a `Logical` whose truth value is known at compile-time.
    //!
    //! Specifically, `while_(pred, state, f)` is equivalent to
    //! @code
    //!     f(...f(f(state)))
    //! @endcode
    //! where `f` is iterated as long as `pred(f(...))` is a true-valued
    //! `Logical`.
    //!
    //!
    //! @param pred
    //! A predicate called on the state or on the result of applying `f` a
    //! certain number of times to the state, and returning whether `f`
    //! should be applied one more time.
    //!
    //! @param state
    //! The initial state on which `f` is applied.
    //!
    //! @param f
    //! A function that is iterated on the initial state. Note that the
    //! return type of `f` may change from one iteration to the other,
    //! but only while `pred` returns a compile-time `Logical`. In other
    //! words, `decltype(f(stateN))` may differ from `decltype(f(stateN+1))`,
    //! but only if `pred(f(stateN))` returns a compile-time `Logical`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/while.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto while_ = [](auto&& pred, auto&& state, auto&& f) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename L, typename = void>
    struct while_impl : while_impl<L, when<true>> { };

    struct while_t {
        template <typename Pred, typename State, typename F>
        constexpr decltype(auto) operator()(Pred&& pred, State&& state, F&& f) const;
    };

    constexpr while_t while_{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_WHILE_HPP

/* while.hpp
I8akMz6MmKB5VvLkLrW7dSVmuvjJBdoj8oKaqHI50UK/aHGphRU5PvobbxaRap/m8KB+C6gPpw+LswQPLlVMVZ0sHxH3B7FC52QlHSWTqquYXJw9K01vpCFC4gMhWbYPQfHcx/9kx7B2Tey1rnoQLnf5lgQE1Fb30nesXIitHUybGV4fwUMCw5FoULxANIGgEVid2qZOEot1SzpHEoHqpW8fBu8u3lgwiToHUTXcI1dJTVfD1tfaQSYVO5lorNj7CbUCV1yJlInT9rTwAWGJiLPgzqML8dAHSNFK2ql9rAbdW9JVUutc0QOdkKx0UHnEJGEwpzJrw4PZhBCS+P0FIMv51pO85/fl3I2VaBh1S0jLzeqVJ/5qtvH3hp5bIbURvGJyHw8woqTsnnaOWues/AtU/oU/IaqvNOUxwZsPNai/jjA6tgKZPkmsA9brO0EcTuCDN5zGyp5UGcNRD2tqX94lA9Uu+bAl8yomFajNTqP8RZ3p2GFGE2NwIRJOk7Pv28z0/86flD+PGyjvK7F8vH5qw3LQ1Wr856iG3TceL0TFPqQkY2gaUapm15gHyfkS00nmxECH2s3E5R+o4R7R4ST7qRl/KEbOIV7a0QJcn/1pi2LeQK2nNnQw4UQRchZtkKh48xp9Te23lS2nz1eOwYYBkmZevsn8XdHWIH3InE6Q/QBxMVCM93mv8XbRO4agci9dj/xSCJaKDSR1sb60hGPL4uClRlLZeFnT7YpP+ThPnS8voZM0FrxKEZu+U1wHpDZE9/Mgj7svV4neZ/FlRTGui1Sb9UoqbZybVIJTGR+ixUNSH7Gip2JACkTuXkkyYofR/IyIK3xS36xYjONUHqXVdMobOkuWDj+OJkvvoVyD3vCvVWSW/X+/n5olBQBe3sOaZCJ9QTP8ESMmM/gEEDEFoVShqKCFaTbaHhIDvkqlFE9wk1rf5U2BHZIneM/D6yUOBmQZQHy8dpoo8cQ/0ksdEWkvwIcg+FKFxpIkHushtyEuorzvEvqLUwCNsZa7l7yIoBpc0X38U0LmLxEVFNZMywQrKYE4F4clg3MtbhKHjrFZrECfXxFY/A+MgGO7EkYtYoWa2zspGdy5YTEnRQs+jBhkUeiQ6PuuwScsrOKLkQZ1bm41qHNseEeUGeoB29RUNKkyvj4W5ETEMZhu2jrViXxoUeRoVQJuMKH/OqQ4wE9ykTQMd/INmp/6WtPDcA2PzLE+tT05OiwesSvPYUEx1SElXLRcWom41UHunKOE0Q3ipM+Mpees5RVOLFDXc8c6kzlL6xcdju1BM0ZguGLh35EI9cvuhrhOakZ66pKFhJgo2GMWHB0oMy1QmaZ3l5zp1+vrfd2P96vQ10y0euKDeb9a5kwNJxJibLHu8KclL+HoWc1TE6058VPFUTkUjLCu0bmGKKa5ijehLUyQf4VJZWy8Y+Oi1og4AhY0wEH3s6vNzhERkS83iqzbical5UtvyWbGJXMaFhsL1TWQb9reVVVn8HmY6a/P8vtmtfVfkOV/IsvvPbOt33JWW/9d6XhT/xEYMSg1QowG90aKgMX4ar93UDs12hb6rdzMDpuGIXHiBo0DuxaHjsdejB1MJ/1EoGAHGVbtPL1t/doNqqKoU4zqnx7M/tpvzJgyrbNV7v+kctb+lG2VfiAG9Sg6RwXDNZgFwGhdbUC2LhyQS8vYZK0SnUCUSwep+5cv7CBODqSb9OJImuhpCIqXvWrmbQ+KH3VVnm24qkNyCDrpoQtGzyBbSt7DcuQth4eu2y930DZITEQR9vooBL9WUSbvPX3TXa1G48lClCZ12tc+XjxwZMfaMogHfsj8d6v87ePF3P3mZ/wJi4JuxNF/6JI=
*/