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
# ifndef BOOST_PREPROCESSOR_ARRAY_REMOVE_HPP
# define BOOST_PREPROCESSOR_ARRAY_REMOVE_HPP
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/array/elem.hpp>
# include <boost/preprocessor/array/push_back.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/comparison/not_equal.hpp>
# include <boost/preprocessor/control/deduce_d.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/tuple/eat.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_ARRAY_REMOVE */
#
# define BOOST_PP_ARRAY_REMOVE(array, i) BOOST_PP_ARRAY_REMOVE_I(BOOST_PP_DEDUCE_D(), array, i)
# define BOOST_PP_ARRAY_REMOVE_I(d, array, i) BOOST_PP_ARRAY_REMOVE_D(d, array, i)
#
# /* BOOST_PP_ARRAY_REMOVE_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_REMOVE_D(d, array, i) BOOST_PP_TUPLE_ELEM(4, 2, BOOST_PP_WHILE_ ## d(BOOST_PP_ARRAY_REMOVE_P, BOOST_PP_ARRAY_REMOVE_O, (0, i, (0, ()), array)))
# else
#    define BOOST_PP_ARRAY_REMOVE_D(d, array, i) BOOST_PP_ARRAY_REMOVE_D_I(d, array, i)
#    define BOOST_PP_ARRAY_REMOVE_D_I(d, array, i) BOOST_PP_TUPLE_ELEM(4, 2, BOOST_PP_WHILE_ ## d(BOOST_PP_ARRAY_REMOVE_P, BOOST_PP_ARRAY_REMOVE_O, (0, i, (0, ()), array)))
# endif
#
# define BOOST_PP_ARRAY_REMOVE_P(d, st) BOOST_PP_NOT_EQUAL(BOOST_PP_TUPLE_ELEM(4, 0, st), BOOST_PP_ARRAY_SIZE(BOOST_PP_TUPLE_ELEM(4, 3, st)))
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_ARRAY_REMOVE_O(d, st) BOOST_PP_ARRAY_REMOVE_O_I st
# else
#    define BOOST_PP_ARRAY_REMOVE_O(d, st) BOOST_PP_ARRAY_REMOVE_O_I(BOOST_PP_TUPLE_ELEM(4, 0, st), BOOST_PP_TUPLE_ELEM(4, 1, st), BOOST_PP_TUPLE_ELEM(4, 2, st), BOOST_PP_TUPLE_ELEM(4, 3, st))
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_DMC()
#    define BOOST_PP_ARRAY_REMOVE_O_I(n, i, res, arr) (BOOST_PP_INC(n), i, BOOST_PP_IIF(BOOST_PP_NOT_EQUAL(n, i), BOOST_PP_ARRAY_PUSH_BACK, res BOOST_PP_TUPLE_EAT_2)(res, BOOST_PP_ARRAY_ELEM(n, arr)), arr)
# else
#    define BOOST_PP_ARRAY_REMOVE_O_I(n, i, res, arr) (BOOST_PP_INC(n), i, BOOST_PP_IIF(BOOST_PP_NOT_EQUAL(n, i), BOOST_PP_ARRAY_PUSH_BACK, BOOST_PP_TUPLE_ELEM_2_0)(res, BOOST_PP_ARRAY_ELEM(n, arr)), arr)
# endif
#
# endif

