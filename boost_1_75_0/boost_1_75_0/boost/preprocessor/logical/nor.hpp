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
# ifndef BOOST_PREPROCESSOR_LOGICAL_NOR_HPP
# define BOOST_PREPROCESSOR_LOGICAL_NOR_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/logical/bool.hpp>
# include <boost/preprocessor/logical/bitnor.hpp>
#
# /* BOOST_PP_NOR */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_NOR(p, q) BOOST_PP_BITNOR(BOOST_PP_BOOL(p), BOOST_PP_BOOL(q))
# else
#    define BOOST_PP_NOR(p, q) BOOST_PP_NOR_I(p, q)
#    define BOOST_PP_NOR_I(p, q) BOOST_PP_BITNOR(BOOST_PP_BOOL(p), BOOST_PP_BOOL(q))
# endif
#
# endif

/* nor.hpp
bJIrFyerI/8RShYS/qHwVl4XtiFgmhOruJBh163ndEuB3KakJS1OgoDF2uGrqjiWxH0rh/uDiQHELb3U2tyH1mERvvOso1KsKXb5mPeu5xJzYS2O8VSIKlrO0vzs3RQ9WC+gOYctIlxJlIUiM51K+TjdRlrWXXg7/TjFXkN16HZG+vcser10Q5hONskiRzXOUCFy2yF7jgmWU3R4es0agQHW9cqpqrRsx61bKnftC1CIRJVkZ+IjNBYthkqqDM20IpJshcQNcL4vtbO+6OxoJwjqoVXdweaUPmaYQ/pupKRF1x3YUWL7c0pZCTGj7J02q/kViy5jfY79JvPLQnpBjaa74a3hXzZsfIUOaSxVwSPqYZcL22vI9hJVtgVNlVJPO9+iyDd7NWPD+qEmh0H998x1S7DSnxpuRgxuJRMSooBK9U7/BnXkZj6ST8SsqzJ73mp/HtyLUa+nAzq+haxUaN6NOFRavm2df6Ooj1RV/fUkYs0ntxHKTgtFlCmpn2MY6GRIkLGlXGR+MmDWtOLzs3JcIzef3tKwCxMdYt2x4fRzNTRS22ohbkdzrwpdJ/fzGu1SX6jRhJFLjqBsZBM5pGiLk5siMiZCeXCkojFRe2Quksm2AoNDZJzbUbQDBT56tQU+HSag+NUhiIOQwF/73k9UOO/N7Xrl/paHsZStVrjY5qKqGBQ8qzd323OzA0pdM1drJVSNZLDnY5b3
*/