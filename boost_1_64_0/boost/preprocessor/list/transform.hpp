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
# ifndef BOOST_PREPROCESSOR_LIST_TRANSFORM_HPP
# define BOOST_PREPROCESSOR_LIST_TRANSFORM_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/list/fold_right.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_LIST_TRANSFORM */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_TRANSFORM(op, data, list) BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_LIST_FOLD_RIGHT(BOOST_PP_LIST_TRANSFORM_O, (op, data, BOOST_PP_NIL), list))
# else
#    define BOOST_PP_LIST_TRANSFORM(op, data, list) BOOST_PP_LIST_TRANSFORM_I(op, data, list)
#    define BOOST_PP_LIST_TRANSFORM_I(op, data, list) BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_LIST_FOLD_RIGHT(BOOST_PP_LIST_TRANSFORM_O, (op, data, BOOST_PP_NIL), list))
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_TRANSFORM_O(d, odr, elem) BOOST_PP_LIST_TRANSFORM_O_D(d, BOOST_PP_TUPLE_ELEM(3, 0, odr), BOOST_PP_TUPLE_ELEM(3, 1, odr), BOOST_PP_TUPLE_ELEM(3, 2, odr), elem)
# else
#    define BOOST_PP_LIST_TRANSFORM_O(d, odr, elem) BOOST_PP_LIST_TRANSFORM_O_I(d, BOOST_PP_TUPLE_REM_3 odr, elem)
#    define BOOST_PP_LIST_TRANSFORM_O_I(d, im, elem) BOOST_PP_LIST_TRANSFORM_O_D(d, im, elem)
# endif
#
# define BOOST_PP_LIST_TRANSFORM_O_D(d, op, data, res, elem) (op, data, (op(d, data, elem), res))
#
# /* BOOST_PP_LIST_TRANSFORM_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_TRANSFORM_D(d, op, data, list) BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_LIST_FOLD_RIGHT_ ## d(BOOST_PP_LIST_TRANSFORM_O, (op, data, BOOST_PP_NIL), list))
# else
#    define BOOST_PP_LIST_TRANSFORM_D(d, op, data, list) BOOST_PP_LIST_TRANSFORM_D_I(d, op, data, list)
#    define BOOST_PP_LIST_TRANSFORM_D_I(d, op, data, list) BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_LIST_FOLD_RIGHT_ ## d(BOOST_PP_LIST_TRANSFORM_O, (op, data, BOOST_PP_NIL), list))
# endif
#
# endif

/* transform.hpp
MfCrCpR91Vv50XEmADDfU/GecRx07ToF4ymExryrjcNoBgA2fT//WiUJd6AkGtnxn4fDd/GUJZ8hBuEUcAe1+/x7/eLQUWRl6itjjxZShnySx+Sk5H0i+0C7tS361W1CC9cFQhaX3Z/pqAVBJE3D/dg0FZkSYZaTSK9AFtAZo7lCHeeqfqAIuUFx6qG/rbz9vwWJ4E58iExLDhGh61vZVjei8UGQ0+kge14uum7MCKFK9MkCyNKjSnXdV85I7eGMK6dMCzAlpkNhLUwyR+rP91MqvOYbdv++NaNZiUQ34FnyDtJzeZZ7yVy/pvky+f+FSYm5G/s0dGd7sDkUlI5V6GL4NvPlQuYmzjv/SP0Wj/h/TL3oyGwYNGDYczKNo0w7y0Z2wpELnNcZcP6tyJuijiETWkw1IKKkwl3houOdpsLEj/Az4HMd3iaaHdJhZT9TCEAvtjSeimwe7UfIXzpUFVEHUwmxEKT91MGGYNRN1sGuGU7n+jKqBQUHztSCCu+RenfNrH7kyis9KgHtG9k1dJQhqbWapRvMniofTmp3Ala60aXFGWrDpI0tlw==
*/