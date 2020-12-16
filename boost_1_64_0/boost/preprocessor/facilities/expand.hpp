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
wRuVyvyj6nniUyGx4kARDj9uFmFdKL3So965xWY6WBZSj99iY7sxXM1tvaUbJhmdiliELhuLKffxagpyTte5aaFf686KDeTRDvgoKdHeOreDSrug3VgmEfLFAxApX5A6LI/1fzVd6IB0045yQiLpLJVLv+p7PYAf5CDKHmwXvTNfR8bbKQWJK5wbXZPY/Wp8SMLds6r9xomRqkQTxTUOIK1Aay6yPflVcxIMikxkOIBvMjBP1Gyw7FJ7aw69h076yS8wjlJs9aDMtPQF1GeI9G1x2yrHuv618Wtnd3+d7rfCxCGV+VRd+ecRDtTIr2oWpTxVBCtLS58OCx/VCAlS/+gnsnGK7i8uyhZ0gJh1xFoEK1G2MWRrsaMSbSoUH5i4wU1IQmPFqOgZIhR08Hpk9Fs0JQLBdwZa46+G58Epjpnh1oHKFeCdSt08Uzhgo0uxzgk3sLFylvfJxh0D/HSjtQWfhP/7lTj3ei/DDwvVjLVY0UrSqC9MSWqw+l29CMwWp3qqdm0vUZddz0NA9dEZxb6nhjegHfqERdlXvIMVoQzl+Yjiezf0dzI2kk/lx2Dbo19xeDus3v6KuZufo85drbUagrA1GdMUMf4G75AawB4iAPAOSV+GWfMbbXT3SXxCjd7FTr2E9Et+CzB66/sNDFXrLYmvwTesXlmFZENG2XgiKV6McIaDrESwDasb3BTkeR7gJeb+sNEzobe8erHhedBQ6p0TpjtjK4mGsscFKsBboKFc34XL4cNlyBXdi3x5+CSnI2fuJbVwGjdQvkjnjwc8aHiQvyn/hJhdktq2jDdpSSYXwU1izdCw8gjuizYqWC42o5prdRNH8mkZlffpYMBXrbCYPGHqZUYLeXgZAcRiXgr+UaWiI5DpFS5qj0cyws7uGtZhh72KwzZnhJ3TNezBT62w53PYBRlh53UNu80O24PDVlphp/F5sAhrdjh9gC9zWGXT+ZZ+pjhSgMStiqBVmN1NftRsTpPvRuiIWQelTAfD6t0VZsKTPz/hUjO9M7ql57bTu8ZOb8sXTu+Fr3ZN74lPrPT6m+np404+FjQSelzM/fvNiCh4/K65QNK6hrtsPk3VwEckO6/nkc0vwUL+A77Qu/oVU/xpuLGM05oayZgB5ZDZotGiXuVwhamRxhoOdRbn6JHrsD56b6YX2gTlVi/BX14PW5svqWFU3m/i29GLka7M0tRgPbC3IsZkQqc+Xde2jhCYGUS0IGJ8NS0gdWGe23uXcix693U4RlrKzYsLws038V+u1s8RjPl5HhJLqboXFpwzuNj5EEgmenQZ6NFH+/odA/r5HW19/I49MLtg9sMcgnkA5j0Yh8PpynJn53j+n3+5+DP3G9bZOLwxk37tc7I65gJ8GuKPMn8YlF/yNxxibYjU5dsMWd7cpC6xOb16uHHv+dRdNxrcLaBCxDdxUqBFPLaOaBGUVXsQOE5amGuxP9CVxTUGrZcsIAum//v5lXOfXBPGxgUCIR5gD1xnbsBLcdvEGfUwmLPcYI84Ak2u+suan6WMeOfIU+vTp5DBuulhEuQE8na6XIOuT9M6dNN8Ou5FHDV7aquLtQJHzsR/Ha+dxTJwvo27L87o3mvleud7xg52b2a3B9Uj+vpc1BRVfGmtVUV1DprT1l+aJ5rBfHiYOxAwOjFlQuNwTruWZ0yJ3AcPMPLOB1ydL0nrF1/bP273gEhQwF5niBche/2MYgblCog5+j5ud0VHNKfhV8p+qSXs9xvyM8oYdAggO7i7S/CnM4NXMOihjOBNb3dEz0Lw3jp4QvyCRi0717KT9T8ZAYYskwCEz8E1X1yM9HDFbHwnDyD1wK1afp51FJuiGaFQKNITqpQ=
*/