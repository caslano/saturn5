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
# ifndef BOOST_PREPROCESSOR_REPETITION_ENUM_PARAMS_WITH_A_DEFAULT_HPP
# define BOOST_PREPROCESSOR_REPETITION_ENUM_PARAMS_WITH_A_DEFAULT_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/facilities/intercept.hpp>
# include <boost/preprocessor/repetition/enum_binary_params.hpp>
#
# /* BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT */
#
# define BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(count, param, def) BOOST_PP_ENUM_BINARY_PARAMS(count, param, = def BOOST_PP_INTERCEPT)
#
# endif

/* enum_params_with_a_default.hpp
QVdiu/oPrFwXHV/rBwZgiFEt5dki5AFOgSw2K6kvCQ6EKkRK0x0KqxvM+mv4czGYMgQb1UTfNg3cZRhY5zFcf2s7JM4Z0YHwaTTJNd+WzYGo3spW/t6b/l6rESOeGnu106LgJ33znwyBxoE5YYN2gUpTsK9JyfN0meJVThypr+npHpICUqgBY0hnrxqC4Xltgj9/07Gs/KVTFEoWykVxV4GoxJ8jEYBnkwrx4/wwyywpCKTMhz/KWfgJQabJVtsW9v3Y0VB5xYHWNe2qhaxl7i36Rc0zQnh+KTf/oqkTY2AZGYbMUc8XVfxgtUADw9aA1GNa2wcY9xlWZOS8SD9tT1zRauwxR/HIpDs1xKZh63mY+l/Ofb+FgZAmJL/FQ9RxukvsLphbWdON+5viB2EZu/imaF82Ot9woaz1jOLsYOk6d38QkhgZfbh2Ms2ZPy9GKGbWAukQQDhwsngxXMW2a8yCQpSlnLqdCfYjGd7YRVTdnBRz+m2w4UdDg+4klNw2cmiraIkGB40P/P4XF1l7xWGu2Ry0Hi05hXY8gKIDH0Qz/T8rM2wWXLHemQ==
*/