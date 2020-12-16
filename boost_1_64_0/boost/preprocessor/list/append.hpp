# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_LIST_APPEND_HPP
# define BOOST_PREPROCESSOR_LIST_APPEND_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/list/fold_right.hpp>
#
# /* BOOST_PP_LIST_APPEND */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_APPEND(a, b) BOOST_PP_LIST_FOLD_RIGHT(BOOST_PP_LIST_APPEND_O, b, a)
# else
#    define BOOST_PP_LIST_APPEND(a, b) BOOST_PP_LIST_APPEND_I(a, b)
#    define BOOST_PP_LIST_APPEND_I(a, b) BOOST_PP_LIST_FOLD_RIGHT(BOOST_PP_LIST_APPEND_O, b, a)
# endif
#
# define BOOST_PP_LIST_APPEND_O(d, s, x) (x, s)
#
# /* BOOST_PP_LIST_APPEND_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_APPEND_D(d, a, b) BOOST_PP_LIST_FOLD_RIGHT_ ## d(BOOST_PP_LIST_APPEND_O, b, a)
# else
#    define BOOST_PP_LIST_APPEND_D(d, a, b) BOOST_PP_LIST_APPEND_D_I(d, a, b)
#    define BOOST_PP_LIST_APPEND_D_I(d, a, b) BOOST_PP_LIST_FOLD_RIGHT_ ## d(BOOST_PP_LIST_APPEND_O, b, a)
# endif
#
# endif

/* append.hpp
ju283iBqQ4D1XcCU/jxENTwWwvqNNERg2XiiKsrVGh1MOVFdgDemS+BzHy08GMeRGXpkBtHuH+ifzdVcNN/DOIAtY7Sj3mF2ucPxP8VH32sRcM2XbLEfg7WVnBrebmMzIuNQEA8ZFK62SLxudctPDjn6KLERxv3cofHJuJxb86S239BBe9GTe2hh1qoK44PLXJo/4YJd98LaS129jeYzhVk2XyLvRC6nvN4wyhWpMnZHd5W3TWGt3dVfjYhQn3HtodgAjLYHwteQi1iKPTNdu4acSh+zs45v9WfkPKZebROdH5NtqveUNyKOpnzfmBjWjKknaRx2tUUH09DBXwWiITrx+feeepJnVB3kRiek/y8meX6A5F7e9jjkco2h+Ns4ngjGevfg7iLAqq0W8GEhml8yB/fMUMUpPwuY/j3ttn5Lh7mXwyuhTEOv++CLNqp4/jv5RY9ko1bGlz5RVo2b3OlISaJ+p+RM0N5+6zZWneDSApR63NUiZ7YY+F3D1RcZ8TNH/swzbn2JFm/x104bgoSyg7RVEzWXrlUt26l9XmP40CaPDcqUy1iqnNga2U3Y0XT1wjgbxYJsGL0GQMYG0u1keIavg4mcX1V0UjnPXHxr6vfBAw1qgJ75NKnam+7e8U6aM3IqyMLUau1tRrU6m1EL8tEm+Ohgz8FnKTRiHz6oHueX8Bsj8rb1ieoQJ20eJOBZi39sUw9nJl/t4PXJHYjAGdCHKEioHCJSOEc0XrHY423hBvRoBM3TUUfSiSzRUVbAT1LQbDpLtEIMQ+AWkCG9xOlvgbm85ir/Z+Gpq7qJoIrA9glpaJVAANTP19liSTEyQh/Ch7dHIrtdpZEN9vbbAFD1ftwgJGWJW8AQzFgTdjCU8UOyNBuSIhegkNJGjXWGvU6qn9J31u3PasKgqzPhMOmwHRuSlXInjqqtMUuWQeJQIiGYu5NSY3DgSYzafIblWWmWIo3OiuiD7mZ3qF2hrzFbFGobdJKmSvR3OJpdClbEC6YIIzeyweUS5rPFQGSXd9ceUtJb6O2VoD07Ld+yRXf66LBwxrM1dnFz+zPqlWLsoeUZ+e/aKs/E0J0vwvjcksdMhxjDgFu40zsR25K1u1DQc2kdTRv6uDpk4xTpRy4eiy5yLjRpcsv5HZ3E0k1YmzK7BZ8ub5GCXk72jNR5nLpFT13kl7qQUz+VqST7BzB7d6W35sbbXa34gVmc89P67sos+AaSL06u9FraKeavn2ntRyvBZA4fQFgdqbuQYk7y9kH6+m+L3p0vQhkb3vZKCgjhuYpW5vhMCB+klIz2k01O7ImImfdJ7YWdTu1AZjtqQQxb0eIh5EpEaKFkEYuQZkarHGMD224xI5IfGqrdzJ580Q4EQPWz8aPeOhYz4IcePf6zePj0O/oMOv5gvGb55ixsTAvrFrWKZgwIbwWKLgTDw/Q5jUB/+Lbxx5s1ZdKR+tqp7IP5A03k/vM21q9vYO0K9zPcUbg6uFZvDjRdDHc5XBLcDXC3wmXDPQD3GNxUuDK4Oap7F+4TuLVwP8H9Ddd8Ht6BhOsBlwo3F+4juHVwP8Hd8hbubcE9CCfgTsCFAqZV+J0P9yPcNrgoxIEvLA688Oc2ufNg+/443bRInkr3/6dMSpy7L2sImaHO++cQzPbwry65uOhHmAXPFrczJ8QMKRxARUyuDffwcntD4+srG+Fb35mf/t/6pt/tW9+H56jPjgrdpmxU6B4eqdbZXz0fbqjr0Ba7q76q5TsqTayfUGHUf3L/ha6fUGPU//J51D+bzg3VJhJxkKvVH4f6DXTbxa9cZ6Re5w6uMwj9rlcruVYDsuYuAFn7D/zL+wf5EDQouYo33OL0qlc=
*/