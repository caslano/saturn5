# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2014.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
#ifndef BOOST_PREPROCESSOR_DETAIL_IS_BEGIN_PARENS_HPP
#define BOOST_PREPROCESSOR_DETAIL_IS_BEGIN_PARENS_HPP

#if BOOST_PP_VARIADICS_MSVC

#include <boost/preprocessor/facilities/empty.hpp>

#define BOOST_PP_DETAIL_VD_IBP_CAT(a, b) BOOST_PP_DETAIL_VD_IBP_CAT_I(a, b)
#define BOOST_PP_DETAIL_VD_IBP_CAT_I(a, b) BOOST_PP_DETAIL_VD_IBP_CAT_II(a ## b)
#define BOOST_PP_DETAIL_VD_IBP_CAT_II(res) res

#define BOOST_PP_DETAIL_IBP_SPLIT(i, ...) \
    BOOST_PP_DETAIL_VD_IBP_CAT(BOOST_PP_DETAIL_IBP_PRIMITIVE_CAT(BOOST_PP_DETAIL_IBP_SPLIT_,i)(__VA_ARGS__),BOOST_PP_EMPTY()) \
/**/

#define BOOST_PP_DETAIL_IBP_IS_VARIADIC_C(...) 1 1

#else

#define BOOST_PP_DETAIL_IBP_SPLIT(i, ...) \
    BOOST_PP_DETAIL_IBP_PRIMITIVE_CAT(BOOST_PP_DETAIL_IBP_SPLIT_,i)(__VA_ARGS__) \
/**/

#define BOOST_PP_DETAIL_IBP_IS_VARIADIC_C(...) 1

#endif /* BOOST_PP_VARIADICS_MSVC */

#define BOOST_PP_DETAIL_IBP_SPLIT_0(a, ...) a
#define BOOST_PP_DETAIL_IBP_SPLIT_1(a, ...) __VA_ARGS__

#define BOOST_PP_DETAIL_IBP_CAT(a, ...) BOOST_PP_DETAIL_IBP_PRIMITIVE_CAT(a,__VA_ARGS__)
#define BOOST_PP_DETAIL_IBP_PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__

#define BOOST_PP_DETAIL_IBP_IS_VARIADIC_R_1 1,
#define BOOST_PP_DETAIL_IBP_IS_VARIADIC_R_BOOST_PP_DETAIL_IBP_IS_VARIADIC_C 0,

#endif /* BOOST_PREPROCESSOR_DETAIL_IS_BEGIN_PARENS_HPP */

/* is_begin_parens.hpp
7Vmo3iVZM/Y+60pDEIsKovGmyOxXUtSepJocTkP7tqZU07lfCvLwfFGfh0YZT6M4nkrQ1Jj3yt2+ba8047JXohSDBnpkwFrUkQFrjUdUdo07ll72pl/DOrJ8u0nh5ZS36gotBsNdQ25wxGhwcAvyGmV/GeLkxSItNVKRz6uHS3DTTBSp6gBv8q3OJcIcLO3+J4K8jJyg5aW1G6UHuyqHpjVk2wMPXXNh19grLc9uippSkSmCBzQJMqf30oPYx8PYHxbqtL0FtKAUAyOifT1atGjaPKfxVv2Z849619bSYdRsXvSQYljK4NnGA8SJRmGtuHm4vdVI40uucJ40a1/u6gHbOMOwrFi6SuUYr3frANZvV52o03IHfwkdZUD5MKtpfUd72NbW89GVnFVe+xNrlGQOzpackGggB6Qj+vEU1dPjtj5sDFrt6cHnS52SE+1s9bI5a8IXFcVlpF7TMtuTHimZ/0f5DDb+o7Ipd1J6NUhY1eG5tJngxzct3r7zcRxHtePZ6iBsUyElH7HyKyxeHavx6PjHcBx1ULne+p3qyFROGgPFeA+tu6EjFvP2TFXE180/E74KTad3LZfKhflSsZX+98BSK9yK5oQ+0Q/XNfVGYSmmfLUdJJ/YYZteQH0rZ85OhCREfXF2+5PY+EKaB9pwwOqnRFDgx9Kxo4oxReg2tYebHqQVgYZxL57X5kSO1zPXPlKh1zhU1qC9ubcMDKspsCi0PPyIkvymRWVuuRFabaYaTuIejibHx4IksfcxjzXaapwNV0LjUafmo1uXt4iuWoC4VoejNboK62RFY8ZmFp+IViSyQztdN8t7aNTmFoydseTVoU83uUKh2S4fNiCMdk0VjKRH8J20LvkUmQr7KNI7YjhYG6L1WOMRYm87ZWtjVb65E6etQ94lzXkYNGaPh4qv3qlfSJW21SlCerUW9qav610EjTnh/RG1OKr6dy9hoq0GO2JK6a12NTxJssj/48kOoL1pLPIuDnl+tD1Y7SxKbEKTl8sBZeDdJC+PqmvkfrWgeAa9kRp4rP1ywDTO65Vl3rUQPFnlQGxOjkvCrtV8r9qG9oBC9lylmSqKmp+HtS7Rdh/xiExHm1fY4CVsOe90ZZnN6i9VrnhH3UYwkonnFde96FOTpr9h42PcJKv+FcP1Rxvy+eKPlY42cvfWK3wlaASdA7a2IYjmtjG5fPpwd+f2pq5WFi572FUdEtnpmKyOdNqNurxiQiioSitNGNV0N9rPoLAnxNFyuFHPRxduehYrxcmWI7PpVRQiNCkCyy7QGcrUmk3DZXVouJ2ldF3HvN8yQZw4t0sZSdr4FjqKQfZ4dZNB2oZzzcM2zO7rHN0ZU3tS8At4teMBcT532J6hYxfGoTnUzU1IuFiOpHlH7l7sCGY1NR+S5p832dR304S4zR+3XcHd4jZXnHuXW487LnOVgeFSTXGJ2O+1YDQOda8lVZe6W6cTfoBSFUYH0X4ltF+5mVpecsdX0IPoNiAG3I9MZz4iUYg+UCX2PMXngwcRczLlCi5EVeoZS6qn6TL8VFdM9vjDh3Je1HYeuXa7rNKOy74q54frcdgaNk/Fw6RCJRePKAk3UOuOkL8acLmpYrV60S6x3xSMUy0DijP9E2Cb+l1nTcXGXzi9Df7d1GXN3YRPTvo6pkFTWShaR+6uN139pEtTAluw2gQbDXstRuCQLJqfXbI1t82NZVkip3fzZxhoRNbcRuSyHLmC48fHIz0/fFfhvfRNmRcphcMp770s8VvMFpPFdDHPv6lisXhQcZavo8UI7+eKheJ0ccL2FWNMwMbTCvaX+31YTnrg3ZM7yqlNExuTbTBz3mU2trma942dbOch/t0=
*/