/* remove.hpp
6lKXx3j5vYy9E2uxbbVpPz2GXXVbc6hrw82zSCurZvtecicHoHKkbwfO2yUYL9QbsZzxSLOhgUSzn0Hj0wbcb+Sd3rXk49+zzMO9b5mHG1Mnd1dhrciP2T4weaTm6AJK+GK4D+vk+AKbZJlCCHaFFl9SZ8+rwgLf+Ew3ZbDMh0uLrPRQ6IjHtOrKKvHRwqBlu6rLiuvEQ0UzJ1njH/6ebPm7k3Fd2Xu/rzPKBNB6GuXM/QvwUxYM39coG4Q+ADoIpixg73C1twTXFG6ujUtmOkorZxJcFFXOtNCj4If/5D9FN850j1Z8UXS/zo6QUkd1UUpFVU0tdh1l0jJqqiFacepYk27uuWaeg9uGsfzYMpaJYuzHmpWdk2kc3jXRO4ZWCmN3VtC9N+3JATszxcbaky3bSRk1WQljA28w1xms+y/a/8rAaJ/AG2ur1bNMejupMugGTZ1nGK7vtPCyZ32eKC7U73jM0fQ/u5QXqVPUdF6OleDX+90Wvd+j9D69Dh/NDLC3gxZ+YAf9DTHnZpR9+9S0iVX+B5n7hqt9Qz+z+pV/0phbfVqGOmN6r+pH0nHZxd+3Nwaf9lv49IWqv8LqLwLnJpWth0/lJRVqe0tF3+flUVKleybbmRgzXPl+PfvSO8cWpIW8a6XmLQ9Y5y2PY5yDysdx6KrR16+7B+zdpebKDZ60ES9P/HMOFgzVy4KhfBjkYPe6c2eHLPhkRBvvNXd377UfVdk2quyEbkfJwzZAT4z+/KKworU/p7SVE/9O/Dvx78S/E/9O/Dvx78S/E/9O/Dvx78S/E//+D/71/EST+0/h3LW7dDn1XZGJh22y/a/kZ4ptcuZH7IfxHO8z7hGZdjK5TWL29y+3yeXjiNPbafL0RE1W3C1ycgHnsi0nBm2py8nxIm0fZfbnJNaODyTnRvB7eJYmEQmsrpynSavrbXLzM7oMT9Pl+xpdhsbb5OIdmkz/C2/87Nblwwc0efOILvfTjmtX6DJvvk2yY3X5boImYafqsuwN1tPm6hL1syaNtvGu0dWaXEecqvP3Gbdpsmq6Ltd+rMsTkzU580f2Fckkf/i9Jn95XJdZG3Xp1Ju2UuefLzT2ktFl0lBNKu2sFUywSW6JLm220oe2tOmQLjcu5HxC6ljRR5N3Duiye7MmNxIZ/2WPJsumanLXtzZ5qsomDx2xSftfRPI769JxuS693tclkXzLK804W7mfSCV9XDlIZPNPupzTlZOlzmQP/Sc0OThck6hkTcaP4szWfZo8uJ29Fpbo8slU3oHaYJMdIezlv1OTHtuozwVP7iBncC97mr/P6St7RTLOYU1+X8YhxCZ7BsCTmzTOzNVk7GpdRr3C7myfwpM03p0fqcle2ncoT5O8v+hyA+Mnt9okmXLdZonEDdFk8WjG6lVdrq/R5L4QXT54lpU3+23yCimF8Qt0WbWUeRmHJjELeVYL2n6xLtdFaTLrLtY+w98r4O8Zybos+TO8LdDk5vd4x3CAJlPPsEmrF2gz7b50PWs9T+e8gC812TCUdyJ3wOsImzzagfWe8MdzI/ur9yIb9jJrh5vo4maz8xen8x44q/N+flWTpKkiP/1mk9gbkU9oEYU2GTWCfNF+3pdrpMulN9ikZVNdPkcm2r2uy32XsWZuB/LTn3v3Mq9zk03iRyILT+vStRP8a26TCT2Nk0BtsgZZ3ferLn+l/w+cKxK+lDUWyFB4MbJ0iD1r0JOQibpMP8I6yemabH1Dl56z2dNmsy4fDdKkfaYmKRvgMzLdH/7uXaVJxQhd9lzDOo5Qkb13a/L95ZpU0R67xyb3reHdhjhdxsDLFXdq0uJt3huDJ1t26jLoEPt5LLbJloW8gx4=
*/