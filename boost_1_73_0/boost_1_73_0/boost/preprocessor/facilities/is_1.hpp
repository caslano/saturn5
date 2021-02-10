# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2003.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_FACILITIES_IS_1_HPP
# define BOOST_PREPROCESSOR_FACILITIES_IS_1_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/facilities/is_empty.hpp>
#
# /* BOOST_PP_IS_1 */
#
# define BOOST_PP_IS_1(x) BOOST_PP_IS_EMPTY(BOOST_PP_CAT(BOOST_PP_IS_1_HELPER_, x))
# define BOOST_PP_IS_1_HELPER_1
#
# endif

/* is_1.hpp
ZXhhbXBsZXMvZmlsZXVwbG9hZC5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUtGLfkIKEgAAhTcAACEACQAAAAAAAQAAAAAAl4EHAGN1cmwtbWFzdGVyL2RvY3MvZXhhbXBsZXMvZm9wZW4uY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJot/I63wUAAJUQAAAoAAkAAAAAAAEAAAAAAOmTBwBjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzL2Z0cC13aWxkY2FyZC5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUsOWsZClBAAAWQoAACIACQAAAAAAAQAAAAAAF5oHAGN1cmwtbWFzdGVyL2RvY3MvZXhhbXBsZXMvZnRwZ2V0LmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSrMjC1t4EAABuCwAAJgAJAAAAAAABAAAAAAAFnwcAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9mdHBnZXRpbmZvLmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSoC8fb1UEAAALCgAAJgAJAAAAAAABAAAAAAAwpAcAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9mdHBnZXRyZXNwLmNVVAUAAbZIJGBQSwEC
*/