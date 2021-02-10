# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2014.                                    *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_VARIADIC_DETAIL_IS_SINGLE_RETURN_HPP
# define BOOST_PREPROCESSOR_VARIADIC_DETAIL_IS_SINGLE_RETURN_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_VARIADIC_IS_SINGLE_RETURN */
#
# if BOOST_PP_VARIADICS && BOOST_PP_VARIADICS_MSVC
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/facilities/is_1.hpp>
# include <boost/preprocessor/variadic/size.hpp>
# define BOOST_PP_VARIADIC_IS_SINGLE_RETURN(sr,nsr,...) \
    BOOST_PP_IIF(BOOST_PP_IS_1(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)),sr,nsr) \
    /**/
# endif /* BOOST_PP_VARIADICS && BOOST_PP_VARIADICS_MSVC */
#
# endif /* BOOST_PREPROCESSOR_VARIADIC_DETAIL_IS_SINGLE_RETURN_HPP */

/* is_single_return.hpp
LmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS6UjvYiACAACpBAAAFgAJAAAAAAABAAAAAADy4yEAY3VybC1tYXN0ZXIvbGliL3RmdHAuaFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKLbLQhdQgAANYWAAAZAAkAAAAAAAEAAAAAAE/mIQBjdXJsLW1hc3Rlci9saWIvdGltZXZhbC5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUiGOuc9jAwAAQwgAABkACQAAAAAAAQAAAAAABO8hAGN1cmwtbWFzdGVyL2xpYi90aW1ldmFsLmhVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSe3BWfNdGAAAI+AAAGgAJAAAAAAABAAAAAACn8iEAY3VybC1tYXN0ZXIvbGliL3RyYW5zZmVyLmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSGYnx/pkEAABXDAAAGgAJAAAAAAABAAAAAAC/OSIAY3VybC1tYXN0ZXIvbGliL3RyYW5zZmVyLmhVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS953yg+WBAACz+wEAFQAJAAAAAAABAAAAAACZPiIAY3VybC1tYXN0ZXIvbGliL3VybC5jVVQFAAG2SCRgUEsBAgAA
*/