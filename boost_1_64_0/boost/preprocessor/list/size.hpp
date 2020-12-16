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
# ifndef BOOST_PREPROCESSOR_LIST_SIZE_HPP
# define BOOST_PREPROCESSOR_LIST_SIZE_HPP
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/list/adt.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_LIST_SIZE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_SIZE(list) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE(BOOST_PP_LIST_SIZE_P, BOOST_PP_LIST_SIZE_O, (0, list)))
# else
#    define BOOST_PP_LIST_SIZE(list) BOOST_PP_LIST_SIZE_I(list)
#    define BOOST_PP_LIST_SIZE_I(list) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE(BOOST_PP_LIST_SIZE_P, BOOST_PP_LIST_SIZE_O, (0, list)))
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_SIZE_P(d, rl) BOOST_PP_LIST_IS_CONS(BOOST_PP_TUPLE_ELEM(2, 1, rl))
# else
#    define BOOST_PP_LIST_SIZE_P(d, rl) BOOST_PP_LIST_SIZE_P_I(BOOST_PP_TUPLE_REM_2 rl)
#    define BOOST_PP_LIST_SIZE_P_I(im) BOOST_PP_LIST_SIZE_P_II(im)
#    define BOOST_PP_LIST_SIZE_P_II(r, l) BOOST_PP_LIST_IS_CONS(l)
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_SIZE_O(d, rl) (BOOST_PP_INC(BOOST_PP_TUPLE_ELEM(2, 0, rl)), BOOST_PP_LIST_REST(BOOST_PP_TUPLE_ELEM(2, 1, rl)))
# else
#    define BOOST_PP_LIST_SIZE_O(d, rl) BOOST_PP_LIST_SIZE_O_I(BOOST_PP_TUPLE_REM_2 rl)
#    define BOOST_PP_LIST_SIZE_O_I(im) BOOST_PP_LIST_SIZE_O_II(im)
#    define BOOST_PP_LIST_SIZE_O_II(r, l) (BOOST_PP_INC(r), BOOST_PP_LIST_REST(l))
# endif
#
# /* BOOST_PP_LIST_SIZE_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_SIZE_D(d, list) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE_ ## d(BOOST_PP_LIST_SIZE_P, BOOST_PP_LIST_SIZE_O, (0, list)))
# else
#    define BOOST_PP_LIST_SIZE_D(d, list) BOOST_PP_LIST_SIZE_D_I(d, list)
#    define BOOST_PP_LIST_SIZE_D_I(d, list) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE_ ## d(BOOST_PP_LIST_SIZE_P, BOOST_PP_LIST_SIZE_O, (0, list)))
# endif
#
# endif

/* size.hpp
q8g907hmHNMUftJg58f58LhKP0DdNxL1B0Pl+fAHWYspU8V6DVhslSVKwgThRm8ze6EOv9S8IZEvvocTcNoXBSH04ZJ9B44229fDFN97hzfh0fCLS15KemRm892Jmxvzlx0TWyNJj8xgsXmFa3I2LCP6RlB8UvSKHmQ4GyvLcOEXw39rXD9Gux/ZYut39S+H3Nr6322W9T+J8SO9tUcX415zyFFzgrM3N06r3Z0Y+aVkyjHYKw2dKPHFUZ7NtStLgx+Bi0NXSgwPHA3valw/+qMlT4f7DnyMr114wvvCnxyINCcXdZXaSm0fPDhv7+YPHgyvH936OiJWc+f0dbV7j62ST2JcvTk8QwcUXRV+dclrdH7pf3QePVPWLDbX3pW4OGRGDnGJzuJR2G09jWtGoETihJEcUrjmyTrM+rElfz7wSfAkjNsexoKuuWvXJJ8AkTzL9ar2T2P5tJ8vSGNksDCAv6KJ0FjguBqM1sUnxx7MatIn8xjfKEJnZynuWFs2isvj64Nv9F5dm1kuWVyetV9qa3RvjU7TsWaUM6Q+zK+DCzq+L96O4svL9MHo8KG6JoTXO6XsQqbW5esXVW8ckhMX68czX1DzZNH8rU0s3jJ3fnNKK3wym1+aTm6DvROv/aeSHL2X9W7q+vjJ6Fa5Pl47cVLwJv02Fd6enLEm9rWYVI7YeIjIr355FqMpq2ApZ5szLMvmj94enwioWz8j2tjVUzeaU/yAMRL3bvhMGltHrKasn1y8nOMdmXMhbm9cJCfxFNZkrDeZHfptJ9QXv48Dtdc4Na4/0iVLAY+mzlyDcXvvBo4d0qAIqGqGl4yRZchlZFDrJmo5UBAPQi+bej5TL6nIyKFGPjWca7EkUH0PulDGd9KKR1cyzz8geIltKmLrQtLgqe9Pix1P2GXT5yi2cEb6F+v1DdRrMeAcvTEtdsjkHj0lzrIF0/zq6DLrZPsivh9EH/6GrACXWUebovKpGbTuObKdcUaaWGJQMrvCEss70DFftHoVUr+s6XGVOqAeY7DZMta3Vpb86hTL4+BsM3uQcLutHe0zrbNk1LWef5nkl4zQc/RKl3ryHNrjO7gN8Wz/8Ay9LtpmntjI96pjZ1NLDZxrndu5VZo7eIVHkFgF1F4YmUlWpBcnyhE7e1hFT7MmrRK0uhuG5pZqUl2OBIEVsGw5PMYd30uz6Q1W3IzQ3ICalhF720OGuRIbEWoDo+7g+zUK+/CRIevN0aV4eDm1cHYsa1+DETYo/3hRLPue0ZaLdWYfHo5ldrs+V1ESXIxzGdlWts4XWyfCXzA7lqGwVxq8UrJz49mx7JTJBvItHbM8xBCqaqiysJoBlR/bPdIMQifXa53iHjzbyt1M2VeQJIIoxJ5b4JiOVXDh4+auX82c+P1HKXyY6wPqyjQdzYOxYwMzz6AOymeZLXSCT52v1TdsCu++TsqDtf55iYzo9OgfGpIR8GS+nCCLvwK9ZF/trunROeHnJ2s135lglM6Qmvf1RzljD4+I09U8HavGTtcLry9mnxY8g/WhZtkFQfeqmmW20IcBowIO/epPSM2o59kEm6WxRzRm4rjMo9o5RzspfpUyaY90KY4QqEfPtHJ+vhGMF9rc03WjMBepi9c3JcdCEear8atpclhjOkLBu8NSxuwp+swMDNGAX7O7q03Gu5svnjzebYVWUeZBvWCjz1J2QCsp0IMlH8yZKrBv2Jq6B0YyFO6EEZSdNv504QdWvBDFEIUQadBu16Y79U+3tpQr+1oILwN5jB8UY/kZ0D/5WjNX/+TID0oTpP02SksgPaSlyZAOalfbtI4BaYf5wuRp2sStPfLoH5f+SU6AHX3FwPQaStMSREo=
*/