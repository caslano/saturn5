/*!
@file
Forward declares `boost::hana::when` and `boost::hana::when_valid`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CORE_WHEN_HPP
#define BOOST_HANA_FWD_CORE_WHEN_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-core
    //! Enable a partial specialization only if a boolean condition is true.
    //!
    //! You might also want to take a look at `when_valid`, which provides
    //! similar functionality but enables a specialziation only when some
    //! expression is well-formed.
    //!
    //! > #### Rationale for using `when` instead of `std::enable_if`
    //! > `when` is used to control the priority of partial specializations
    //! > in a finer grained manner than what can be achieved with the usual
    //! > `typename Enable = void` and `std::enable_if` pattern. For example,
    //! > a partially specialized tag-dispatched method will have a higher
    //! > priority than an equivalent specialization that uses `when`. For
    //! > more details, see the tutorial section on [tag-dispatching][1].
    //!
    //!
    //! Example
    //! -------
    //! @include example/core/when.cpp
    //!
    //! [1]: @ref tutorial-core-tag_dispatching
    template <bool condition>
    struct when;

    namespace core_detail {
        template <typename ...>
        struct always_true { static constexpr bool value = true; };
    }

    //! @ingroup group-core
    //! Variant of `when` allowing specializations to be enabled only if an
    //! expression is well-formed.
    //!
    //! `when_valid<...>` is always equivalent to `when<true>`. However, when
    //! used inside a partial specialization, SFINAE will cause the partial
    //! specialization to be ignored when the expression is ill-formed.
    //!
    //!
    //! Example
    //! -------
    //! @include example/core/when_valid.cpp
    //!
    //!
    //! @bug
    //! Using `when_valid` seems to trigger ambiguous partial specializations
    //! on GCC.
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename ...>
    using when_valid = when<true>;
#else
    template <typename ...Dummy>
    using when_valid = when<
        core_detail::always_true<Dummy...>::value
    >;
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CORE_WHEN_HPP

/* when.hpp
wAl4NFrQ6t2g0SAP0+hlMi0oFp3YlQaQ/Fjj0CmGvMfA1shchM/JorDwmOyty8Tmai8XZUMmD73kidyLBwqQPfApW8Y5RNw/zpSWVONgl6ZOvlBW5JHT0FbCpILJz29HIwzVotVSty5S6kDVe/syKTAZNNfoQmKN3GekHZKmlk952XFiksuJ/aAnMbNPMs2fzLgqs91YQXLLnjaxgP3Odwrrt7z/7Dx9z9GqXlautd3FJdFt4cb26NVOrNNOrDOH94YXHUbq4jkTlaYG9TTyWAKFr0f2VZd8+aZOE28+Sl3mVq88hQfiou0UXtTI/75C/wYh1RorcLA10B8OinRIa8+Sb/dqkDyA0lVAOdElK9v41FGpXudO5bBtZCuKnaPXMse5b84P3OpDYCSkNspTm5m7WMS1eW51oMAJb+kSJ3bMpQbAR3mVqp4BBI1YveXvM+2A3Y1zn9JkG9msoJyK30Ehr6mDy49PLaz/CEkLtAmrxSadMp+1fs7mOWPc+c1F73Mn9Qc3oW6h/dMyNblMrhi9U6Xmku9XgzVKl70R00cYcqZ9Tmgm5m6cpuE3tcN4Cfl94nihj8xip4rcxkQpjkURppQfKs2CUuy3e9RLHdKkxMGN6lE/ypOWFM9MiSeZu2aIVvWoG7qyqmPRjjaIBwPoYSx+nDDj6JsIO6jDvlKD7QXcYh3ufAH3uGy0jtoeBy0J8l9agnyXEJ5B4SP3mx6brNnbYVp79xx9wSZ8PJ2tMbwFfX0f0nol24aVy2/p7T6xcpkyXFu58F6OMpKdfWiyiWXRx2zCuJ9MGPcnVXTFlJNtqLA2s2rpqTOwQ5Au3pvwXlT/XP8ygx0Jy22j1oSW5BiPd0ej7f20136g2xMCpLAnnHy5HPBvnCHeFJR3VHvCPJElsirbKO0Jf3ZGW5aCn2AKic14bZupCiaeHHvC4RfH2BNW9Bb2hJuuPB57wmzjSbQn/PO4qP1c6ZXCfq4xN8GekCUwxPdry56wboC0JxxjP357wgEx5b81SZQ/Mlq+1n3qD1xx9nvNjrbs967qIe33XrCdqP3efWOj+JRo+Dzd+wh8Xp0Yh8+gNvE5bbTEp+CE8bGNjdoTPumNsSf8uSvGnjCzd4w9IdOHmheLoUe9s29b9oQ5l0h7wmWdO2BP+Ohpuj2hLKZhQpw94Tl927QnXCnWI4XMpFGTHFFarD3hBB22VcL+0YQ4e8KNfdqzJyy7WNoTNmZ8z/aE14+O2hMqvaQ9YapHtyfMMcbbE943QE47SX3aMg5861JhT0hNoGWZpWdZf3pbWYaXxdgTNlhP0J6wbqA1Yb2ekbCeT4gfnBA/KyHsS0h/T0L4/oT0BekJ+py0BH1KQvwvEsLvJMCzdE7QfySkv6tTwnybEH49IWxIwP9gArzC2PQx8vW5Z8bI11+7RUC9v//Jka+LL5VT41O95VutO15YqhzZEfl67yUyv0+HdJE7Kl8PHvk9yNdje0j5+ppL4uTrdwR/wNujl8fJ1/VjpHzdlPZ9yNfeCzsqXz94sZSv95UmyNd13pMkX+8o7rh83ZKdKAPf0ktylrLSeJL5plDKwbMtHZGvbzsCdl8d9n5XVL7+tQ4323KS5WuXLX48VieEtyWE66Jhed4dM//s6XghG6mSl8iMNezCPVTs39O26hKjbVVSw8eWTmttq0ZE5MthfgmbuzeoSeHLzSHrErwHW3PnvAlAWQA0LAqoozDGL8llIPY5b8Ct5ezjNxZi/S7ffwLzE6oQ0UhOmTJuujJL8JI8pXQ2H3zbGHCiC7vfHvxH8Y2Zy0alF444zzSydrRhdHCHseKrUOnsmohw+YkEFfbmEsYmWAK+YYqU4ABfuDQ=
*/