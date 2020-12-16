/*!
@file
Defines `boost::hana::not_equal`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_NOT_EQUAL_HPP
#define BOOST_HANA_NOT_EQUAL_HPP

#include <boost/hana/fwd/not_equal.hpp>

#include <boost/hana/concept/comparable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/detail/nested_to.hpp> // required by fwd decl
#include <boost/hana/equal.hpp>
#include <boost/hana/not.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr auto not_equal_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using NotEqual = not_equal_impl<T, U>;
        return NotEqual::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct not_equal_impl<T, U, when<condition>> : default_ {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::not_(hana::equal(static_cast<X&&>(x),
                                          static_cast<Y&&>(y)));
        }
    };

    // Cross-type overload
    template <typename T, typename U>
    struct not_equal_impl<T, U, when<
        detail::has_nontrivial_common_embedding<Comparable, T, U>::value
    >> {
        using C = typename hana::common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::not_equal(hana::to<C>(static_cast<X&&>(x)),
                                   hana::to<C>(static_cast<Y&&>(y)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_NOT_EQUAL_HPP

/* not_equal.hpp
b2H3IcDYPQwvX8Tzv3Zii5zr4m7gTRvFW7b+JtHQhwjV/z3V13WPDqGuZrHUtyzcFSb2h41aocGNjK/gbF9eZPA5cO2g71tcT/q6Mzbb64ejTUNyonDZPeFmRHN7fTIcQx2AmYHqwu5/f3bafujEljzmxIl5ii6zeMeWPouFoz7bubsww2OdD95Qz1y35zyDYHXMNKMHDjwDt2vH5bkGzokxCb4dAMauhVf010K3KZi3AFRga+E1X+fjo63LMUAO7I5t5604P+rQlk6KgR3bzod+jbXBHZ9128639ttpSfJwmKyd77Dwl4YlOeBxffrHh/qkQNG+pf+eWfqHY8xTu7pp16A5mhqcDjz2ISXloHjDwn2Q8BoYM++mBRt0tjP+dWl359UnCeYp6zoa9BDy8lDbQJD88BkLY2IK4NOBXa8VzZeWnyi+zqttX6ibLYCl+zreVxeG6L6Zr43W5HFAspKNR2T63o9H9AXd5nAGgMucH+TrslvYmyTXUL83D8C6+5vYAs6PuvJ3s/hKdAoxfvp2f/67ZWfCTA3O2vb+kM+pGWcTPmloYX7G59NZFp0M+Xk2ZsTDLO7Rl51y0zZW/mfWDl5OsTn4+jRrziaDtOf7N2f42OjBtFxlxF6dlRhyg6nz91mZ4GDavlDi7kwbCztqBwe2zX/s6NVVRIG6Rrb8rzPlWpikdfevmXKQs3cUNrZX5200lj481sdA3zNaTYINzWHLLvwGZbhXPXLVi8J0gltrx4df13eCOlht2kNxeoBNh51VP+7KjRWcilGyoIAmdAZ9x8IYQR4WdvhMvOP/gspX5MOvlKtrOvOK2tUmFubsTxnMalNXq9KI5R2d/Z/aWL0OHPVlSjh0APA0NBhs+dN+OtMOzFVX/pyZcve+8u7ZNuqow/ye1NxqABjcTrUID8Ubm8O31qpM7XVsoxt0Z+6nbq3KcU5h8eEYt7sixVB5jsnj0rJHJ/c88S6qXnu2YuSJ3gceq+AhSW0okZxsJqm/zYKqx+VfPX1Er7mWKl8fq5s+rPSJn56j+6gO7/2DtqmDdYvzVQ9WZYfrT9HrzZSyfe8PVK7vwwpAD9JtbPlLdWw02jjxnEN1E81H0Kfrs2Q4fsqmGwunovJH+B7mBpNLddfcsjYYDpNRHtMrxw5zHPc0TWnA5/Deqn1m77EbAuN1cUcnthskZYrvdmhw4HKlYSa7mnvoRZzacuwebvn4QP3dPvxMWFuau7lw7WM17U3IT63KFR8qP6/ZM39wbZSr+cVwA4l7GRt0/LVwUwWn75NnByzG3x/upb4b+R5FFu8Hbqi+k1xmLmOEeUj9vB8byz4UG9Njd7b9tLEZR/rNTr0l2b4KC2PKzNKf0v54HVWuM8bbyiMqu8lVzfrpymgMb6nKzDwBu7E8tTwHW21V3u7Hqnn4tGfrLtyJtRtbnl6emEAqv4st17T1fWTCePJTTn3XkJfPz9f/qngXSjGlMGN+uZ8/7dhhyLhMci8LBb89nu1ikZ2nOC28XpCJOKpCaJ9tvhuoCrUsoU3dNrUJvHXYbB/TgGxa2feD5V5egbCoQ+jY6TaqfdjCyoS2s5/1Jx4qjeyUOb6wEWWUqPgZsdCkR24DO3ymldocjmLpbi+7+tgsSsMmMk+Csxi2Do7QR9Oeyup0b+3GJY4aLw69WgQqNqmhumFd74HYJv9cbnu3DLWrE0vpVRxfmIooD5ssqAs1acYa1Nii2pXCwitO9hQuYdv2omXXz833G+UkVl12/CxtzsVyQTrjBXyyLGKvxJu0ijc7svPPZnSXxotizTs4alEGTeB7mWEtPMQaJC1/sl72+ODXvbaEme+HQVYJ9dy6ZO8aJsoW/g4=
*/