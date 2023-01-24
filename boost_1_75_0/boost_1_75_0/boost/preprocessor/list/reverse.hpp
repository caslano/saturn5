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
# ifndef BOOST_PREPROCESSOR_LIST_REVERSE_HPP
# define BOOST_PREPROCESSOR_LIST_REVERSE_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/list/fold_left.hpp>
#
# /* BOOST_PP_LIST_REVERSE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_REVERSE(list) BOOST_PP_LIST_FOLD_LEFT(BOOST_PP_LIST_REVERSE_O, BOOST_PP_NIL, list)
# else
#    define BOOST_PP_LIST_REVERSE(list) BOOST_PP_LIST_REVERSE_I(list)
#    define BOOST_PP_LIST_REVERSE_I(list) BOOST_PP_LIST_FOLD_LEFT(BOOST_PP_LIST_REVERSE_O, BOOST_PP_NIL, list)
# endif
#
# define BOOST_PP_LIST_REVERSE_O(d, s, x) (x, s)
#
# /* BOOST_PP_LIST_REVERSE_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_REVERSE_D(d, list) BOOST_PP_LIST_FOLD_LEFT_ ## d(BOOST_PP_LIST_REVERSE_O, BOOST_PP_NIL, list)
# else
#    define BOOST_PP_LIST_REVERSE_D(d, list) BOOST_PP_LIST_REVERSE_D_I(d, list)
#    define BOOST_PP_LIST_REVERSE_D_I(d, list) BOOST_PP_LIST_FOLD_LEFT_ ## d(BOOST_PP_LIST_REVERSE_O, BOOST_PP_NIL, list)
# endif
#
# endif

/* reverse.hpp
3N7Mwx47P6cogSTxwGXneQsss6q89Kzr3VLtIg+IxXmKt1vo/2veqCJnoeB7EOclgihC+EreN7ihYPCqmKggjKYx44aUDBshe6Qh3giHWgT1/NBGIPgke0FoPq7w3fZRcFWrOXmuYgxCNsJMgcZPVaGrV+r1UWId9I132L0JDhY8Y5cj240FX1cZn4uVVqk6fok0Tl02ymNqrr8jYTXDxo9cg2FaV7nkSMCpboE2Jq/A6wY/qXJyha58EXtBCM/GXNwhU7v8hXLarGnXztQFheyabfoSIm0H9E1EyzL6eivpdOo+SY7CL0HeSDzqur2DC3gveAHATRrfv9132b268azMksTiyYqawmtgJAcqWpZcJAWSn76b6D0q9YwQ83mtHq8e3ye0kN7YxDKk9vS9VPJl4qxSNibMnVG0KPcwTlRqo3QYYsga/yVAITyn61300DgQ0VRjjyZWc8rxxudYSLeujGZMifj+yHtTQfXmhdOg6DPm/EeRr+i3bcEKfCCibrmCYhcIEYT70DknMD6/JAOERXOnsJppVKRFmWFUBjzAnrUD64GFwBaQAN882MdmiBkEF0IMZYQS/W2rDIoJJYNS+48KgZ3cE2B5sBRYzHYJxcx5TCeczfAnHEacAsthhE9DnzEmEgC1/icNjAV34XfM8KK3Z4KjhATGIFJVWKfyyxPzRILfXyuK36CEaQB4892TkYWr/5VdoP7b
*/