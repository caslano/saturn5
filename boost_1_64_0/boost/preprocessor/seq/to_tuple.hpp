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
# ifndef BOOST_PREPROCESSOR_SEQ_TO_TUPLE_HPP
# define BOOST_PREPROCESSOR_SEQ_TO_TUPLE_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/enum.hpp>
#
# /* BOOST_PP_SEQ_TO_TUPLE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_TO_TUPLE(seq) (BOOST_PP_SEQ_ENUM(seq))
# else
#    define BOOST_PP_SEQ_TO_TUPLE(seq) BOOST_PP_SEQ_TO_TUPLE_I(seq)
#    define BOOST_PP_SEQ_TO_TUPLE_I(seq) (BOOST_PP_SEQ_ENUM(seq))
# endif
#
# endif

/* to_tuple.hpp
IIMMMsgggwwyyCCDDDLIIIP+lymOGWSQQQYZZJBBBhlkkEEGGWSQQf/vZAW34P3/H/tvK2p/vpF/BCB/A8DkbwDkvx8g8Hi/AeC/5VEivgEYJ74B+EqU4SC4CeHzL6BvACK+7j/qu/8TbfTbEUm2MDDuMf6+A/5wPD4YGALZDMRKIVlEko38xxzkbwYKWT+yaadsEyQansttupBsgi8cLq8ETwWD+DbgdNs59NsJrQFZt8JmJTsqbelUJ0o803HYbqO4PL10OT2kP8ZG8XF9XopsZ56wc7G5p50O6CzT7GyV/K3HZeOyH2jjMmHj+SndfZlviW7jKr2NwaA/yNhx2bnqB9q5qhc7X+/Fzg06O9GAff7jtHPDD7RzQy92bhEv8IwQiQznfR46T+vsxBc7+FLm+OyU45lIF0q4QlShG6fT5ddP/4AyQUbp8Zt0noco59/Ucsr374p7KaLcpTHKbyvKlAhuhc5urdz4IQneI489RvB89op82iPyWdVLPsyrz8fjY8eZj9kbPZ+4PtHzSemWj78zfJz5pEbks4/7FHwthCmmlz8p/njzjGdr5/6iIv/Frs9LGHuC5BlJbvurZ+/qGH7SjVfNm7PuS4Z4XH5x6o3PPjsre+qWOy74zfZTz4G+1czlD59Rte/Q2JI/X//xu8+7TK5XGNsPfcW4U1Lkb64WmOXvq+5hyjiuje+p4FvEdYv4vqoN2Je7GJgJ7AAOBvqAvJ3PAhYDQ8AzgGGgHdgJbAB2Ac8FzgW2AecBZwEvAc4FXgpcBLwM+DG3D/gFcCGQzzeLgNzeYepYrY0DZvBAcV0u7K3Q6S87iv4YoT9Wp7/qKPqnC/0zdPobjqI/WejbhX6+0kdpfOj5PVu10K8B8nGjVhdvt4iXFCVekYhXDOTttESNxyut93jDRbwRIt5IXbyUo8Q7TcTLF/EKgKVM/ghvGXgV+BHwJvA28D5wihX+AleAzwfPA68EbzBeeDTIIIMMMuj/nP5d+3/6W4Kzi/PH0Pb/h+//O1OYuodlYg97pVjjXAG+Lw3z/BRaB7vwq5otTOy5wrQ/8V/Y6x52iraXWZfGdV3h2aRTZssEXk/hC9hp+L/H/iYifpiswn5CxM8C3kbhQXYSjE6FztYUoeNwSUFESIYeL9TLpJfITmYzKY8u6F0Eng2eA74YPBc8j+Q91/dxveynuE3pVH5tP8XLmU7llNf9JcKvu8R+9h6x5l4Lfha6OVXk10BnMOAPSY5AED+gpfh3Lu0VWzy0xxVlriD9i6P4m6el+WsrxSU/9PRthK6T6iYg5yvqpoDCB1LcJF3cJF3cBLVePGq8agqTz2HKyYsB/hN/uJ9oO4TvX6ZQ+CW4V+O68XtXFD8Nd+dSuEe+x1Ud3fftpq/YmQH8GYUvYkNQt7F8j4E8LwVfxutSZa1e9cvPlF7qlfs9nfyu1etWLiN/kox84uR1zf0m6nq4qOt7xObgiMjjG/BL0N0i13XI0+ZjCWodzVb7wz8ofBf7K7NGrd8tujort1GdXSjNiVa/mq7WT93812971qdON1XVdXmD+N06pV+n6PRTIvRfSKO0PW1SSNVP0+mnRdgyuz/X5z+3prXpGdU8fBrFzdLFzYrIq5z8FZJc/CfRRF4DdfoDI/J6kxvL+6LQ3Yn2NxbtpC+T+/188ALwz8GXgxcKXAS+AnwleDH4KvAvRPsZ2Pu4gDxjbI/zsoiBKpm3J7XtzFbbEq+7dKo70ZaUsUTUUQZkKYpMrQuSk2+5z9NVn1Ma5Dfu23Tyraw7kOfF81Z8JuuSH95MUcap7ucgdWID2M/M/96K/DvA7/G2S+Waz2cdGl09rXPIx+9o43r0NlsdWX8=
*/