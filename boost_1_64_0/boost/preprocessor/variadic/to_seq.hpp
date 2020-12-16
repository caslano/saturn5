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
# ifndef BOOST_PREPROCESSOR_VARIADIC_TO_SEQ_HPP
# define BOOST_PREPROCESSOR_VARIADIC_TO_SEQ_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/to_seq.hpp>
#
# /* BOOST_PP_VARIADIC_TO_SEQ */
#
# if BOOST_PP_VARIADICS
#    define BOOST_PP_VARIADIC_TO_SEQ(...) BOOST_PP_TUPLE_TO_SEQ((__VA_ARGS__))
# endif
#
# endif

/* to_seq.hpp
Gk6FeXAGHA7Ph6PgBbAYXggr4MVwBpwHZ8NL4XJ4GVwDF8AH4RVwG7wafgivhfvhdfAHuAwmk5br4bHwJtge3gw7w+WwG7wFngVvh73hHdDJ16Y4vQeg9yycfP2a7+tC9/YMe1XBEpgLx8GBsBQOhxPgdDgJXgAr4GxYCX8Nq+CtsBreCy+CG+Bs/m+Gc+CT8BK4A86DL8BL4StwPvwCLoRpurdhPbgYZsMr4dHwV/BEeBVsDZfCU+Cv4ZnwGtgbXgv7w2VwKLweDoc3wgJ4EyyEy+EEeAssg7fBang7nAZXwEXwTnglXAmXwlVwNVwN74W/g0/Au+F2uBbuhlXwDXgffBfeDz+AM+D3cCYM+Gk3MA3OgnXhL2FD+Ad4FHwItoYbYHv4MOwNH4H94WY4Dm6Bk+FWOB9ug4vhk/AG+BS8G26HT8Bn4XtwJ/wc7oJfwz/CZM7b52FD+BJsBF+GLeAr8AT1n6z+dvBPsL36O6q/B9wLR8O34Hj4NpwN34XL4D74e/g+fAp+BJ+DB+Br8FP4JvwL3A8/g1/AL+AP8EtYI46+HtaCX8Ec+D08Gf4Az4A+H+mBTrp+AePwT4A1YJn6K9RfCRPhNPXPVP96mAzfhHXgflgPfgUbwFrxXBthLsyCx8Am8CSYDXvCXDgaNoXTYXN4ETweXg5PhIvgyfBa2BreqP471L8StoGrYVu4DnaA69V/v/p3ws7wfXga/ASeDmtyTTsTdoBd4SDYDZbCnnAKzIO/hH3hhbAfvBL2h7+BA+HNcBBcAc+Gv4OD4UY4HD4LR8DXYAf4JRwJkxPod2EvOBqWw7FwGiyBs+A4OA+WQtlbi4iDcONxs3BLcLfjHsBtx9U9i7YGo837/XZk9Hm/jUf5jsz9jTL3t90o3//E/N8jc3//vrm/R+b9/vfP+7Xn/PbgfB496p8/5/fnXf9fUDV57MTiamcGwD+4/t95rr08w7jP8lgnIp9PKJJkuB/e05C6nq3PtQuCz3+NvkO6WtbFF44dW1xRLamynjnsu9iJ0yDa827sRX3e7d47ry1xN/hOQvsTcyrX7v5RnntHs1MxmXXKUZ9zoxu5Pr9wUmnZTGM986srx73eHGvixUaaZSMt/Hhqo3pmRXFwXXRd/DUk/j2+jiZg+viSuHbXNxf5UsVWXctW3Qhbq4LP7McgFt0Glm6DiLTnSpnrumHVb2zpN46a13KpJHud8VeS1mtNL51TkGvZyLVsRD5jzNb4n0v4y74k4ufh4ny9GAMNNOHvL9M5AnNk7T5htU0rE+8+B1kv8vrWMaQRuc8+051wrB9vElRGgxTZlSYduRNvjc5ZqNKy+DZs3XqhGEzV+r1H8tzId54ZGVyXT9u/Ve8p3wZvx+2k8d6h3x3ZCtxvcXfi7sKtxC3QOMugOsJUpveB4/7mGuf49AfmuPcm3feHO+dTvYjzKfaze5Vpm89EhlfXFWvb1vh1Q3Jtr8ikPGh3yKTdSfzGMFfSoO1L5blufLsdpUtZr9G5AqF5AnmSL7Et/tER/k3q31wvfB7BqwlGPn0ITIK94Vbi7BX92Ty/ZmJSWWlxeTV23L5HCsmt366XOLpvR+9z5kTtc6L1K+geRr+iurH6lUyYJOlq4jveBKL3K3Oi9is6bwa/xK/ja2f80foS4kc5V61nZI0lfjv8Nd33Iw4S2SOUdYJpxL8zTJFZZ+LFxno5pwpL7WeKp4n+AzHPOZkfc5jn1Co9d1ar/pO4uw7h/MmwzxdpAz/feRLRxn+WdfbR7/ce/n3pRzs78o3nDmg8+qETvlv04Unj3rmzc/rhv6Mn+n3pn/8+c/T7ybHuP8e6b3z495//XfeZD/d5x8+9zv4=
*/