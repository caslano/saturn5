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
# ifndef BOOST_PREPROCESSOR_ARITHMETIC_ADD_HPP
# define BOOST_PREPROCESSOR_ARITHMETIC_ADD_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_ADD */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ADD(x, y) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE(BOOST_PP_ADD_P, BOOST_PP_ADD_O, (x, y)))
# else
#    define BOOST_PP_ADD(x, y) BOOST_PP_ADD_I(x, y)
#    define BOOST_PP_ADD_I(x, y) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE(BOOST_PP_ADD_P, BOOST_PP_ADD_O, (x, y)))
# endif
#
# define BOOST_PP_ADD_P(d, xy) BOOST_PP_TUPLE_ELEM(2, 1, xy)
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_ADD_O(d, xy) BOOST_PP_ADD_O_I xy
# else
#    define BOOST_PP_ADD_O(d, xy) BOOST_PP_ADD_O_I(BOOST_PP_TUPLE_ELEM(2, 0, xy), BOOST_PP_TUPLE_ELEM(2, 1, xy))
# endif
#
# define BOOST_PP_ADD_O_I(x, y) (BOOST_PP_INC(x), BOOST_PP_DEC(y))
#
# /* BOOST_PP_ADD_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ADD_D(d, x, y) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE_ ## d(BOOST_PP_ADD_P, BOOST_PP_ADD_O, (x, y)))
# else
#    define BOOST_PP_ADD_D(d, x, y) BOOST_PP_ADD_D_I(d, x, y)
#    define BOOST_PP_ADD_D_I(d, x, y) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE_ ## d(BOOST_PP_ADD_P, BOOST_PP_ADD_O, (x, y)))
# endif
#
# endif

/* add.hpp
dxJLGvezcj/C/AQPWPL8QwseS48eJD7+2DL3nbtz7JNW9ynNw57y/csmeSd0iNvvUty14NxPN+ODPaRspsuR+LMHiwq1F+YiKO3Drt85j0A9RIzLIMVSMuUIg1su/BjQM7iVwuz3mcOv+hxul6j9bZp1ova3aR4B3eNF/W/TbBX1v02zG+X3iWwCMxDrozAefkSNrRae5lCLhAg/yvry6B58f2iL7/vCVlx01b1wrDKRr9Y68zFuW+a8fzoUvZ6tv/7KbOrfrL7weAseqy/8nfrCPywbcqM1t32C0v2Lzcd/xObjT1r5Raub/8c0nw+1uvnDrV7+B1n+SKvH936tfr4XtLoP53t/otdIadvrnvHzzvUFuHvG/60TBuJj10JWD/w29VjU6pfDQcR3U6srh4OJ76hJhzUza7MWq+6trXisuseIxuJW//mhZfS8qEX+y/cMI+JplGcJ5Tlp7j3Leew9haOH8vpEZ59rWgp8RdjxQBHxTOLrsNbqedois/O0UZ7Dq+Rpi1TPcwTlWV4lz7V4kA75/HmOpDzP4W06qw4hcRSlO5rSHYl0jYwf1BtluP8uilaTQ6NYSTRWtVb/xu8yK47quZS+g9LfTePGs1oprlDbl1Y3Lihp7p51z3mWMaSaG1AI92ykbfLOYtBHMOkmij97d6ZFrTse+N22K0AjJsbl3qe5PAaFs/OeHpQiso3PYqmYdQ1CYiydFTpvW3W8JGNoLKd7MmrRWEH4WjSOAf8racxChE5F16sd8A55l2sBCAgO6zJUoawc43y86oLszR2yZgycnNT0V4PO8eCBhd9Q9JEw7bNBpAruaOX66SDycGerMH+b3XgPFESbqqp/WjC118m/c2TuXjKxphF1rgbJUbg+T97FymkM8M2mjbV85fVc5RxH9uPTbFzBb2NP11l97ziyhc8je7qe+sHzKd3GOn6G6ySPlh9A+wz4t5026u/7M1k0zTPG+ug6fMjyIrw8kv0LueznHdsciv6ezQO62Xi60RpTNrXiscaUzSTHHkr7Gp9vsVdO+dGl2bePDGxrZoKtCxvFgIldMvMbgiElPzOAtIPuYkLwOIvJnmmaA3aSj/pEJpeYqL+HOGvvBv5MrW+bu0e6mULWQtaeHwS8107dO9jq37vtiur5BfVz2f+YP+tkpG8UOBnG7nkbaNZ7amzvyNhCwFkcWTEC22d0yot17WOyW+H2Z76bZACc90VMd/ot3RloxWPpziDpzovYHCDDzmkMWzRGWvFYNLYTjVMo7QlWO/LLGFgbVkOYejzJ5lWnWzy8uBWPxcNLiIdRy+bA1vjmwi+jdHFW379a898E5bmB1r5jlCdp0T7eiolLU7pxK92VUWufk9JlrHQ3WOmmKF2W0n3NF2sDW1jt29gU92/WK2ZNw+8mxGAyEQfCSxeVcYvsfFWMrXvwrr4dV6yUhX5fqmKFvPxt6vyqZ0uWM//l7qg7dvPY5oVotDzT746A362lccXoRtHSjbNa8Vi6USI5Opa8myzdqFC6abY+OJzFTu0guI4T3an4N86VpP2t1IjB5cbiWMbGsXQE3msbg88m1YXqRYTcoqx+GsPO5mOY38ejtneKlbFsxt1fqIU0Mtti78NS3VtbaB+W6v7K1jp3INY/g6Dy76L8Rq7sO0+vqTI/bojMPmdwLvHyuirpb43OTv8GSn9ea43v3bB1hX2fw5so7/l8bWHyVisvIt5MeS6skaeF3b/QQnl2U563WnmammvneTvlucjS20VkJxyyTxdTundafQF4a10UFu+itO+2aI5b3+Z6L6V7H6VbgHSCywF/H6A0l1q0KsLP34co3YcNf6ijReMjrXN+H3vOOTPKj34=
*/