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
0LaW+An7kgLzjLGWCPv3uyGutQTxWZyrpXKpVmatpX1IdS4oEhjMO3/QbqYgddNKVFL2PlKi04OsXKLgr8YsbTYqoYBXQP9LbSQG5bQhlPD+DyQajUbKZ1n9UnILkfLv/3h952JCbZCGiDQvBxe9WIM070Y2+mf7LW3etA92797NvuWl/UhRXbDvxmnfpKVLl7J9kvRxDfZbGneOfUPu5HiIffNLe8pMmDCB1UPfBYvfpI8cOZLVUdV+S+EHY9m307RPE+0rSt/g7t+/n31/PmbMGJg3bx7o7d9f4RvyRQsvsT1qVqxYAdHR0WwvdNoDivggfNo7SW///gr7Lc2ecQHu3L7DeKbvfel7Zfp+m0DEr8k35MS3mMS93EV8/f379fdbmjYxCk6fimT7kNJ1tra2YGNjw/YFpb2rJk+ezM6TDGn//l1bEnXfkK9ddQlOnDjDZEdyp2+nx44dy74hJxzK0147QUFBunakGFKV7bdE8qc0bdo09s03HY37D+3rQ/uUkmzpO3DWHlevsr196Dt3+hacEn3jbIy/Zs2aAfr7YFWVKsFnMbAo0f5R9L033QOdp2/IxSTuLTt9+nTQxxVBPxmfp72LaK8w2gNKH1+sIyMjw86YV/06iS/at3/WrFnUhyvY1Sir7vq4oaGhbL8EMdH34jQOUcYm7eqEhISOtLc/tTd9q0/XEz0RKOYBjoUKdnX5vqQScV/S
*/