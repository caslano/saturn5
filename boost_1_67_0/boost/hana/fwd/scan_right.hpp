/*!
@file
Forward declares `boost::hana::scan_right`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_SCAN_RIGHT_HPP
#define BOOST_HANA_FWD_SCAN_RIGHT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Fold a Sequence to the right and return a list containing the
    //! successive reduction states.
    //! @ingroup group-Sequence
    //!
    //! Like `fold_right`, `scan_right` reduces a sequence to a single value
    //! using a binary operation. However, unlike `fold_right`, it builds up
    //! a sequence of the intermediary results computed along the way and
    //! returns that instead of only the final reduction state. Like
    //! `fold_right`, `scan_right` can be used with or without an initial
    //! reduction state.
    //!
    //! When the sequence is empty, two things may arise. If an initial state
    //! was provided, a singleton list containing that state is returned.
    //! Otherwise, if no initial state was provided, an empty list is
    //! returned. In particular, unlike for `fold_right`, using `scan_right`
    //! on an empty sequence without an initial state is not an error.
    //!
    //! More specifically, `scan_right([x1, ..., xn], state, f)` is a sequence
    //! whose `i`th element is equivalent to `fold_right([x1, ..., xi], state, f)`.
    //! The no-state variant is handled in an analogous way. For illustration,
    //! consider this right fold on a short sequence:
    //! @code
    //!     fold_right([x1, x2, x3], state, f) == f(x1, f(x2, f(x3, state)))
    //! @endcode
    //!
    //! The analogous sequence generated with `scan_right` will be
    //! @code
    //!     scan_right([x1, x2, x3], state, f) == [
    //!         f(x1, f(x2, f(x3, state))),
    //!               f(x2, f(x3, state)),
    //!                     f(x3, state),
    //!                           state
    //!     ]
    //! @endcode
    //!
    //! Similarly, consider this right fold (without an initial state) on
    //! a short sequence:
    //! @code
    //!     fold_right([x1, x2, x3, x4], f) == f(x1, f(x2, f(x3, x4)))
    //! @endcode
    //!
    //! The analogous sequence generated with `scan_right` will be
    //! @code
    //!     scan_right([x1, x2, x3, x4], f) == [
    //!         f(x1, f(x2, f(x3, x4))),
    //!               f(x2, f(x3, x4)),
    //!                     f(x3, x4),
    //!                           x4
    //!     ]
    //! @endcode
    //!
    //! @param xs
    //! The sequence to scan from the right.
    //!
    //! @param state
    //! The (optional) initial reduction state.
    //!
    //! @param f
    //! A binary function called as `f(x, state)`, where `state` is the
    //! result accumulated so far and `x` is an element in the sequence.
    //! When no initial state is provided, `f` is called as `f(x1, x2)`,
    //! where `x1` and `x2` are elements of the sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/scan_right.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto scan_right = [](auto&& xs[, auto&& state], auto const& f) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct scan_right_impl : scan_right_impl<S, when<true>> { };

    struct scan_right_t {
        template <typename Xs, typename State, typename F>
        constexpr auto operator()(Xs&& xs, State&& state, F const& f) const;

        template <typename Xs, typename F>
        constexpr auto operator()(Xs&& xs, F const& f) const;
    };

    constexpr scan_right_t scan_right{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_SCAN_RIGHT_HPP

/* scan_right.hpp
DrV/LK02dKN4K3fMeSqNmcf3ro9CtypY92PdeocV+ARu30hp2LWGU2L0gSMVryrlcfOfnYBS0AtEiQ7EMaRtu1m0OagkGOnNB3gbA8+fxr3ROouhFhhWM7faZULhuurBIokRRm05jSVVRa7WwwoY2AEFc8Drvd+Rfrb25xjTfIT/A8PBwioTe4ifiTpGHQhQo8fvGPwDAOA1Yh5dGIXqdwbXeOn1qrAYVHgnIhX0LlPjlOBY22jIYJPQvjKxctEfaEEI1hoh387xJQcOKPG0T8vAAEC+MrAvm69ZucNgPc9PevAt7XY2QSJbG2BpC8z+EIq8mqQcLtgSn91vySGrnrCPRhkJjMG1cYjmAm/+Xr+gim1jHjn1YtYDoBsyqN9aJG0cUwpkChJcktgIv5/Ayot4ojXkE6G+L+tFeyyrkKIdicxn7NworM+1TFEUz4OxaCBgSVvxNhvuyH4xPf0TT/oEZL6Zd+NFg6/KkTXbHEM+Yh6jPEChP5efFe11ZNHAesoxw2SrOQt4NhfJ7KoXM1/sZOcTlvtfWKjd1uu19WB/df8G1q0LJChxmshALG52hsYsbVPGpJdRgdQmaO3Z5U6W6k0WmYr39mYZp/zJP8TBgATow1SDBmMvXfiMK6qNaR7M+9al+IFlNbHOE+HaWDFLuTlgAXIr6n6NLU3OdAP1qmAyHpq36gLLDhXbBnMa1SaqKc4SC3nFL9g+YNNq9n5mUupxvzh1I1QzJsQ3NztIOyG7QIsbRprcy/zHeHZ1nVhU6emSMzcOjEiaY2hY7C8MDoLTbvqXCnTYDRJIDCICXKdKN96mrawtNReweGFnchJ/8BTX5AOrjiXLfGcknxH1gs3+J+6J8CS/0txpZpEzzPlcR3kOmF8Q5uYCM8goV7m2o5Bg1srUbzjQYwVMQyOIF3RRnEjUHjNig9z1nT++qelNgv7Z+NiDlBOn29oO+RQaRU5GmOighoyVMY6AWHfFGy52v/Sd03cjkfreoOk5QK2TqC+9xtvL0NvODOlqHPfnAMvaDNqlZMryEQtqQNG+FBgnBrm90S26RCTmu2rHHFS0m+RpFkKg0BPijvIGG5yGirvRtwSFElFmAD9U5FvbaOs+J5AbES7RWPioamhXE0qIzYW3H7jIOTXOzM6J1vHZ5VdseHF8S19sbHlviY4VY4nr+cLR51Q2cusM+Vws6IrfgQBaLkk6bwH4E+SP+2O2iIFpp4Kn1aigFe0d9oQfWEgOQZBPmNhx5CBcm1E3pkrWl1+zoEL7UR9mTe9dNFnUZm+qMpzhKSxcr20kRuqurEZhUCF0sLE2K/2JSjE1GyOZY7YsTTl0ydXSGmRkLxTNn2GFX7MoXeIabffKJODm0PhJrnu7skwdOk58Kxry1AJx+uznbPY9hanhzWvT4xWhbxB3s/j5kykghI9V7XX0LeM/sgxaZ+YgSwFjTEt56k8ZUtKX2VwQHAfcSXms/mCO4PkCpIbkFWqHotzTeDluBn0W9OZ6f5X6ou8L6+zc1KUS6CI2/zDqgfYGhBsBhp5byZ1k4cSWWbYVOssMFCkE7cuOFI7melxMw1bfEkL0zYRshtz9VurrwJaVedK20AD1D4tPrckIJ+O1BimzeMPRiXyHZLEE4+1Vh4Ux1BWaWwkp590PogwSJujwlHQvJRbIuz0Tl9JJdWRFrQ6HU63vs2nqv5FCEDC2QEqjIjXHEqlsw+j9wfVhocYRGsfFztFc5wrqtznBoUI5saGHF5r/H4GDFTjwdSITq6hbqwTYTOn+iuhji/z4XPzSTEbZzUgrPVsHPjxu/NWgmYXbGeSk2jSO+iBwfOo3Xf24rUo/XyMv+v3CJcfIeg/AVqkImTsSydnaE+JnLmz7Cy60ouh5Sr6CWz2v+uNOZN36fY93v9NbjYEZfZ7jIFwlRdJJMKkjq9FvYntsCX9HDQELkQU7u4Xkdbq1v11q7+r6tDSv+iYPOyBHoERri1e3vQwBQt4qu6+PkzYxYxxr4OCxyl7exkbUIRYN5tuVxxLoL4fdYfahbCVMHSs8YA9b6XdhDYOSQAcsY+ZUhj/x8AF9p7p6vXfRnuGwXoZabgEwyfMYB16JW4Epv7Y5MomqobNq+DTjCzRzgoXh3HDyX+L10hiUMDFWGfY33KZARCiDEazKrHUFLeD0Ez7ZvXVeL47u/OWT+W8pE34cC59jRiU5sdR1OWMgnurwDdMU82VcBXnrn5HyaoEiAvJXgYoehBbvmHVyYWsTJgRfDrcGn6gE/NjVsWO95gojU51ruODMhspZE0F/b30SviyjxfBS+3bfCYBgWSpj2Iw2VtdC1JfNcRo4hpFIzmLkbOMZySX/BTp3C9J87hoC+8HsLF48hiSLroZPgVfA4iikUBtWfOetRAm9HgFjeQQUiKJWI8DJfUqaK/f39YvoqugY9uZz6t+62wqBps2zr+icR57eSdt9zf/r6AO20Cc/t8sviengNSIjJxBfZkMyHt+o4oAjSS8QVpll38sYptBgj3G7U+0TSnRodF89fazygpLqC9eK7g/qwg1n0XdUzF7EIP9mER8om6eNHgcpvetQ+R/wyTC3MlZ8YSDqTz6GDAnziTbwUsrTm6LjZuEHQkZwfOvorEBhqrobwquHP7b8gBwP4Uvbq1j6BBZBF3hM1QJVjAKesqorYD0EiLkempHLpEk/2eRKvkg7mL3yivjO2+SWQZZH8dEyLNHLeflP3nMkTUiz4c7OP10A2n58v/PwHLUAnZ1s27eIPV/qKWxP0Jr7TULeQjhEZMolWo0Z4Aa5XzCRHVwM8yXwu6Fha9SV2E9cNhBW/PpFPmcYKuprMUq55jpJMbHuGmLq7iqZOdGFOGbWJRJR/4VlMCgTVRIAneZER39oU6S+1pWZTMm2e/dNlis8fiJB2iIenlGlrkLXHHzFBsqkXqmkX5r9HqMfs1sQcuC5rdCOYmlOdSaKdqNFHbamk3vIBp7KKQepbaRESYxyYAB3y4DagGv3x13k02CQKHfX8DmRgA7mO0aKLkACa757mAAR14ijaXvNaA/EMz3L1/Q2y2OrXgeuAesu25hIJjUjHaqR8TUFrkoWIdWjZpgjPnFlqs5pjbUOI1oFNzo05vW5llZMeQfBPN5S6za+55YKxVVJq1KY8s4HVhx8tgPi/IwIi+hr6hgYubJSwJpDdtPlJoaZiwMrl5Z/A8rV6PbGAEj2pq6tWxltGiboQWNcQqkR0HsGD7Wrzu5nNzU2xylPeX/9PxRKB1Vv6GVKkKdLtuUJMC6v5YmBI1cgCiQYyb2iFxNFHgq3K+Qj8M9aWlfnImhCIjr+xarm9BvQCGicNmwy+XrKyj+vyBH5Th43zKlUipaP7KrLi0AX9OLAC6XbdVCy3iQgLrPK8GSWozs9rAdnoOw0D50SSOW5HT0Car4n1rKROLqa9Mzu8ILzokb0bUJtCA9oz/+YhcknacIUYdUEZuOudyjVEKcBcNmLxkjn/jvSRCl4AiHadQSzLJNWxbzQ2XgLLAdvsB3aYGJClEM5exhk97Y8yir+IcsHB3Bl214Gki2lfsSzWKmPL+jLL2u0Xeoj4ax1V1kwiuaTOCtKrUIiRwPu4qEM6X3ivtwKfVrMg3hjPiLwtWZtF6pDCZDoqpHhTLgaeRe6vvgsYWE2Ft+U6vo74Kv43tV2RNuvxOvHOoeri0kh0ubjlOEUKkiDKeQVlBLUCGfyJ2vq45xJfXeAxTikC7DjwGFQwCpWQRcr24LbVIkGqLe5jYZ4ew12Vdjk523jEHvxsgJnVVwWoswUc7uio8MShBx31b3BFK9omUnz5+71hgVheKA5ObwPJQyN2xBOb8ZvrCg4sSLDEhHjXyvCnG80cnGEHdZeL31Crf7+nQR2COZdChn/6ZUKgv4dhIma38FuepVlIqJ4vXZs037qIAhC+oW5E819pS8IMvQ7z0x0trA874vBs5BPPbhR0ejj80JlGUK5UMNOscNRL87P7nC/jJCo9kITY4/ETTwuS9CMOQ2cP3fehpZ68wEKt2hgMS+3rKqcljI5qGd4UyMZiTN/dWnTP0cBkBWvREkXV3G3HNKfPCU5GlAaR7jybMxl+6rMQEeXq7PdGmMLmHoPvVOxtKl6P1jTlIjU4zn+kHn4b4StJiSCGmxatKOOMbdvDXcJNwv4K9w7hr/iUzbhVfAjUm/5Wqk+xgfMfRPn5/Cq2vuxf1NfwbFX9wmcBvJAwYQYsowI1x7DABYI+WxBVmgfzgu97eZ8bd5heNorPyjWjoyxjmlwAL5iautybUiy0h/Ybz0Qr8VPVSX9AEOCyApKWdlfPHM5W6R6Q2H9LJ3R309wlcSJkFm4uDE7A+YejQIgwmmBsCDK2FhWc6tgVOy+dTjOQzjhkOaw9WL5YTBysiLkytHLm4blp3xvJmJAgy4H4+vwtkyXURkVJJ6El4+8odTd1W6PjRiGQTeL+UGnZlJCZUW6SDtEiUVmTWZu/TA8/xUeT2QdJROnYoMjImLy/OC+hj45Sgl0hsi196HGtpvRVZSKP8mMN+rbn7wIixiADVmtdPq/QT7mZwJUFnUDfOgSUSHWc0q0NQV3VCD1yeZIPHWZBFnl+Fs6Vuqy4lyufzauBa2rZ35Y3zuDIdomUKmh+U7peWbAikZndP6nNu9xiEW06VzrF8Ju+u5TYD2hOjL5F+qh/MFR5td3xuWXje0PUuCeRZ7+GWP3zhIeJHJJXLt4QKRM2jN6flCGAX8xCRI0JYHazIY1CBJDWdbY3rNWuejDYjulTSFktD7Qek+0X6tkSUQUH/dECqBp9O+wtNlwkDrn7FquLr2PAmVyLQxv28sJn8TX6d+ZJqCrQIqa8fNuJjEK9p94XrAa8EX47UDnPOTozY2COq2kT7J7xgc7QM17dBRk93drDZ6SqbinJH3ZrTsno23q/I372Yo4vfGQBGI5l+71hHj7erShrYoxKtkGRPLVKFQn4s3p9Gmnpw+1TTYDnDvwS0twF962gDzL1YHgLgvhoxez+lD/Y9399QK5ymLdlCacafQsHb8L2tA+mU68vYyXwNSfbIrbOykRo9errEOCOcpIW+ZDGcovH3s51d804DZQxNyT/AH2vRxOLRZPBnhjOZyL57r072LCeZ/cUlvW3WPoWJFb9OAeV0uRbiUtqqI5mRc9R0Du8rhETR8kL07O/85Gszi/a8j5eZnnHodXhBQrq73JIP+fXjHzER17q5w+OVq+9SCUstJhYIidJLeKvzeMh272XQZLGINZegyiD17jFySen7f++GTbx6OOOQIav1U+rG/1X3U1U9G1jDDHge7mzIgTbHrrj6IGcAxnn0EWlnSUVkJDHMbKPQ/sYVn7ApmaPFI2kJfs76hwSYNhfhGhpDI0WzRZo5ypOn23LWzPRdYM01dN2zAR70c55FYYVFdX2aY0nV4QUVTyiBxoH4rKBD8ZssUwXESEMJT3BPk52iXWyZaGBfwOH158Jy+xIKSXOHuGpKAOZv1XmeIRtxNafZOyQ69FllhvcS/kh4lALgWIjEtBRDJ06x4grYNimfEE9GngaShk+JHYor8CAKSQl3PQS0v7rmqdVrPkD4eEQQg0sqqQLbPM40jLxwuFNz52ebvV5YXS2FalSji2S415WsbtmJyfKx2rGZRoMvlmdZ0iJZETo30ozp00dhd6/xaWskj35Jx2K2SLbzNLbc6nX+Ly+Eyf3TsK8aItNTF+MuW0E6J4zh0ea3oMfnq9PKxTn9zl/vQdCLkclsQf/91jkD4+Q7buDvTr92mfyT/B6Un8AVdpBhzokkY1y6wsvk+LixG5BdB2A7wamC4hHo0cfwsh0vOxBJkTSnHu82yISobhSuoFlB4zLpC+8wsZNvgWLexlnNBUgXd2j/Xi3sH7hdazm4GN7z3VNnQfL5xDkxwi6YxxbLt3xjuJyESF6nvmUd27FO3pdzBWiVlQ61ttkIiHi3FC9owYNUHWGwFEqwL5xKHUBqsH3wZ9AT+wIvW6RtACKGMYKDGi38jOsDxCZT9NDL3SYn3t6/sxT7i74N4Hhus6bZcKjCsFtEWT7UteXPTQ+vOYl4ASitX9DBH3ZxUH7bM9EwK1Uh5aABpaFcermr7oHK5awn92q1STwW4pRFMWdmAsMm6cIHO5PE4gT8LuxNty/pkKciCedNpaVlWsQvJVQiNv0jTVOoj5GgjObFRbslOtGwkSQ+q7awNyuN6oo/5y5SkJLv4FZ/pqap0/q8YDWGJiA07uv5GWfNnTe7YOZ2U6LwvUsXxsAzXny6ESwhtKNL46Lev33nsjBjddo/s75IbJ+X5kzGETzVeVruh8tBPhtwkO2d/xV9vkoNyalybpxrzbi8MgNY4QUPG45m9rQTB9sSbJt4CZEZN739Jxyqk6c6nJvK73j0kmxF6lBbqz4k9JLpqx22HTadwxPxTgsIR9oI18+p2415cPmtKtv8G0sal0v/zCXu37206nwtk/L4iozoPt8B2Pn9w2a2hfHlPxF2HoOYbkUqGxAnEM738DTrmYBH3/uSZ00gmy5gqqp96YUkGJsy9q0owJ0C5sxninore9r9SOiQQXoWaZnGPCLssRJNYSigIKKYuMBQ6I+3WWEIYb82guX1ejOxO8rHjHNkaZwlejyeHai078I2Mf9d9owYBFpu/U88sFq8wowEvazwLx6JgngUww7rWbASeZIM8ZeyIFXtR6hassvl0MCNQPZ3WP+cjiBsuyNkvcTbhtq0bEP+N1Orzh53luUKINbCgXjA7KJUEN56CS2MUqssgkPk+C3aLqfqpyeONxE1Gj4mJ1l3IElvr+dPOUF4WnDy/7vRsRJ9g2uhcEmhWrtTt7Gij3YWrD3hYqG/WtxDTXfJ2QlThQMeJYpBnsjql6i7ZRkjOcF0YFlqO2tbjBZSW2i4IvrFMOYFZMpDHxIpJ1cH0Mt/erd6s8avska5D59ydYdiSIfLNLbXPOB0z3/ro9fw28ITsAOZZ8qcUSCNqGmi+aKe4nYQhdBgrvO8ht3y+f5fIXPWE7Ce+CqNsfjOYVVuW2GbEkDvBOg0hlXRSb0mUfn6A94VsPJ2Syb6hEWJwBjie0kTEwj5+O5Zn1BnY8Bo9zimo68JBZ2GIl2hDOIBAg8VSkWIi0daID9OSFkY0URBqB+3mgGRyGmEFgsT7fCnguOmrei/hLvGj/gD9LV70HoGnCIKj56Vtb3zYkY4RTtNsusQwgdcYhrpZrQ27oh0W8nCYmvFyh8hsWgeV6VozSyOJBcJqgadxeavOgkCkIwq+CQUO47TlorYBNIMxkuJYjon/NKghdZpGpcGuWEj4y3zTXGWy1XzMuMn4HkTBxHz5SF0lIv+1tZvx4v6PZPL9+DtZjpo2r0XWjeD0YvlX3I0Mz893vk04OV11yQzJiDPslrRLZdfwZnq+GK5o4TL9vfK7Rax0oKV8nsNwow3AQka5OA1AB/bh9bPb6OPYEqzL2t23wXpxZtK2er9kAXF4qoeFYmTEicd0nzP4d9HT8KNyu3uw2ItYlxTCWZW0KTpi1Dz5zplDtLqCz8UQrSTP8b9PDRkyRF0J0ZTkUMh6CWNpMeUAF+HZatsBXBTj146Gh+toUpcsKZ8kThsNW4DQ5LY9EBAAbV4CHjtUNeDvKtl9xReXF8cc1cOQqwmtbA/osnAiwjm6u6dKfM3dWC8AJoHUQQvWSktsglAIr5DCy8I55eKZDUoJmH4M6aH5SQPKWiyPbjooR3yy6F+MqyN0S8R0BtOev054iJV0ptybFvzDTVXYZ1Xn+0goa6hZtM3hlEw6FhP1FPg1TQpE54s8vcoGla5hkMbfreZ70nBi8IKOwp7u+W64FTQ4+ElErdmvwWCoNoiSHtjkgEh+pXpa6+6r36q1wo4tJRkefr5zR3st54YNYWrd1xTh3v9fYZ20IKefQNFZLUnaqrfD/ZmBpUiFSdwCEygV87BpkU3mg/Kk6dKKtE6s+krF4d6+WrOmcwMHl5ROI4MXFf2nFHzvDYKY8NaggmDygV97iEx7LYpjb/RKMh+tLEVhcX2GqD3eMWgvICqGYaRTjhLOq3HgymHeHd9haoBHtkJHdLVDkyGdidxNQR8hoPVU8ZsTRc0sOaRW+m5+0XWyuQIcdEkOb/Qv5ASLmaNGUpiCHsBQdh2PZHj8PY5VqJhfSdLWQRo8P+X1PmkRi228AscN79PW2Sih7khzj1Lkx9ozoK/e4uohDDRe9gVcGzk0lVd1J/6F8+IKDsUAuyFPICLSb33wdjLeoETHBHojRLpHCvpCs5vOnRQj0LRYSj/pkEVhlfvM6Jd4viSyhz8vvY5tKqqIWRhoXkLDytIE9XmNndHe/Wzq9v6c8iBMgW+/uHU+ZlZHwSLvtA7dUZUYUqQbxQ8A4w2Qa0fpj0tWc75K65vJZe6ugcEacA3eIwgOxJJ9LRE1gRGEjdeY5RwrmJE+XH07ZX9jyXYUkuTUQR0TIgjazhPAQnQRqAyFTZSi9x3enYsXs0IEq/xWSsm+X0YRQxhJZkRqvWTP2XaJZLZ9w3OMQOyOlslzhMSovUXPgNCpY/qF/+OSiVC6pkz7PEkhloYX95gqloJyYr/Fwyg8S2256NkPCurjH3KKmxOGV2ZKj5u8scVld+Qs1CbkMgc4UxCjLvf3OLbHHSYVV8uvDzyVAPLAK3jDezORhn+OlZKVrdgU4zS62oR1Q6RS/StCdYouh7UIgrVqhDZS8diMRgwvbRVgIE05+58nYF1XtXHYBH0PSlbwEAZjYoPbr42asw2D9Vz7Q60LQUEUb032dQz/zBtn9HZjyFAVAhgMA8vdtbgKyQcVRxVUj1+OcOGhvV23xO0+gRgv3u1DRExz59g6fiN//5Lq0vq2GfWU0AylZESnmm2Q4UVBjl/bzHIt5KqFsoqGLgXcwA01JmtwAzVm2oaYKw9u8uzXDXPP4ecm3tjYbmXQDjMQFZmBt0n7ceh9j+5uh5EeHWWz4mkrJHjQGrE/HQ0dAXLOLjXMzQ/4vb7V2Wy6kDZ4xAJMGdng9aGOlax4ov1nHzNny1jWqE34EhMpwBLFxgFJ1z+2hIj7VrQWk9aVRrn23aX6m46nXckHHW9iU8nGzKPx6KAkEr+RTxrWNvU2f2gfLJlJyQv2shcnWFjkCtcLv4PZ+tEL2LgCHIuv6zTFQaCVdp58=
*/