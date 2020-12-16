# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_ARRAY_POP_BACK_HPP
# define BOOST_PREPROCESSOR_ARRAY_POP_BACK_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/array/elem.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/repetition/enum.hpp>
# include <boost/preprocessor/repetition/deduce_z.hpp>
#
# /* BOOST_PP_ARRAY_POP_BACK */
#
# define BOOST_PP_ARRAY_POP_BACK(array) BOOST_PP_ARRAY_POP_BACK_Z(BOOST_PP_DEDUCE_Z(), array)
#
# /* BOOST_PP_ARRAY_POP_BACK_Z */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_POP_BACK_Z(z, array) BOOST_PP_ARRAY_POP_BACK_I(z, BOOST_PP_ARRAY_SIZE(array), array)
# else
#    define BOOST_PP_ARRAY_POP_BACK_Z(z, array) BOOST_PP_ARRAY_POP_BACK_Z_D(z, array)
#    define BOOST_PP_ARRAY_POP_BACK_Z_D(z, array) BOOST_PP_ARRAY_POP_BACK_I(z, BOOST_PP_ARRAY_SIZE(array), array)
# endif
#
# define BOOST_PP_ARRAY_POP_BACK_I(z, size, array) (BOOST_PP_DEC(size), (BOOST_PP_ENUM_ ## z(BOOST_PP_DEC(size), BOOST_PP_ARRAY_POP_BACK_M, array)))
# define BOOST_PP_ARRAY_POP_BACK_M(z, n, data) BOOST_PP_ARRAY_ELEM(n, data)
#
# endif

/* pop_back.hpp
l4Gf2UN6uN9PJH0MLUfygcRT3ylHcY5gcdQekEF196LajRUfV0vgdFlBPplM5zLgMxmBnR++C+ubBfaq0raafnqeS/MzARt3Ra0b9222nYicNRhPm+pO23njkbPig3kFsO3GRJo+2lM8OGrbEIvvimepUbRBB/0+Fp/2AVOuto7vTOg9wu3sTbCVJBs9LNYa6dEvI6ldQt19Heq32wQE49x2L3CdmnPrjdC6IPy6hGLe6aha/z7Loyms/OSRtd4+y5fT7wPI0lbR35OnTnNjB+0dapECTE5iy6oe8qjfr8Bvc1fiam1XXfYutwbtCzbFxoeSNDtAfXfY7DG8DrxEsuG8k72j7x6fL2t1+24nuns3vL3ZffqFMg1+mu9/oQlfQVvu6CXXbn3BB4OHXXgfXbM7mEtlHAOfp9tzkDPe1RpuyTX8WN0W9cZHEmSomRaaenEsfdLpo/m4eL1e68K52SamvzTtA+/sJnV00aa1lm1qe1ekRSstAE6aCrzvaJo8rK5xFPC6EqlrMgG3+WC6bsvU8z1GFF7N9UvhBq5XCh/DwvMo3OT49Jh5JcJrtP708l5fbIe39/5Cpy8+sjFrw3tUuN0LX6rCES98hQq3eeEPOJGhBEvzw04ky8MfcyIDZ7Hwp4iehz/jRAZ5+HonEuPhGyl+moVvdiIJHv6ykqfVk+frTqRd3tt8O8nE43xHxelz4xxHermL/FxODdaHjH1ltY9eSCW3ltnRXaWFfbTZcx1y9Fy3rvvrar39LEthC+uo3l3L6x33sUP8TISF8/xo31bm4Xr1iS/H6xuWe7iWoSEaw2QdZi/ubgi7hATceuI5z4vXMT6cyozF3HZgPfakvYbpoWca/pn7ZPJ90ifrnLbU4q1Q5M8Jzp+OGzJ1B5gN8JethfxlT7fePNvHJeTwQvV9mjz0PWy1/vND7bXYW49zDhsVnug2gc7E4XOhm2v95zOOr/VwHcDRX81vC/h1gZ85T8vvf+shnDxznnf8Zyd6waeP82H7iCh9fU9aKdqQbbW4d3uGu6coz3Dba9m+K5aPG9nZZ1MX7iQYPzP7Woq70lc36LQQGSu1JayvqE4KaaB9Z/p1tdN7f3LzNNJQsFM1/7zj9TdPyMeGXHwD9elJpbOiul7SqLh3Y0Rv194Y6dUddz9I+4qVvv1nw7SLgxZDcdYrucjA9MqpU4NzNzHNv71f82zv991tNCbO0wyiPIdQng38fFKRMqr4w8KeR2B/OaQzinQSzJ6VDAe92fV5ZGvQsbOvl+1HxbiJnW1rpfY+mRrh/Q4DQ/fAtolsn+2pmAcYq/XtoenY0kKZoUa5LeruVKc/bchdL7Zdb52SirQQOAf5EvJ/oZTZodhPHHLUSTh1Io76X2NpxzvLtyV2eipjJhn2eWf66Egfh9s+g7sFQWtcTS9kWHvAcX3+Ptg8p5UG+AkyTDoWqDwxrfLH6BKxfpxSYX0M2hwxNpbItdOa54ZkavCM/lFqdkZTySHOr9bS9aeoXBVxIF2d00ksevRd+v36emYPt4zyflZiLD/WkqR0dAOllWbwK5xtiUwur/ZijKUyuwL5H+XQFoNBahY3xWNp0f+qN7iWYdrRQNMbW2hrMzsP2ei09rVBw3wPdBPf1w1ea1S/KNdJvQmP/zqHdJnPEONWeug1EedyNdMcO0YBOtsc1+bhWuUZok3OxnwsM9Ta3joaHzyjPT+uC6snlVCbSZjuOg1dWyKbjtHrEIKU8+wxtIbGlcji+yVeS+Xht7t4X78lRXX0FIe6OO6WM6UEPQ6rofqbZvV3NKh+tXVQf4L2JZ90TAMq12QkvjdW4YPoL/eRM5wMfFfWtr/0m/mxHGsLd9Q=
*/