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
# ifndef BOOST_PREPROCESSOR_LIST_ENUM_HPP
# define BOOST_PREPROCESSOR_LIST_ENUM_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/list/for_each_i.hpp>
# include <boost/preprocessor/punctuation/comma_if.hpp>
#
# /* BOOST_PP_LIST_ENUM */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_ENUM(list) BOOST_PP_LIST_FOR_EACH_I(BOOST_PP_LIST_ENUM_O, BOOST_PP_NIL, list)
# else
#    define BOOST_PP_LIST_ENUM(list) BOOST_PP_LIST_ENUM_I(list)
#    define BOOST_PP_LIST_ENUM_I(list) BOOST_PP_LIST_FOR_EACH_I(BOOST_PP_LIST_ENUM_O, BOOST_PP_NIL, list)
# endif
#
# define BOOST_PP_LIST_ENUM_O(r, _, i, elem) BOOST_PP_COMMA_IF(i) elem
#
# /* BOOST_PP_LIST_ENUM_R */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_ENUM_R(r, list) BOOST_PP_LIST_FOR_EACH_I_R(r, BOOST_PP_LIST_ENUM_O, BOOST_PP_NIL, list)
# else
#    define BOOST_PP_LIST_ENUM_R(r, list) BOOST_PP_LIST_ENUM_R_I(r, list)
#    define BOOST_PP_LIST_ENUM_R_I(r, list) BOOST_PP_LIST_FOR_EACH_I_R(r, BOOST_PP_LIST_ENUM_O, BOOST_PP_NIL, list)
# endif
#
# endif

/* enum.hpp
oMv7HIuM5qB8aAXLnulPJ2V5H8QR84W9+RedlVGDNkS0yByOSB1V1nnH5COg9f2MDXZBNlpRBwslTgzjW3o3gg2ewYKc298PGhY/b/9rntHIIvYC4WT9Wf+KYxQuuYd5THxrGoWZDGAkxdOWS9O/rdtUy805HckfctUXntlCNFECV/LcklRnfdeQ6JhdQ0R/GaJsiL9ToFyRqIIipCfH2iDmv/NCHX/TOQGzb+0YpUKWkFYBZxZjvgZRvCuQI+offf9lvgBIOILIrdLGXcH+91jE9ngYUEz98Gw7jA6WBR54zINdfzqzIPEMTEzdrEL+jahRkmu5YXrvr4psIVF4alw32FCK2k3DJ/NVbyY9fQ2cKonyPSEs6gTVloRb2zav4KcosAYM3LW7Z0gB6sJc9oLzJYjeaCB2FR6jc0AruZ9iunkC2diL+fKDcNZ4S8oHvHTFwAEqZmvB091ZwOAjarmIKvuYn1pBAw6pz5jJ/gCwvQOKRbK79PjB7cXnnmUNec8LQdPLyMF4WCzkPRkD8USnsGDycyvBxlX6z5v0u4SgfQWAPAxPkxRnjw==
*/