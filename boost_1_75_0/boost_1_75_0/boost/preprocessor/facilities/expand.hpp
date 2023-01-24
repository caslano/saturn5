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
# ifndef BOOST_PREPROCESSOR_FACILITIES_EXPAND_HPP
# define BOOST_PREPROCESSOR_FACILITIES_EXPAND_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC() && ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_DMC()
#    define BOOST_PP_EXPAND(x) BOOST_PP_EXPAND_I(x)
# else
#    define BOOST_PP_EXPAND(x) BOOST_PP_EXPAND_OO((x))
#    define BOOST_PP_EXPAND_OO(par) BOOST_PP_EXPAND_I ## par
# endif
#
# define BOOST_PP_EXPAND_I(x) x
#
# endif

/* expand.hpp
Q3PiFvq4MTJCZfXIEiWYA4Xh2vbesKrd3Xr6dviLS2x8mp+TGw8emq0Hbci5MkymJt3xO99GGwSFlbukM3SZlV6ifnS22HMvx1FuS8jrvPze7KpE5NYkoICwfhVqavppmpzHFvZuTGTVYbQx/znBNXCAvGpw5HNGeo7yhOr4nzCwJtCmJ/QzUZDGo0cN+N53ks/wVJUDp/IbSyuqcZT5NeJ0SineSPlMfuYfN7daK/4r1q713uHUZOIMPz+FUpHEGZXF1IczrhiABYOdB0nutlnDWwP6ptvvsvoDWw7j4z6sVy3o3XYnp8I2VwzdA50bsqfMlaPHEaA315naFm+JS564zvvfQEXyaOfjSYtNyWBlh6skOHv66s5+qRsaC4CS+o3kwu1S4lZYYMfuDEP/u+amUFdxDkX+Q6hZTDPGBx9oTaWoW1jrS9hqObongH5ZU/tDb8YHF90fRmCwOaBYyUeY0PeLbCVgmQLdDlX/5pavmtGFd9xRgq+VD2LrXUUXLHE1lGof4DQ1/9kyVVOseuYjsfu3QD8vU/wDzfyZRSkIPrZPRsxBmOZPXaAWXbX2feR6kc2AGCVhf0aNQSN/hrJkQhfgIbSWNiUrWpHF4w2RucCA3L648wjsOyVvUdmhOT6vDhYfq5XfHOPKixbBpSRL3wMMXMp/U/a7T4M9JBLMxPQwMqz5vivqaCUvpkJ5lnF4Zcga8Sb6uk/P
*/