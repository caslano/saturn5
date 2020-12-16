# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_SEQ_FILTER_HPP
# define BOOST_PREPROCESSOR_SEQ_FILTER_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_if.hpp>
# include <boost/preprocessor/facilities/empty.hpp>
# include <boost/preprocessor/seq/fold_left.hpp>
# include <boost/preprocessor/seq/seq.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_SEQ_FILTER */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_FILTER(pred, data, seq) BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_SEQ_FOLD_LEFT(BOOST_PP_SEQ_FILTER_O, (pred, data, (nil)), seq)))
# else
#    define BOOST_PP_SEQ_FILTER(pred, data, seq) BOOST_PP_SEQ_FILTER_I(pred, data, seq)
#    define BOOST_PP_SEQ_FILTER_I(pred, data, seq) BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_SEQ_FOLD_LEFT(BOOST_PP_SEQ_FILTER_O, (pred, data, (nil)), seq)))
# endif
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_SEQ_FILTER_O(s, st, elem) BOOST_PP_SEQ_FILTER_O_IM(s, BOOST_PP_TUPLE_REM_3 st, elem)
#    define BOOST_PP_SEQ_FILTER_O_IM(s, im, elem) BOOST_PP_SEQ_FILTER_O_I(s, im, elem)
# else
#    define BOOST_PP_SEQ_FILTER_O(s, st, elem) BOOST_PP_SEQ_FILTER_O_I(s, BOOST_PP_TUPLE_ELEM(3, 0, st), BOOST_PP_TUPLE_ELEM(3, 1, st), BOOST_PP_TUPLE_ELEM(3, 2, st), elem)
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_DMC()
#   define BOOST_PP_SEQ_FILTER_O_I(s, pred, data, res, elem) (pred, data, res BOOST_PP_EXPR_IF(pred(s, data, elem), (elem)))
# else
#   define BOOST_PP_SEQ_FILTER_O_I(s, pred, data, res, elem) (pred, data, res BOOST_PP_EXPR_IF(pred##(s, data, elem), (elem)))
# endif
#
# /* BOOST_PP_SEQ_FILTER_S */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_FILTER_S(s, pred, data, seq) BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_SEQ_FOLD_LEFT_ ## s(BOOST_PP_SEQ_FILTER_O, (pred, data, (nil)), seq)))
# else
#    define BOOST_PP_SEQ_FILTER_S(s, pred, data, seq) BOOST_PP_SEQ_FILTER_S_I(s, pred, data, seq)
#    define BOOST_PP_SEQ_FILTER_S_I(s, pred, data, seq) BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_SEQ_FOLD_LEFT_ ## s(BOOST_PP_SEQ_FILTER_O, (pred, data, (nil)), seq)))
# endif
#
# endif

/* filter.hpp
nwu/KS8R5e0lUyO/G2+s4/0ZPqfJKrwIpRVB1xM3Kbwibcv2htp3xlfwADXvcO3dT1Ddq4km6sqvJVJizbutdTM/K053hUhTyVQ68ssySLWxIiibm82jH+ZK1jk8yxUxSyPZsBAmpL7Mkr7LOTl7aaI0mku+Qztb6RvObvLeZjJMBY7s5MClhyTNUCdYbTTTm+WtKoX9VDm+whLluxpn4Ss8XKzIeyQLcZKvm2+jN5soDU0e0ROb7rlx4pyru8gaQXGL67tE4I3X5aB59Ni6G9ct3SquM0UzpqFtlNilxz3qljx8mZUY7QnYsaxFDL+xFNcq3lvYn7j42S+9qwfOunOtKKeT8UFHBXcMfqLFRk6s5Xm2pG8wT2C/2MoWnd99muL3lWSilOhFIZpPilY7fzAJlzySsaJPUBHZczr54WT2/ccScoTtHdZkbMxDXypIHxKxL5lxHGvbxKdFDQdTmuGY1V/1UxvdF+mDYw/TnlM4YmtLrQGfaO04fO857iF26HK3rZFq9bTrnVMqov6rReOyy8HLLL67FB64hhtebCnp40ZZpkVdeT4TcgK4aM/uMixY3qxL2Hv+qCZbt+0fjA0H0RG4A+FE5JmZNJR3E3HjhcNDIwG+tqQZqijr9sg4/Kw99AiYYtSrPYyBWar8LpDbLgzjyQeZmFc/rXYFUk6xhiadLrgDQU7XwaBzaQUN7+3ZiQZW4Ty5NHxY7PSDtWCoiPzNwS0JYhWxMeOZg9ctIwGFtzDK0V4rmqTqFgczGc4fpgUNm8jeO6FTD0M3CYGSvi7odecQg7KUJ9g/MAROz8bTTorjvqVes+0/W3145H/E6j5huv7tO7ScB0PMdyH5dAoyWcerDlGub+avGZx0RTGMmZJaEdDQMehN+QIYxhNViGtLZsXQlaE8BM56i30J/M9ILY/P7aFeto8Liyh9ejX+MWKGpuFz9X6zU5CqKddsHanF3l49pmJ0QwKqGzfGEiaP37CQls4ji9m8slFsRUeIeL5oGiaGVYxtaYdYZZapDy+5xH2Om2s+wq1btM228l6Sr3oJNKdq+xA3lCyGPYc0u4qAacjB7Kn35HT9nY38W7o3OV3Q8+vwP3c/K7KAEsTBqSI5exOZX1VrYmFxmpg89B+0X8jVLbsbbgisECbuB56OlQjTktLkaWp4RmqLwI56+TWmETzgpH+HN0x5pc+iKA6evy1CLPegj0+DbvxOJOOOjMjJXRAOd3zr28+wTepve+Vw/JaRztbpeUVDKVeRzlVnW6Gbs1nxgpZ9ZEmPCwsJHXA+9imLq8PxyXnZuumUb7M7uC5VrE7eF3BicMoKb+29oMy8gqq/MEFU+3FLBbmReyz7IfeTht1Mj0XrQtTHCvbq2uom4MN+tLydA4x+OHo5kyOSs6/ju4aSI60h+y/nUSmIGECJqDPdPFCMLC6kNhUskNTFCBxYTIeyIgOZUt4/w9pOL19xEI1H6ZUw1cTjmL/e8/9EF76YqgHVSINC065iVU6JJJ8kcRn7rZTRmjaN72fNTxoRzI0YGdcozffOaiJzxQXC033xDlQqJNwhHEbTwz+YLgU17x937O87l37Khpx7t+mTtbRECE/KrJ25MPUd73m4B1hAq7RyqjCSzGUkrbpOC/c1BpCt9tOVSsux3Q7zdZVSgwrENnhE+Nl+niArM9NdbPRM/unbARNQqYc6GuXZhWNFysbJkFKSsufLOtiY6G/FCB6l39JxGF58Ccl/hEuEu2uqIs0enNWYxyYIhiBGFUnF9mqtSHuBtpCl9pj9qGsOOvBy0vOP243UuBpuSrY5mmG+GJK09fgeOR5ILpWxhA6dsxBzi3oDL4uDv+pkKligRaA=
*/