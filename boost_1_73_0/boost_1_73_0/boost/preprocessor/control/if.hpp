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
# ifndef BOOST_PREPROCESSOR_CONTROL_IF_HPP
# define BOOST_PREPROCESSOR_CONTROL_IF_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_IF */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_IF(cond, t, f) BOOST_PP_IIF(BOOST_PP_BOOL(cond), t, f)
# else
#    define BOOST_PP_IF(cond, t, f) BOOST_PP_IF_I(cond, t, f)
#    define BOOST_PP_IF_I(cond, t, f) BOOST_PP_IIF(BOOST_PP_BOOL(cond), t, f)
# endif
#
# endif

/* if.hpp
AAABAAAAAAAnHwYAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvcHJveHktY2VydC10eXBlLmRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSlFpE5ogAAACjAAAAKgAJAAAAAAABAAAAAAABIAYAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvcHJveHktY2VydC5kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUrqnQUF9AAAAnAAAAC0ACQAAAAAAAQAAAAAA2iAGAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3Byb3h5LWNpcGhlcnMuZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKtzqJnfgAAAJgAAAAtAAkAAAAAAAEAAAAAAKshBgBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9wcm94eS1jcmxmaWxlLmRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSfNw4DKYAAAASAQAALAAJAAAAAAABAAAAAAB9IgYAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvcHJveHktZGlnZXN0LmRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSx8iO2ToCAAApBAAA
*/