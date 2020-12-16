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
# ifndef BOOST_PREPROCESSOR_COMPARISON_EQUAL_HPP
# define BOOST_PREPROCESSOR_COMPARISON_EQUAL_HPP
#
# include <boost/preprocessor/comparison/not_equal.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/logical/compl.hpp>
#
# /* BOOST_PP_EQUAL */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EQUAL(x, y) BOOST_PP_COMPL(BOOST_PP_NOT_EQUAL(x, y))
# else
#    define BOOST_PP_EQUAL(x, y) BOOST_PP_EQUAL_I(x, y)
#    define BOOST_PP_EQUAL_I(x, y) BOOST_PP_COMPL(BOOST_PP_NOT_EQUAL(x, y))
# endif
#
# /* BOOST_PP_EQUAL_D */
#
# define BOOST_PP_EQUAL_D(d, x, y) BOOST_PP_EQUAL(x, y)
#
# endif

/* equal.hpp
+ng2QLYNHpyseOA7d2yA2S6jiEf8Ouv9m+OeakzMH6/2NjzF0ofQ+s/1qAcHks22/2zz4/RUA0Q44+1JGVl25TcVLWOC8umJipCQxW6uqakZhrNOSZrsNLCL3ZFNfQpr+4s5snJVWeW3LNcS7FnZPv/QKIBu4LzsHIf53MaWaxPsk532SQnJvvuaBN5HU3zXQgPbkQhqVG1sar1md5iIg5N/JtiVf21mrTc5Ln2cwgDNLfSklPQUR7I90fe8MP+1iXjA9Gxrv1tYrln73dJCD+xbq4B7nLlZSZN9uM5yzdq+1hZ6un1SNgFKRrZqQxvLtcC2t/Vdc0xUQwsj1bPa+a9l1etXeyUT6sajykQHS/2BMtHRcs3Km04WeiBvOluuBY57F8u1wHHv6r9WV/66WeiBz+puuRY4DidZrln5fX3EEK1s+KnMfvMu0uLdj7dLuynp4ReuTZp1d8nA3tAGGycvmNvnDTY2rPXIYI+7cHCpuV94AZtTTzNPGjW8v1FDF6XdrfmczaeZ4YkUrZH6/uDModqJ+P9E/H8i/j8R/5+I/0/E/yfi/xPx/4n4/0T8fyL+PxH/n4j/T8T/J+L/f2f835jrbaRJhw1Yhk5hrGFDw3y05xXtV72Wtl3RPrOUO6RoTbVaWnPeK06H1tNSbnAADQwERSQiIo//KquKKzC8g4ZEDImILMnjZ171EGeZqyCi0DyX3tahkZyNBcnjczWfc/kUhctx1oM9CVLP/IbXU1EYpJ4FlnpU/ztip1sKYwJfFK0FtEnwqLeixfze80zTXa6+nB73DHeQZy+u9+wJPKcl6+Rm6tjqhj/Hy/JvA5+zpN5zSnjOT9SbjoNqrmilimY3aA1/tuG9gvRxee2zG15nYVlFsLFfWa8/99D21aSuhhj4CVpUg54TjGerGiZffJw11R6jtXXruaXh9VSbAh/QntsaXg+dq9+e2+vx7iV4d2ob1gAay6aOu25gT726/9LwNro9+fX7ene9Np7Tib/aerOUbRWtsJPXJpVaaHMUrb+FNlfd29qgHW+7ygsrSur174F67VpE3e+RKj3FwHaKtljRIi2066Etog05FtoKaP2wKZVNamm3qHJnGuWOt62m1gfycF3Dx4LjdOvLy2MNr6fY7a7fnvX1eHc/gXkb1ku3p76OivaAonW30NYq2o9aLW29oiUb5Y63XYWVQcZ0Q712vavqbmt53rfQxkCbwDM6KdoPivamQTvuNhBo1WvDpobzuLDYXX+sNtfry1VdqKe9mHuudVG0a6AVQjtVaml/VuUSdWjH24Z8T8WQem3Y0sC+DHWWe6YEsfGvNrie4HhjW4PrCY4Tttfj7QvwbBK1DaW+kxTtVUVzWmjbFK23hbYd2jXQehm042xXYUGwdr1TX36p+6kO1G/UfTw+122eJGT8HOr0/g7ynPcb5setdRbUlJQUB8M/H/6hOvlyluXPNk7mH1rfznxcjx+DuvL+M3LtEMbgDz2naEj95+z8Q233hvicalyeX1W/zt312p5A20/p7J2J63s8clI1vaa4pjgIrz9rmB6oAL5+G/c2rJ6iIYDf6iB93d/geoLbiS/r8cwFz85ozLtt1DdA0aZBex0+ttKgHefzgtuTg/WeN4e6e6NzC826lW+HlgotTBg/RbsR2lxoXQza8bShwFXp5Ls+7w7Va8Pd1H0vFYc25x0/RbNx9T1o+1JraU0V7bS4Wtq93BvKp5XU0jRVznxn0OeHKTOST5yl3Dr+nson10J7TNHKLbT1Xb31NUqrpV3QFiQPfbNWS3vB+JtPH8u9A9t5y72qyo1RfCuJzSsqypvBAeqVZZ68Qnc1v4G87uqaqryCGldZUd4=
*/