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
# ifndef BOOST_PREPROCESSOR_CONTROL_IIF_HPP
# define BOOST_PREPROCESSOR_CONTROL_IIF_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_IIF(bit, t, f) BOOST_PP_IIF_I(bit, t, f)
# else
#    define BOOST_PP_IIF(bit, t, f) BOOST_PP_IIF_OO((bit, t, f))
#    define BOOST_PP_IIF_OO(par) BOOST_PP_IIF_I ## par
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_IIF_I(bit, t, f) BOOST_PP_IIF_ ## bit(t, f)
# else
#    define BOOST_PP_IIF_I(bit, t, f) BOOST_PP_IIF_II(BOOST_PP_IIF_ ## bit(t, f))
#    define BOOST_PP_IIF_II(id) id
# endif
#
# define BOOST_PP_IIF_0(t, f) f
# define BOOST_PP_IIF_1(t, f) t
#
# endif

/* iif.hpp
LAAJAAAAAAABAAAAAAB2IwYAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvcHJveHktaGVhZGVyLmRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS87dvtIMAAACsAAAALgAJAAAAAAABAAAAAAADJgYAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvcHJveHktaW5zZWN1cmUuZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlITQHj1ggAAAKEAAAAuAAkAAAAAAAEAAAAAANsmBgBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9wcm94eS1rZXktdHlwZS5kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUnr6shJtAAAAhAAAACkACQAAAAAAAQAAAAAAsicGAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3Byb3h5LWtleS5kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUv5HVPu9AAAASgEAAC8ACQAAAAAAAQAAAAAAbygGAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3Byb3h5LW5lZ290aWF0ZS5kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUqMzB7Sj
*/