# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_ARRAY_TO_TUPLE_HPP
# define BOOST_PREPROCESSOR_ARRAY_TO_TUPLE_HPP
#
# include <boost/preprocessor/array/data.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/control/if.hpp>
#
# /* BOOST_PP_ARRAY_TO_TUPLE */
#
#    define BOOST_PP_ARRAY_TO_TUPLE(array) \
        BOOST_PP_IF \
            ( \
            BOOST_PP_ARRAY_SIZE(array), \
            BOOST_PP_ARRAY_DATA, \
            BOOST_PP_ARRAY_TO_TUPLE_EMPTY \
            ) \
        (array) \
/**/
#    define BOOST_PP_ARRAY_TO_TUPLE_EMPTY(array)
#
# endif

/* to_tuple.hpp
KsqLeEhhpZ/FEf04ULKfyQ5MVmafYec9C8c5o26YeZ6LfFc1xf7Oa33fle9enO+/5nZ9fAiJjfOO7l6c1h5yEidLpPiW5Tr3ptxDKzfid25LUH5jCuuq831DoTtzeE5f7meYer7TDI9M8DdD+WVJwjzkgZETwac5X8w7UOV8Ol9+1LMVx6VE+8an0G5+f5Dlb3ZXz8lz+LW8u3runlO+wqHfxd+3nXKTwVF4Zh8VEVDWSLzj6t+GsduvctERWf8=
*/