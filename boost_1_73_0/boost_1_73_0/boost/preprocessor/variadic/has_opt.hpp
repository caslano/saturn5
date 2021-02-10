# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2019.                                    *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_VARIADIC_HAS_OPT_HPP
# define BOOST_PREPROCESSOR_VARIADIC_HAS_OPT_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_VARIADIC_HAS_OPT */
#
# if BOOST_PP_VARIADICS && defined(__cplusplus) && __cplusplus > 201703L
# include <boost/preprocessor/variadic/detail/has_opt.hpp>
# define BOOST_PP_VARIADIC_HAS_OPT() \
  BOOST_PP_VARIADIC_HAS_OPT_ELEM2(BOOST_PP_VARIADIC_HAS_OPT_FUNCTION(?),) \
/**/
# else
# define BOOST_PP_VARIADIC_HAS_OPT() 0
# endif
#
# endif

/* has_opt.hpp
ZWN0LmhVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSYa8Bw2kbAAA9WwAAFwAJAAAAAAABAAAAAADUyB8AY3VybC1tYXN0ZXIvbGliL3NlbmRmLmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSPRSKEWoEAAAIDQAAFwAJAAAAAAABAAAAAAB75B8AY3VybC1tYXN0ZXIvbGliL3NlbmRmLmhVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSId3x2pNGAADQXQEAGAAJAAAAAAABAAAAAAAj6R8AY3VybC1tYXN0ZXIvbGliL3NldG9wdC5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUgqfdbdTAgAASwUAABgACQAAAAAAAQAAAAAA9S8gAGN1cmwtbWFzdGVyL2xpYi9zZXRvcHQuaFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJkYG2ylQgAAFYpAAAdAAkAAAAAAAEAAAAAAIcyIABjdXJsLW1hc3Rlci9saWIvc2V0dXAtb3M0MDAuaFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlK1eglA0xIAAKc5AAAbAAkAAAAAAAEAAAAAAGA7IABjdXJsLW1hc3Rlci9saWIvc2V0dXAtdm1zLmhVVAUAAbZI
*/