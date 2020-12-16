/*!
@file
Defines `boost::hana::arg`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_ARG_HPP
#define BOOST_HANA_FUNCTIONAL_ARG_HPP

#include <boost/hana/config.hpp>

#include <cstddef>
#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! Return the `n`th passed argument.
    //!
    //! Specifically, `arg<n>(x1, ..., xn, ..., xm)` is equivalent to `xn`.
    //! Note that indexing starts at 1, so `arg<1>` returns the 1st argument,
    //! `arg<2>` the 2nd and so on. Using `arg<0>` is an error. Passing
    //! less than `n` arguments to `arg<n>` is also an error.
    //!
    //!
    //! @tparam n
    //! An unsigned integer representing the argument to return. `n` must be
    //! positive (meaning nonzero).
    //!
    //! @param x1, ..., xm
    //! A variadic pack of arguments from which the `n`th one is returned.
    //!
    //!
    //! @internal
    //! ### Discussion: could `n` be dynamic?
    //! We could have chosen `arg` to be used like `arg(n)(x...)` instead of
    //! `arg<n>(x...)`. Provided all the arguments were of the same type, it
    //! would then be possible for `n` to only be known at runtime. However,
    //! we would then lose the ability to assert the in-boundedness of `n`
    //! statically.
    //!
    //! ### Rationale for `n` being a non-type template parameter
    //! I claim that the only interesting use case is with a compile-time
    //! `n`, which means that the usage would become `arg(int_<n>)(x...)`,
    //! which is more cumbersome to write than `arg<n>(x...)`. This is open
    //! for discussion.
    //! @endinternal
    //!
    //! ### Example
    //! @include example/functional/arg.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <std::size_t n>
    constexpr auto arg = [](auto&& x1, ..., auto&& xm) -> decltype(auto) {
        return forwarded(xn);
    };
#else
    template <std::size_t n, typename = void>
    struct arg_t;

    template <>
    struct arg_t<1> {
        template <typename X1, typename ...Xn>
        constexpr X1 operator()(X1&& x1, Xn&& ...) const
        { return static_cast<X1&&>(x1); }
    };

    template <>
    struct arg_t<2> {
        template <typename X1, typename X2, typename ...Xn>
        constexpr X2 operator()(X1&&, X2&& x2, Xn&& ...) const
        { return static_cast<X2&&>(x2); }
    };

    template <>
    struct arg_t<3> {
        template <typename X1, typename X2, typename X3, typename ...Xn>
        constexpr X3 operator()(X1&&, X2&&, X3&& x3, Xn&& ...) const
        { return static_cast<X3&&>(x3); }
    };

    template <>
    struct arg_t<4> {
        template <typename X1, typename X2, typename X3, typename X4, typename ...Xn>
        constexpr X4 operator()(X1&&, X2&&, X3&&, X4&& x4, Xn&& ...) const
        { return static_cast<X4&&>(x4); }
    };

    template <>
    struct arg_t<5> {
        template <typename X1, typename X2, typename X3, typename X4,
                  typename X5, typename ...Xn>
        constexpr X5 operator()(X1&&, X2&&, X3&&, X4&&, X5&& x5, Xn&& ...) const
        { return static_cast<X5&&>(x5); }
    };

    template <std::size_t n, typename>
    struct arg_t {
        static_assert(n > 0,
        "invalid usage of boost::hana::arg<n> with n == 0");

        template <typename X1, typename X2, typename X3, typename X4,
                  typename X5, typename ...Xn>
        constexpr decltype(auto)
        operator()(X1&&, X2&&, X3&&, X4&&, X5&&, Xn&& ...xn) const {
            static_assert(sizeof...(xn) >= n - 5,
            "invalid usage of boost::hana::arg<n> with too few arguments");

            // Since compilers will typically try to continue for a bit after
            // an error/static assertion, we must avoid sending the compiler
            // in a very long computation if n == 0.
            return arg_t<n == 0 ? 1 : n - 5>{}(static_cast<Xn&&>(xn)...);
        }
    };

    template <std::size_t n>
    struct arg_t<n, std::enable_if_t<(n > 25)>> {
        template <
            typename X1,  typename X2,  typename X3,  typename X4,  typename X5,
            typename X6,  typename X7,  typename X8,  typename X9,  typename X10,
            typename X11, typename X12, typename X13, typename X14, typename X15,
            typename X16, typename X17, typename X18, typename X19, typename X20,
            typename X21, typename X22, typename X23, typename X24, typename X25,
            typename ...Xn>
        constexpr decltype(auto)
        operator()(X1&&,  X2&&,  X3&&,  X4&&,  X5&&,
                   X6&&,  X7&&,  X8&&,  X9&&,  X10&&,
                   X11&&, X12&&, X13&&, X14&&, X15&&,
                   X16&&, X17&&, X18&&, X19&&, X20&&,
                   X21&&, X22&&, X23&&, X24&&, X25&&, Xn&& ...xn) const
        { return arg_t<n - 25>{}(static_cast<Xn&&>(xn)...); }
    };

    template <std::size_t n>
    constexpr arg_t<n> arg{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_ARG_HPP

/* arg.hpp
90CiqwhPH0VtHAZMfAELe4TATiLYIwV2CsEuBezpaPeOOpIDaeMwtfEUKbvnbMACvgVgni/lYE9D2Q+hjYVU3zOkvnriy7Mi34JgzxHYILX7PKlvGdX3ApHJE2mM2Ne7yPdpqOyL5HtfQjxg/+8i38+RshfUaP/OzhQm4RFEf5X56/n7e2l+Or/i5dqvQH040YWUdfPenXlfNnY36OWWrlyCsrIkciqgWn35Yrw+6Iz5Sx8NmsfgZ+La8EL0Jq3zYa5QdTgkjMxy6aDQLBea14BGPeSbns7bM9xnC+4NwBUqaHQG3k8BBz0Om6fbcIwzM4Hk6wydvX0zaAdmOo2nNJIfY5/rLSaOoT4mk8Xl4eiLzWzFSWM6Y2Tp0Oys+pubVK+Cp+GJ4Js3JOsDfioDgsw42AJK2Mvo4cPgs2k/lOstqDc8DmABVVceaVI+i6xoqLwwC3w/UCiXilP4qLq52h/Tr2TGO2DrfpulZ4ISjrWqm41Udyp1c9St/m2WuHRmZgbPIkgciegP1ECTqYGG6oEIRzS19S2XP3K7QkN8vzJZp3rCdVoJokqIx7BaGXsPaCGk+wSuClhZPXexXw+SpavIw/tRD1qB8z8THwY9T1ke4M6nlXMHB013SG0hT+ZnVA4Et5s1Z65aa+1LGf/EwSnmw9WWV0emlbGak3btnLKH/1SxSr8+pkngM1XxV4f7g3lN/K4i+XzO5MbVpq+i9FRUpi7i6QfpOyrqGoyD+FiZyTZAo/QS6dBrbBm5XMrTOxGPPmLpfH7iPMvc41MXycFHgZcPq1tK5/FUJZhuCu7eHwEtejRRqEC2Im6MzxaN9gU/qHxGP7eAuC+IaMy4biZI2IupgL0ImG8HAubbgQ72abEDzyUY2YGA+Xagg92Asj9fgvWeyrLNlwrYfKmAzZcK2HypgM2XCth8qYDNlwrYfKlAXDfl23wEuxGwUwFYoWB+/JdgXwrw4KsMC9iLqYC9mArYi6mAvQiYbxsC5tuBDvZ17kvANkz5tiHV9z3A7g0eNFPZHwnsHIKxHZgK2IGpgB2YCtiBKd8OpDaeBJoy2l1OsJ/yt5G9+FoaN99eTN2FeGn0bywnaaXpJV7q+XTviNmMjUl7x+Tz6xpgv9E6Qvs/SuvI7glo5qxDrZI4F0Y0heKB0n7vrv6btU6bTqfFJozgpy8hONkxT10mOYGi/wJGktWHv0TdujG+HyNaB9SSms7bftzKcLLzbnd6WbWaO1xUL7FpSno38Yj0f2/vvKO7KLY4fnc3kd5DSei9SOhVKQIJNYSQhA7SEkI1EAgI2OAJSpcu0nux8USKIGoUCwgC0hGQojQRQURF2vvsbwYyJivv8d774513sud8zyZ3Z2dn7tw2d2Z/G8MPqPypfA1d/rpph3WIgmegqBsdaKudfKcR15i+iN9hwOsQUw00vyXWGx66t7vPM2najqeIH3zUv4xzaIy48f4p6KcBnXOfpj6oR/2mvBjuyxiWP8sLb13z5m5cfLJP7u7zPI8Z9aSOGfTKgGaQ+45h/P2f6Pv5z/W7ayYpKjf9/G++/pmdMO9Pse8UHsTqfad5jHfg1RvMih6UQm6VJsTodR/ven1lGN175czvo7mZ7K7NjDjmQXzxdUD/zof3PGaw7+tMQ/i52QR3mWiwOx7J39bWa7xD3GK6lNseM5Y0nsafvimY+hhNrCsdeuuk8b52yntieKuUuvv71qYS4o1Y0oMvphpoxhcy+K7nk6qUKiRmXHrv22X/ihym5iW/n0DMlSzPWpYQkxTS5BVrw0RiM8WOmNSziL+WMd8vAwwwvk9vyph5zbjftW1k2aNUDanjrobar7gfY9jBXdkkmWbGYpo=
*/