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
# ifndef BOOST_PREPROCESSOR_COMPARISON_GREATER_HPP
# define BOOST_PREPROCESSOR_COMPARISON_GREATER_HPP
#
# include <boost/preprocessor/comparison/less.hpp>
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_GREATER */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_GREATER(x, y) BOOST_PP_LESS(y, x)
# else
#    define BOOST_PP_GREATER(x, y) BOOST_PP_GREATER_I(x, y)
#    define BOOST_PP_GREATER_I(x, y) BOOST_PP_LESS(y, x)
# endif
#
# /* BOOST_PP_GREATER_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_GREATER_D(d, x, y) BOOST_PP_LESS_D(d, y, x)
# else
#    define BOOST_PP_GREATER_D(d, x, y) BOOST_PP_GREATER_D_I(d, x, y)
#    define BOOST_PP_GREATER_D_I(d, x, y) BOOST_PP_LESS_D(d, y, x)
# endif
#
# endif

/* greater.hpp
rPKivHLPDC45pxW7K4rLhkYpXa2937zbX0ti8Ywh0TC+Im/W0Ki8WSNi8hJSI+yTmGM4vucyw55XziHHea6h3FtYVeMscnmqvPFFgf9+4wH5blexJy/FOEua45FdhCG+KlWTIyryjen1KnflVGdM5PDo6OGRQyPzKgumFhntUoWw1OQkXWXFEVVFBUa+QPM+Y1Bhz0EplgdFcAuJxTx1yjoX/xD3gt7HZybMKj3WRU91UWlV1e+UKDx2iYTKisKs7HolyvIrpuRXufJcFYVlNUXMPzRTPDhqyZqKImNBxFGY4Cbz6SovNur7/RLmOP8ONyn2+yWCV5RKi+MyU3x9Cz6myJA7P5OaXMaxgBSvFWc5oGSOChp88x+8J2/GH70tL7+6rLykPrOsDLTPqkYW88vM29OLq5Mm5c2IjhhGGVPHDqv+Bi+fU+EqcRUXJWRlG+WPv0xAT456QXXAMlxWG1NUPKPINePoT/YeeuvJGxKZ5yma1pByfLzXxSf7Db4TiZxdVV35u/dNVPdNKw9eNNfBwZ/llRXW5jPyqkSVC9EnCnNNOVr3rNe91tjpGBHpzErgPaSqvHg3U2jpxmIm7v0dOyrfKFk4PoPqb0xVTUGZqzCvMn9aXso/oAFnDe85qKKyrHIKPJ0YzWdSz0EZRXxmD+o5KNGZFs/sf6YzMSWL5QAGAYGLT030XkpwGN9Z2QnGV2JqKl9c5ocq6ByXmhEfZy5UYYlIiiMjNc44/h77f0j12bgjgYQ1SzZSvEfjOzLtCaOHeOmJrC6aNMn8y5lr1DcxJX1olPH/9OzRlj/MC5MyKcajUo+jVFwqK6acaY4EMvTGIgSWOWQnJNdeyWIpVEqa3bfMJEiJlGw7616Y+TfXhLDEIteeai1mPhZyHIsL0uEVPwy9P1Db7/QMVozlpiTYvaUTDa+luqkekc4z0uNSHYpOizJHmy2o/U0fjCu0wjEhO8PoW1JmxuhIxX+4kcgCnbgs1kqY/WDxlN3kcEpSij3LqDjRnjskUrXXbMCkETFOk+OGoTd/wLicTH6ZhVPNH3VYHDkrMiYyqpaaYjdIIyMj5RuLj0s0C6sK6Zsj22wm64YSU8yBT4ZPqSnp47wPcMbnpKQmpsUlJKewvMk5OjchOyMj1ZE4ZFhWdppZR2Jiim+BzGjzL+PxI7jkHRKjufGqsnQ7sx+JE8w/MpKSUhJSEErzAWYb4lkEYv5ImmTUaCxky0VgzQLGYqLR1JSaOHRYjCHnOab829NzWUqSYqfJk0cnFhfUTPHejrikJyQ7HZPTE7wL6qiOJVc5sERqbf64cnTLnuwx/ocKpiUWQXOgi4WxMzl32O2sNn+XVLodheBtLmZxwzhKzSyKjhw2zPweMizK/I6KHOL9HhJtfg+P8l4fGROpvr3XYyKHer+jhpvfI4aOML+jh8Wo7+Hq20cf6X3eSO5PSikqKsivqCguiijlrwRviRhqPKuMTxW3jEviM5veZBoGpbrUzQJOT35JsZHddRUyFx0hIR2M1ZqhrZmb4NOMT3M+YXxa8GnJpxWfcD6t+ZwPv9rwzbOGREfFDPN+R0d5v4dFe79HDPd+j4wxv4ciieb3iBHm97DokeZ3zBDv98jIYeqb8lNqOACaevLdhaWxKXGGAhi2bJIvjgnh6Y34NObThE9bPvXjk0FBYhFFs8Q7ihYQ7/hoWyl3y0nGnLeiWeMYC+19/n6RcjUhtbRditbPUm6fog2x0L5TtDu1WtphReup19KadvPSrrDc217RPrHc27Ebv3uQvzld0QLiLB+tM+XOoVwHRQuIvfy0bt38sZef1kPRWlhoPRWtlYXWG9q1PKO1pX19Fa2jhdYf2pU=
*/