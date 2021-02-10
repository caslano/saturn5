# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2019.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_FACILITIES_CHECK_EMPTY_HPP
# define BOOST_PREPROCESSOR_FACILITIES_CHECK_EMPTY_HPP
# include <boost/preprocessor/variadic/has_opt.hpp>
# if BOOST_PP_VARIADIC_HAS_OPT()
# include <boost/preprocessor/facilities/is_empty_variadic.hpp>
# define BOOST_PP_CHECK_EMPTY(...) BOOST_PP_IS_EMPTY_OPT(__VA_ARGS__)
# endif /* BOOST_PP_VARIADIC_HAS_OPT() */
# endif /* BOOST_PREPROCESSOR_FACILITIES_CHECK_EMPTY_HPP */

/* check_empty.hpp
VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUkcDxXjqAAAAkgEAACUACQAAAAAAAQAAAAAApLUGAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3hhdHRyLmRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSFHMVos4GAAAqEQAAHgAJAAAAAAABAAAAAADatgYAY3VybC1tYXN0ZXIvZG9jcy9jdXJsLWNvbmZpZy4xVVQFAAG2SCRgUEsBAgAACgAAAAAALWdKUgAAAAAAAAAAAAAAABoACQAAAAAAAAAQAAAA7b0GAGN1cmwtbWFzdGVyL2RvY3MvZXhhbXBsZXMvVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUtwiP+QvAAAAOgAAACMACQAAAAAAAQAAAAAALr4GAGN1cmwtbWFzdGVyL2RvY3MvZXhhbXBsZXMvLmNoZWNrc3JjVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUp4sO37ZAQAALAQAACQACQAAAAAAAQAAAAAAp74GAGN1cmwtbWFzdGVyL2RvY3MvZXhhbXBsZXMvLmdpdGlnbm9yZVVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKwgcL2YwYAAPgQAAAoAAkAAAAAAAEAAAAAAMvA
*/