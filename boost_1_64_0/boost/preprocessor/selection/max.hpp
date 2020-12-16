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
# ifndef BOOST_PREPROCESSOR_SELECTION_MAX_HPP
# define BOOST_PREPROCESSOR_SELECTION_MAX_HPP
#
# include <boost/preprocessor/comparison/less_equal.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/iif.hpp>
#
# /* BOOST_PP_MAX */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_MAX(x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL(x, y), y, x)
# else
#    define BOOST_PP_MAX(x, y) BOOST_PP_MAX_I(x, y)
#    define BOOST_PP_MAX_I(x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL(x, y), y, x)
# endif
#
# /* BOOST_PP_MAX_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_MAX_D(d, x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL_D(d, x, y), y, x)
# else
#    define BOOST_PP_MAX_D(d, x, y) BOOST_PP_MAX_D_I(d, x, y)
#    define BOOST_PP_MAX_D_I(d, x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL_D(d, x, y), y, x)
# endif
#
# endif

/* max.hpp
UW2wcdonld9C3nQmOE+ZxOVgNJL4NB52sPXnViBBNHvWlumN7563vvzAyxmnRh5mVjnMYHt6aAJWEbjHly2iQnCKwl7TrFKkrB7FrlgWVXx+F87HYPDDkviNV6TL0489MmJuQQq6bNUD4MnwZdEwVBsUnH2fEK+1A4xt74wELzc5Mr4q/EEkQW0bM/Ga3dljWnFE0qza2VsIClPPtCwwJw2543hDTvlUWTZb02jqE7sa1wD3ZBsKsn44u2dkcGNgk1mLFCqEyB2fR0cuBzH+8JipRTNOuYcXWrPn3NDJ11jGJMbptwrj74Xl6Wl6tdaYhNyVU9Nt5pUqRr5zyxP1tJF4DXH5QK3juqQzf9tlGCO8cifwqkZhgW6SJbxFKAGfj+q+9G7qKtsI2E2tsygx3tUdMQ19zbvx03SxQaPsxbasplXJUdNXG7qL7TcSGV/6c6qmwGvFt+OPkV6sPhnKqciSsQo8olh+r8k7pZJdIafjdhD4Ph3mB7vCkZFvyKctYurDMJyQxaLvP1bN3R0TKFTZzPsO14gncsq3zLmxkGDQaCY5jpNKY+cQqyzXouYOUWmyY9UP5mHp1oWe4GfODcMkTqtR8p/qMH8sIKekZrY+vERXW3tfT4q+nGZuEJIV0kqWfK2831B/VmZSyUi979jb7BrDsoT7ohWMo3oqCpqtz65fNiZphVw0rU7BgibmwJNiZq0y63zDqyGq53xTpQ7dyIQ69sIaka/2ziuN60cgcxF0c2I6g2JnBaY2zB3C+0ZP2AzONiZxwRLxXim8J7bvcb9ZVj8fXMBitFggH4iRefpW5qegrfYVbIeHrhoBfy5ddTPyYWe2wTgu8cEn54hGD6SqAxLoreqSN3GINFV0bjb0SQg8o461dqy6pSmy6l2SE3pNaAbUeK7pI9AC1kkkOwyQizJmKeMzbZlLCA1sot1iCm4FbvpbTYchm3+I9MUiX61EdjPkT1DvFM/NJxGtDcr/UvdUAN4r0T69DPfFkb0gidUPvAzttwM/BZy84/gO55/8oNmPpo+fjcvJKr/+GKS43iqK+LPKEiE9mW2SnDt4r0YHI78K1kUkzxPzXQniHq1KMYs8K1FHbo6B6JclxZEdkyPDk5gZTiY+W2r4+WnJ6eW8rIX+Zk1o6ke9C9miN4ZNCL+a15I7iZxPP0IsCQl7kLD6PNEk3G6jQbmToInrROVzfnPhii2xL3lLbqDiOUPMk9W8XSW8whO5T7fRbvPMao5t1CQJudLgPNakVPHJRnFEYYZh4tapCycEOUkkIxalBaFC1yzOZ7njMCO1T+5IZsL6nsnrLH/NcVi/rJLzs07TVO8Gv2L/bsUgcdQpXSI8Wc9PeHHuM4Jiv1Kh7WPrJGTNlbS4o3yh5xe9V+exQYCl5OMqvz6e5UgVrHeLPzdxrl2KBxXZr7NmtAlVAZMzd5Fqi1nI5WlAc1Ic506Q6L44lqJVknSnVl6hLsGEr6lCO7dYbawSL3HAkEBqYJFa+NL/Mv79l+0472u60AOVhd29P4Cxc2LlZ/dE3eHVfrxmf12QMeQkdpo4vLdZQsA4ur10Ci7i3EKDr8T8mWJ4uzKHBnHn8okH6QZuOk++HYWhi1lKkHpSlYFIYyHWMzrIFhUFNvEIZlzvwJOBaZG6Mayo0J7vyIkw8G21m6VX4FuJr9/ULHTTlDaXJ2sTfFrWcl17Hk16Z1+KI+wsStuAqdto6+osOEnYxjg+e8Vjd/GJMYToVVEdbFcpXcybZoMf2c983TG78A7cs8mksN7ESb6wHHu/pBzxsfU9J7xrEMoCxthSCn1snFiMdC7l+uRRHcpnSwPIMmFDBpY9A7l2GwHnVsVwxGQYTks=
*/