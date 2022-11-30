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
# include <boost/preprocessor/control/if.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
# include <boost/preprocessor/variadic/has_opt.hpp>
#
# /* BOOST_PP_ARRAY_ENUM */
#
# if BOOST_PP_VARIADIC_HAS_OPT()
#    if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#        define BOOST_PP_ARRAY_ENUM_NOT_EMPTY(array) BOOST_PP_ARRAY_ENUM_I(BOOST_PP_TUPLE_REM_CTOR, array)
#        define BOOST_PP_ARRAY_ENUM_I(m, args) BOOST_PP_ARRAY_ENUM_II(m, args)
#        define BOOST_PP_ARRAY_ENUM_II(m, args) BOOST_PP_CAT(m ## args,)
#    elif BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#        define BOOST_PP_ARRAY_ENUM_NOT_EMPTY(array) BOOST_PP_ARRAY_ENUM_I(array)
#        define BOOST_PP_ARRAY_ENUM_I(array) BOOST_PP_TUPLE_REM_CTOR ## array
#    else
#        define BOOST_PP_ARRAY_ENUM_NOT_EMPTY(array) BOOST_PP_TUPLE_REM_CTOR array
#    endif
#    define BOOST_PP_ARRAY_ENUM_EMPTY(array)
#    define BOOST_PP_ARRAY_ENUM(array) BOOST_PP_IF(BOOST_PP_ARRAY_SIZE(array),BOOST_PP_ARRAY_ENUM_NOT_EMPTY,BOOST_PP_ARRAY_ENUM_EMPTY)(array)
# elif BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
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
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
*/