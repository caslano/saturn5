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
# ifndef BOOST_PREPROCESSOR_DEBUG_ERROR_HPP
# define BOOST_PREPROCESSOR_DEBUG_ERROR_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_ERROR */
#
# if BOOST_PP_CONFIG_ERRORS
#    define BOOST_PP_ERROR(code) BOOST_PP_CAT(BOOST_PP_ERROR_, code)
# endif
#
# define BOOST_PP_ERROR_0x0000 BOOST_PP_ERROR(0x0000, BOOST_PP_INDEX_OUT_OF_BOUNDS)
# define BOOST_PP_ERROR_0x0001 BOOST_PP_ERROR(0x0001, BOOST_PP_WHILE_OVERFLOW)
# define BOOST_PP_ERROR_0x0002 BOOST_PP_ERROR(0x0002, BOOST_PP_FOR_OVERFLOW)
# define BOOST_PP_ERROR_0x0003 BOOST_PP_ERROR(0x0003, BOOST_PP_REPEAT_OVERFLOW)
# define BOOST_PP_ERROR_0x0004 BOOST_PP_ERROR(0x0004, BOOST_PP_LIST_FOLD_OVERFLOW)
# define BOOST_PP_ERROR_0x0005 BOOST_PP_ERROR(0x0005, BOOST_PP_SEQ_FOLD_OVERFLOW)
# define BOOST_PP_ERROR_0x0006 BOOST_PP_ERROR(0x0006, BOOST_PP_ARITHMETIC_OVERFLOW)
# define BOOST_PP_ERROR_0x0007 BOOST_PP_ERROR(0x0007, BOOST_PP_DIVISION_BY_ZERO)
#
# endif

/* error.hpp
YfKJK9keP2T/Iov51w6VTRhAOB7grsTxxeyHR9NYFHklFVOpOWcO8ou3XsYGrgJXpUpO2uBX5MnjVddI6lNQn1ve9mosa5dGTn0fCHMf4Augt0G/C5zaFx5hZaudLwiJh6A6ZOmLkftrJROLuQpZec3Hht/dZwK8XvqQxsRn6RAGwEXx/pYlPBlWWrf0Iy2ourL7EJyE30jH0/ph3/BZgpMlKt7ZwJLtssqXEUEP3DcgrhEB53FLWD5fa/ol+e9B9nFBY7D4eLGhZwGCJ5019jEg1a9KJkk+zsNBd5WbkANZIoEpyZ+W3uSn3SkK3K/ZT8CEvyhXtT53c+zFKuqWceFLNVGRoEbE3RrCXJWW0bktOsV1yjxPg8CIvSfzXj/m6gR+04EbfneQQs5A0E9tICP+UqltjB1HAPRqFHQlfzdJmz1TYsbr/O4dbNLK+uFbw6sC+igJ43gAIirNi3aS/ouMNzDYjPcAVBpVZ/+NqrN45tRcXvltX5ExWfsRtRtxVWglaOftA22Wd8ELAncZHTEGfHdXQGwPkXg19laza+oQi+frtuRVrDmP1Q==
*/