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
# ifndef BOOST_PREPROCESSOR_LOGICAL_BITOR_HPP
# define BOOST_PREPROCESSOR_LOGICAL_BITOR_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_BITOR */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_BITOR(x, y) BOOST_PP_BITOR_I(x, y)
# else
#    define BOOST_PP_BITOR(x, y) BOOST_PP_BITOR_OO((x, y))
#    define BOOST_PP_BITOR_OO(par) BOOST_PP_BITOR_I ## par
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_BITOR_I(x, y) BOOST_PP_BITOR_ ## x ## y
# else
#    define BOOST_PP_BITOR_I(x, y) BOOST_PP_BITOR_ID(BOOST_PP_BITOR_ ## x ## y)
#    define BOOST_PP_BITOR_ID(id) id
# endif
#
# define BOOST_PP_BITOR_00 0
# define BOOST_PP_BITOR_01 1
# define BOOST_PP_BITOR_10 1
# define BOOST_PP_BITOR_11 1
#
# endif

/* bitor.hpp
VElPTi4zVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUh0X7NX2BQAARA0AAC4ACQAAAAAAAQAAAAAAxAAPAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfQ09PS0lFLjNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSfxPTcmQGAAD1DQAAMgAJAAAAAAABAAAAAAAPBw8AY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9DT09LSUVGSUxFLjNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSgo3zUKgFAABbDAAAMQAJAAAAAAABAAAAAADMDQ8AY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9DT09LSUVKQVIuM1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLWhBCMFggAAKASAAAyAAkAAAAAAAEAAAAAAMwTDwBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX0NPT0tJRUxJU1QuM1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJ+RekoTAQAAJUJAAA1AAkAAAAAAAEAAAAAADscDwBjdXJsLW1hc3Rlci9kb2Nz
*/