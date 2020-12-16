/*!
@file
Defines operators for Orderables.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_ORDERABLE_HPP
#define BOOST_HANA_DETAIL_OPERATORS_ORDERABLE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/fwd/greater.hpp>
#include <boost/hana/fwd/greater_equal.hpp>
#include <boost/hana/fwd/less.hpp>
#include <boost/hana/fwd/less_equal.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Tag>
    struct orderable_operators {
        static constexpr bool value = false;
    };

    namespace operators {
        template <typename X, typename Y, typename = typename std::enable_if<
            detail::orderable_operators<typename hana::tag_of<X>::type>::value ||
            detail::orderable_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator<(X&& x, Y&& y)
        { return hana::less(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename Y, typename = typename std::enable_if<
            detail::orderable_operators<typename hana::tag_of<X>::type>::value ||
            detail::orderable_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator>(X&& x, Y&& y)
        { return hana::greater(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename Y, typename = typename std::enable_if<
            detail::orderable_operators<typename hana::tag_of<X>::type>::value ||
            detail::orderable_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator<=(X&& x, Y&& y)
        { return hana::less_equal(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename Y, typename = typename std::enable_if<
            detail::orderable_operators<typename hana::tag_of<X>::type>::value ||
            detail::orderable_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator>=(X&& x, Y&& y)
        { return hana::greater_equal(static_cast<X&&>(x), static_cast<Y&&>(y)); }
    } // end namespace operators
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_OPERATORS_ORDERABLE_HPP

/* orderable.hpp
O+5QZYlKcMeGZRmM6bfHfXegyuB2RpuY95DIe0fJnr0ya4am0Cv2jp031Jc9a3iPSyIBXq84wnPrtilonNM7MC69wiuoly+Nkpap69kruO6x7peWp/nnLeUJv1P6Cu/jW+orzuE5+1zmEb57s/9Ab58sKcOijOdXTeW/YF/fAbPD6qPizZBIg3y7PYN0JmfZfjwY99XAEDQ5+0ah9DXt7MbWWDwfXHtFgDkd9J6JvaDnwmUmXJPEV5tw9kDvICYdaHn4xhjPRSQ67s3Qhe4TOuzxKtP+o2O9Zqg4PMBGov4UbBKwS6JcH6ARw+CVCO/P9oKWx7nKwlgvlnH2WK5vNDcOzKR8DrYn0U1vng27KVG280zZZp/dz/rHb0ifMRvNw/DTzVyYvd+31zMRbp+Nzoib0M7PpZgjF4g5sns2BKYjcDQy5vpfhNFzZ6Z0596OK5ZBFJm+s2Gu6yisaNsyxI8bC4Heydiu56m057hQ5F8dYV2Fq6aOZhqd2/Wyrtl4FLamtaZQh0NK8WHNGy8y+Tn+Tt74HMkbva2MawMRBmXS9evhOtK18jWrV3+e4o+Or18cj4vD8/UNzsbH0KFOepw2H71D/VlyWe9v4xJR/rJZfSA1ODjQK+ugYKoeZY7HcC35gWivFwba60VJfsAd6M+l8kJY5uNlhrOiAyWWB13GuS/LgKDP8/JAni9N8gTuaF+NzJLBqW25kosoRg7UVNeN+zpx6lCE51MvZ1k3BMaP6xeMmf2wy4i72617rxDlfW7U1zs2LgvMMEvckbKbGGq2roESOwfYpYx08h2ShtxY3+jACCyTpB3cnqah/TlE78DwGMxJ395XyrFxBG3AM4R/++gKdY/3VVxXXj3VujKNdf+1VcJ3ltSt+LztOLkacfiN+6Zpf+2vBzyc95Q8zdpUMD/WFbwy9G4vbCoAPz6YR3g/ZWi/ReiM6irsb+rrfL3wL7q2KvneWqXfpyiK3ubOfzqdxmd7vEPgCz/33rbkUvW+7rsC+PK/xn8P5dILK+zkvbs8OcvOYV+ZuLsAx1qVOsu+/zBlu0Xl9cHDlE3jf1jgc09E2vas3rkijf/R5ByOdZT60sLwG5gf9+dqiaveBRX0sA7zbrrKm/Q+LegBNzjuPqtwQvZBnxc4jka1fJcFOF/IO0emPtPEPq6q0r4Zruda4cai9APz5UB/TYg+OFu1/1dC+OK/xv+a7F+W4yVVZtzxrUm59wX+jeRR32AdpC70Sctpy6B0VY6WlP98h3RuUvwC/Rts7+9x3GPuxH8XOP8bYuxOrpD35CE7FjIZpEN88kmZzI9cfys8OSZ+ovS+LZiPqfO39G0A/JczPcY1/Q0kZQFMvM+l3vysknjCDkq/+fkv9q4EPKoiCfd7E0IQlAAREFEmCSAiYgiIgAK5STAkMQfgsQ6TZEIGhpkwSYDghRcq3vetrLre94HXrve1nnifK4r3DZ5479/v1XuvXvMmTBB39/sWPmPS1f36qK6uqq6urrbODKkc79uHdG7ZZu39lbdN8UP+LCqv6yY+SXBGni/cdPmZcu5dLn1bhihvR9IcL1Rk0FdIt+IHax3foaRHjIF1dv1m2WU7bPzW0teMdlEHp1n6cdf5LfXnO+oPx1Ev4Iini5T0EiU9GGkL/60KbfxM6TNZrAmrLGCusr8N4bE5VDwA6jfTaIPqcvAS6e/2LZtPdO/zO3VeRXKQ+7l085t4uIjwwNeR1AW6+914TkPae4+anH5svFXn926rp9JWL38CvuqlGyttbEdt8DexevvdY09PWL/3XoXX39ej/n5K/Rl+mh/i6xYP5ryhf8I+dK6LG7GK/G7ZsYOfyW9ljQ5Cnrf/tGo=
*/