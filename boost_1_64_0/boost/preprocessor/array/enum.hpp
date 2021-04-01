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
# ifndef BOOST_PREPROCESSOR_ARRAY_ENUM_HPP
# define BOOST_PREPROCESSOR_ARRAY_ENUM_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_ARRAY_ENUM */
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_ARRAY_ENUM(array) BOOST_PP_ARRAY_ENUM_I(BOOST_PP_TUPLE_REM_CTOR, array)
#    define BOOST_PP_ARRAY_ENUM_I(m, args) BOOST_PP_ARRAY_ENUM_II(m, args)
#    define BOOST_PP_ARRAY_ENUM_II(m, args) BOOST_PP_CAT(m ## args,)
# elif BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_ARRAY_ENUM(array) BOOST_PP_ARRAY_ENUM_I(array)
#    define BOOST_PP_ARRAY_ENUM_I(array) BOOST_PP_TUPLE_REM_CTOR ## array
# else
#    define BOOST_PP_ARRAY_ENUM(array) BOOST_PP_TUPLE_REM_CTOR array
# endif
#
# endif

/* enum.hpp
LvGiJV7WUnpylWeMdfvisUYptIg9Qp2XjN6nUkgYKCeICOSdeuqxTCBsVLXE2uzwM5eFcp3UD33Rg+Xt/ZawgZMlR7JuRPa9e5MbyqTe7InuAjLn3v0C4QAC/5kCHY3TD9SjefCR/7DHaVZUeChv4f+n4iOgOO912SHCT3yuKQALDXokVwes5hqnkyuOm8iXheUd4Q5hOYMT7lbVWnBsIxRNgy7cdfNG2Q2lEJkZtX6Hml3ZSjpY/WQTKeZvNXqKcc6E0uGAJ9nwBTP3m/t77w0KowUBFXOCl61WxPH23nmnWaWsFlVo/JELF9k4y8JvHMAzYcgmixTgZlVOtw15gSiSNlVA9GNGSDz5D8O2eQ9jkP5fvQNZDQPJ1/mdWxqu+J52Sd1jACfrdeU9S6WrUoeLdVF/qsWCLMFn6Z4m/huRrnwvaa7dCS7AdkbcgDivO0lV+GwoJXq15+p1sEVJv6v2qgWuX6/KliQnUSsIPRij41oFCjtJjK/LjFWmXmEI2eQooiAsE8U2x0OGOyXfs1efpT/F8U2sdAq2jsXMogku9fMK+sjN/0C2Kg==
*/