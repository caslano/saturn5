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
# ifndef BOOST_PREPROCESSOR_ARITHMETIC_DIV_HPP
# define BOOST_PREPROCESSOR_ARITHMETIC_DIV_HPP
#
# include <boost/preprocessor/arithmetic/detail/div_base.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_DIV */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_DIV(x, y) BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_DIV_BASE(x, y))
# else
#    define BOOST_PP_DIV(x, y) BOOST_PP_DIV_I(x, y)
#    define BOOST_PP_DIV_I(x, y) BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_DIV_BASE(x, y))
# endif
#
# /* BOOST_PP_DIV_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_DIV_D(d, x, y) BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_DIV_BASE_D(d, x, y))
# else
#    define BOOST_PP_DIV_D(d, x, y) BOOST_PP_DIV_D_I(d, x, y)
#    define BOOST_PP_DIV_D_I(d, x, y) BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_DIV_BASE_D(d, x, y))
# endif
#
# endif

/* div.hpp
OhlW29iUPpL7vXxJOReWMoNp1Q8YmqLfG3sOamus7JHcFg8yrSc36Y5r9rrg6BlbNtmf4wbDS8j/044RZLb2S5s4qY6g3ETgemzlmQkf8AEZMJqyDIZlZPUcZl8lGmSlaeRuEKzyQxz1lgSXlKw6RW9pU9sFtwoV6T69b3i087wiX5jcO3D4gDITHeZm+laW9kIbmWksEThq28Fg0loZU3wD98NKkYUyR7QWR4CMb2ZHKte9yNdtQX52Rdtj0FW/B6ZWS7EewTsD681Z7asNAvCJ80OKLsy+0dj6OcJzGDEQ34VgJ6uos+Dri3ZKA6t21OF2p7M3efY82z8aoYeIR5Gi6v9teVmYbbZMdjTNbYEZRsGpVn6ouVc2MC6b3Y56l+JFrFgOME/7Z97hxZIoxTKvgxGHP+wRU+NgJnxhgCgoRU9R7qbaZ5ai97YdrldjOfmZrZ7zzdkOUMV2pMXgPAmZVynNPnZ+h7ivmpW7Le+gqnUftMWeYK/rCSBmwmbtBLE3l+itbE0CM+2rMzZAWt/Rd+L4oHRLPBbI7Dr3ELzkNZ4+k0kI8/elbA==
*/