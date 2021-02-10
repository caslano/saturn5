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
# ifndef BOOST_PREPROCESSOR_VARIADIC_DETAIL_HAS_OPT_HPP
# define BOOST_PREPROCESSOR_VARIADIC_DETAIL_HAS_OPT_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_VARIADICS && defined(__cplusplus) && __cplusplus > 201703L
#
# if BOOST_PP_VARIADICS_MSVC
# include <boost/preprocessor/cat.hpp>
# endif
#
# define BOOST_PP_VARIADIC_HAS_OPT_FUNCTION(...) \
    __VA_OPT__(,) , 1, 0 \
/**/
#
# if BOOST_PP_VARIADICS_MSVC
# define BOOST_PP_VARIADIC_HAS_OPT_ELEM0(e0, ...) BOOST_PP_CAT(BOOST_PP_VARIADIC_HAS_OPT_ELEM_0(e0,__VA_ARGS__),)
# define BOOST_PP_VARIADIC_HAS_OPT_ELEM2(e0, ...) BOOST_PP_CAT(BOOST_PP_VARIADIC_HAS_OPT_ELEM_2(e0,__VA_ARGS__),)
# else
# define BOOST_PP_VARIADIC_HAS_OPT_ELEM0(e0, ...) BOOST_PP_VARIADIC_HAS_OPT_ELEM_0(e0,__VA_ARGS__)
# define BOOST_PP_VARIADIC_HAS_OPT_ELEM2(e0, ...) BOOST_PP_VARIADIC_HAS_OPT_ELEM_2(e0,__VA_ARGS__)
# endif
# define BOOST_PP_VARIADIC_HAS_OPT_ELEM_0(e0, ...) e0
# define BOOST_PP_VARIADIC_HAS_OPT_ELEM_2(e0, e1, e2, ...) e2
#
# endif
#
# endif

/* has_opt.hpp
b29mZnQuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJ+Wm7wnAMAAEQIAAAbAAkAAAAAAAEAAAAAAOOCIQBjdXJsLW1hc3Rlci9saWIvc3RydG9vZmZ0LmhVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSl9pvbRgLAAAuHQAAHgAJAAAAAAABAAAAAADBhiEAY3VybC1tYXN0ZXIvbGliL3N5c3RlbV93aW4zMi5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUlfbH3cfAwAAkwYAAB4ACQAAAAAAAQAAAAAAHpIhAGN1cmwtbWFzdGVyL2xpYi9zeXN0ZW1fd2luMzIuaFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKoASLCECUAAA2qAAAYAAkAAAAAAAEAAAAAAIKVIQBjdXJsLW1hc3Rlci9saWIvdGVsbmV0LmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSfw50siMCAACzBAAAGAAJAAAAAAABAAAAAADRuiEAY3VybC1tYXN0ZXIvbGliL3RlbG5ldC5oVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUpZR9YiCJgAA4aYAABYACQAAAAAAAQAAAAAAM70hAGN1cmwtbWFzdGVyL2xpYi90ZnRw
*/