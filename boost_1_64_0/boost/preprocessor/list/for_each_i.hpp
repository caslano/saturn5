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
# ifndef BOOST_PREPROCESSOR_LIST_LIST_FOR_EACH_I_HPP
# define BOOST_PREPROCESSOR_LIST_LIST_FOR_EACH_I_HPP
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/list/adt.hpp>
# include <boost/preprocessor/repetition/for.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_LIST_FOR_EACH_I */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG() && ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_LIST_FOR_EACH_I(macro, data, list) BOOST_PP_FOR((macro, data, list, 0), BOOST_PP_LIST_FOR_EACH_I_P, BOOST_PP_LIST_FOR_EACH_I_O, BOOST_PP_LIST_FOR_EACH_I_M)
# else
#    define BOOST_PP_LIST_FOR_EACH_I(macro, data, list) BOOST_PP_LIST_FOR_EACH_I_I(macro, data, list)
#    define BOOST_PP_LIST_FOR_EACH_I_I(macro, data, list) BOOST_PP_FOR((macro, data, list, 0), BOOST_PP_LIST_FOR_EACH_I_P, BOOST_PP_LIST_FOR_EACH_I_O, BOOST_PP_LIST_FOR_EACH_I_M)
# endif
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_LIST_FOR_EACH_I_P(r, x) BOOST_PP_LIST_FOR_EACH_I_P_D x
#    define BOOST_PP_LIST_FOR_EACH_I_P_D(m, d, l, i) BOOST_PP_LIST_IS_CONS(l)
# else
#    define BOOST_PP_LIST_FOR_EACH_I_P(r, x) BOOST_PP_LIST_IS_CONS(BOOST_PP_TUPLE_ELEM(4, 2, x))
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_LIST_FOR_EACH_I_O(r, x) BOOST_PP_LIST_FOR_EACH_I_O_D x
#    define BOOST_PP_LIST_FOR_EACH_I_O_D(m, d, l, i) (m, d, BOOST_PP_LIST_REST(l), BOOST_PP_INC(i))
# else
#    define BOOST_PP_LIST_FOR_EACH_I_O(r, x) (BOOST_PP_TUPLE_ELEM(4, 0, x), BOOST_PP_TUPLE_ELEM(4, 1, x), BOOST_PP_LIST_REST(BOOST_PP_TUPLE_ELEM(4, 2, x)), BOOST_PP_INC(BOOST_PP_TUPLE_ELEM(4, 3, x)))
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_FOR_EACH_I_M(r, x) BOOST_PP_LIST_FOR_EACH_I_M_D(r, BOOST_PP_TUPLE_ELEM(4, 0, x), BOOST_PP_TUPLE_ELEM(4, 1, x), BOOST_PP_TUPLE_ELEM(4, 2, x), BOOST_PP_TUPLE_ELEM(4, 3, x))
# else
#    define BOOST_PP_LIST_FOR_EACH_I_M(r, x) BOOST_PP_LIST_FOR_EACH_I_M_I(r, BOOST_PP_TUPLE_REM_4 x)
#    define BOOST_PP_LIST_FOR_EACH_I_M_I(r, x_e) BOOST_PP_LIST_FOR_EACH_I_M_D(r, x_e)
# endif
#
# define BOOST_PP_LIST_FOR_EACH_I_M_D(r, m, d, l, i) m(r, d, i, BOOST_PP_LIST_FIRST(l))
#
# /* BOOST_PP_LIST_FOR_EACH_I_R */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_FOR_EACH_I_R(r, macro, data, list) BOOST_PP_FOR_ ## r((macro, data, list, 0), BOOST_PP_LIST_FOR_EACH_I_P, BOOST_PP_LIST_FOR_EACH_I_O, BOOST_PP_LIST_FOR_EACH_I_M)
# else
#    define BOOST_PP_LIST_FOR_EACH_I_R(r, macro, data, list) BOOST_PP_LIST_FOR_EACH_I_R_I(r, macro, data, list)
#    define BOOST_PP_LIST_FOR_EACH_I_R_I(r, macro, data, list) BOOST_PP_FOR_ ## r((macro, data, list, 0), BOOST_PP_LIST_FOR_EACH_I_P, BOOST_PP_LIST_FOR_EACH_I_O, BOOST_PP_LIST_FOR_EACH_I_M)
# endif
#
# endif

