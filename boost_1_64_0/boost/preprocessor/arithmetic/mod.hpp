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
# ifndef BOOST_PREPROCESSOR_ARITHMETIC_MOD_HPP
# define BOOST_PREPROCESSOR_ARITHMETIC_MOD_HPP
#
# include <boost/preprocessor/arithmetic/detail/div_base.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_MOD */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_MOD(x, y) BOOST_PP_TUPLE_ELEM(3, 1, BOOST_PP_DIV_BASE(x, y))
# else
#    define BOOST_PP_MOD(x, y) BOOST_PP_MOD_I(x, y)
#    define BOOST_PP_MOD_I(x, y) BOOST_PP_TUPLE_ELEM(3, 1, BOOST_PP_DIV_BASE(x, y))
# endif
#
# /* BOOST_PP_MOD_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_MOD_D(d, x, y) BOOST_PP_TUPLE_ELEM(3, 1, BOOST_PP_DIV_BASE_D(d, x, y))
# else
#    define BOOST_PP_MOD_D(d, x, y) BOOST_PP_MOD_D_I(d, x, y)
#    define BOOST_PP_MOD_D_I(d, x, y) BOOST_PP_TUPLE_ELEM(3, 1, BOOST_PP_DIV_BASE_D(d, x, y))
# endif
#
# endif

/* mod.hpp
p6/x9qmIsUpgn3Ia9VHl7TbTnw7yQz30lnzCvfv8GxhfWB5szPvNf3NscbsYW9zB/cv05+J0n3KP6JN+G7bxHdZ2voPZ1/eEfd1ZRZ+wr7vA4/uT9aGLGsPSWbEqf7t9t8ozxsekdWZTdL+UfkXI61P9iOunyD1YR4g+971CPz9G3u5jffY087k/Ze3m/UJXP6tSn7ifFPx+wfgdyvg9wPg9KPj9qoo+we8h8Pu1yMf588Q5K9A9LOgawO8mzEX9HnR/YPYwxGR6VMj0WBV9QqbHweOPIq0nhExPgO5Jlla1iLMPvJXP0FpCnKfNvDjsZI/GD8SyfG1UzYcmxvJjdk4UZ98AM3NGf+Xjiv3Yq3ClXBuAzPdC5r9B5r8LuqOFrf0DdM8zfTzJ6uILQvcvVtEndO/Md2lL5k9212N8kF/LZELcT/QI2ULgOxN8ja3y/BxAOBXnMOS7DHEOnF/gbJIdH4qDLxLO5PqksKFypDGHyfUI09khBOc6C1OYPp/OKsCjkvG4VcwPz0Ocn6OeVCHOfBunhPYdsjWF+WxNQchQM199Yk0B/Grn+9N9lSiHQ0F3GJM1IcphyXxxFgZxDmdxHhT5ewh6PWK+G2c54rwMcWye+Jw70jkPOlmJOC9n5W1tb5rlbc45HU285DmnVRomzznJ/dYBcPj804W+6pGPJcj7auSjgeU9z3xgoyjPY+erT5xNAY9XCp29TJTncaBby9L6FbPfdSKtV8+nT6S1Hjxew3j8WJRvC+LsQd3cgDitQr4jhO1EQNfOeP9U6G8T4pwJ3h2Is1nI3j7P/bjsnfP951DmBJwV6eL5xfkQxLH3BeXFGO0EyNALGXgadaGJafQjDZW+TKNznpuOjHOiKIc+E4flVcY5eT7n647B8uJMyimcpoC8p3KaAmmdBh2kQxPP7AwI2QcpzM/UNNLXRN8acXYpTnRLie4Acd+T+er0x+Mc4IwYWS0tm1eGrAlGo3A5BRV6OYNo1LxTGvNOlI19ge3bJHN0eq530rax8DyU1iW3aSYrXwPMQO9ZQ0u4xRV8PF4SrmVnLXeIOrhT2PtZ8730FJ+l3IdQemcL/GFyzpfhibeVl+g0/hyCKZly7E7M3UKmc4VMb7Y8Ccd4ZsMuz7cw/GEk051z/TK/DWnOYXo4X6T5DpHmBZYn4VialyPNC8HzlSwfFwmeFwueeyxPwjGejeB5yfwCdybDNum3rheXMj4H4z13XgaXGzz4dIpzOFdA9rzjys7PVdG3j59jywbcyfYB5OuksD27iDx7PjeNPH9IyCJ98kdU/4TwM4Evt+/Ty3RnOh8V+lkD3yHnfT7O6DhPSfdJ5gfyIc/HcF9xDeO1u9KlmQN/xXl9OqDsePuSB91nUV8H+Z445PVzhJN+9XqCGd3WATeCc9E3gNcIeCncjQQDDnxsGGmxfIYhG9L6IuziWGbTt4g2TeXrVoKRDD45v2TlJLxI+ysU5mdbo9Ahv3ebn239mpQVdDy92wRNY4CdfpPZlmxnpG3dwcpvBtpA9f3Sd1455HwbOv8O14uor1yG7wn7X+qI+QyWj+cK5OMHjIeCyTOwd0Omk+fxuVFezjJOyLlX6M/QcNu/z+iEt7uwa66Tn85nd0C+xc93TkB+fs74mj5JDjrnMv7SyMjo9go7eBBpz5hop/p7aL7YYwobX8vmQX7r+W2i8+C/m8/0ifL5Peqo9CV/EOW4NyDfj0LWZWHO1/po/T0+38/3j6zuMH3ir6Sf5TzB+kzk97SsFUQ7D/dxLsBf3mf6M7OvBOojt6+neBq485HXqxzKx7RVvF79FXkeClsd02+2p1L0cf7OfOAKtIvPMd/yrBgzPO/ll3A=
*/