/* for_each_i.hpp
J9xFdbXVVlbB6GTEsxzp+ZqdJUcmzncncl+70thnOdqghq6C9HlLPdGpY/Oi6O6fpLudO2Si+8Ik3RZ+61J0X5yk2ya6TaL70iTdDtG9/Sp+3V7qrBRlljypoTZUNpS0unn43WgY8XL//nq2CYXSqhxE8UT/mVR/M/P6ztk+o1XKAJSxYvfW+lix+1ZCzu0h2NkvdtbBTo4/dIs5yPAZ4/Hi3Lye6WaWxB9aV/BULbI8bVlvJiFKRoE9nOuITg9f7srcaxYM7wbvxB2OiTvsPiVbdCgSUouvhRTP6EKT7/EZJe/FgjttPQ2SEQj7+r3wdZU9vM4RRW3M3LtRilrzrQ7vBl/zHXY/VIVqGo4Tmd7OFm+TjHmJVrY/m3C7OkU/QePlrtq7nTas3qAnFsvbZBZxGTTCIlkJyddF8jUbZFWQmaVoi7Eo5p16odD0i2seG2EregWGLqH1SPGFPqMr/iA+bXNCFnQutNKqHJo+Q703qd6dX6jr3UYMx611Idm9LJCBorQby2QcYPYKEQcUSK949rx3JdMrBUFJuVkdefZTsZGCIKKDsv5gVIn0wOaWU5bk2UQ8cF6e7cJz82xLIVZCXA6xcYr4PMQtEHdC1EF8B6JLJlPq7c9Nnl8lx+dXRYiv/d9nVU5rVhXuhBG13JOnVpkTMrmSlTdOFwJQSV+WrudY6pwT9AjDhRHGt2cibbZ+oudXJ0tO61nOs/nJadIwnSFzKEtgltUSn4v2XsGSh2ECljGRrnjbJG74IA2dLPyhBUazzWqYhgF1VJvKzE1iKpNSaeSSrUnaJTfoOoWXHzFJc8eHwMV06IiuleIcfrrlW45L52A8sxfjmYKES68yxzPPJtbtjY9nsPdd32Nss2KwMWnNUVWmIyDRLsLumPbVmrg9Zw7El31WZm4pnLnd8znO3DAdy5VOJFl9HQM7RMITHkE5cvvDsxrnhK+wN15lD1/haLzKEb7C2XiVM7za1bjWFV7tblzrfm6tR3IDlVY50CbpIfJywxtPszvWIXCZvbuM1pHYoPiz0N1i6KZb7VwnLrHAh7n/DWzLsNIQ/0P81NYrZIJr9F0hffwAGmiJH1e9gl5VDUOvX92qHxgROMMoHo0FdaSA2n6VR3M7g9mCLjOwJRF3PVITdVSugbW9lGeLLjXHsuvUedrfBZa/wZ3aWYJXzY85Wxww1IuxwBoLzMH+q+vigemFz+As8etq+sXrzePzZZdL7r++YXJ9cbpYXzz4KQq34lfXlTT8+lEd5KZcqU5QeqGS9oAZoYbM1Rw7utMGuUBOBtz3icnJfil+9RN6j9NI+1CS/ruvj/POIvi5xqZ+oxcXpcHCW2j63AFXNIpUrn4wuQGmxUu9gOrzmXrBL0y2Ot+yeverWBwOYd3vulLL4kq/Wk2FnXfhuQOq3qeVz0av5ZX8vNm3R/cUiBPcnLIc/UNonrbu91mDWzsOeZwo7W3/qLS3n79cFmS+hrtOP4yVvU/WmtcBoxIkI4JmFbj4eqkCkui74/dfiu7U+9ULflSEcy+ZB/2B5pzEXRPTLq+dcN/9VUTTiQWURD0Q53GnI9j1mJ1dmuUMTV+7/KPqD1UtYhMewI3H640lVhwnvuxQTyBGS44ZZYhj4/Lmy1GSkg5hkJ8pl9c15jmmvYi55t03szqEd+NaT7k1HjGu26RvZjcq4w93GrwqUikISIZXSF4pa/J4AdNyvHw5OTKCdpEcWffhjs7MwwHMIJCukqoQWD5Hg1ZZiGas9SqJOtJXSs7iBLjcea2+MxrjCigx+FTvQse81I87Qz+DWpet9yWo20SpZCDyhk0iWSsVSd1wRSxT4a5XLGbAYuMau6i7oPYFnrM=
*/