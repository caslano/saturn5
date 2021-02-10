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
# ifndef BOOST_PREPROCESSOR_SEQ_TO_TUPLE_HPP
# define BOOST_PREPROCESSOR_SEQ_TO_TUPLE_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/enum.hpp>
#
# /* BOOST_PP_SEQ_TO_TUPLE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_TO_TUPLE(seq) (BOOST_PP_SEQ_ENUM(seq))
# else
#    define BOOST_PP_SEQ_TO_TUPLE(seq) BOOST_PP_SEQ_TO_TUPLE_I(seq)
#    define BOOST_PP_SEQ_TO_TUPLE_I(seq) (BOOST_PP_SEQ_ENUM(seq))
# endif
#
# endif

/* to_tuple.hpp
Y3VybC9zeXN0ZW0uaFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIXEfRAVBcAAPKmAAAoAAkAAAAAAAEAAAAAAByCFQBjdXJsLW1hc3Rlci9pbmNsdWRlL2N1cmwvdHlwZWNoZWNrLWdjYy5oVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUkTjgYNmBgAAhhEAACEACQAAAAAAAQAAAAAAv5kVAGN1cmwtbWFzdGVyL2luY2x1ZGUvY3VybC91cmxhcGkuaFVUBQABtkgkYFBLAQIAAAoAAAAAAC1nSlIAAAAAAAAAAAAAAAAQAAkAAAAAAAAAEAAAAG2gFQBjdXJsLW1hc3Rlci9saWIvVVQFAAG2SCRgUEsBAgAACgAAAAAALWdKUpMG1zIBAAAAAQAAAB4ACQAAAAAAAQAAAAAApKAVAGN1cmwtbWFzdGVyL2xpYi8uZ2l0YXR0cmlidXRlc1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJWP73FUwAAAHAAAAAaAAkAAAAAAAEAAAAAAOqgFQBjdXJsLW1hc3Rlci9saWIvLmdpdGlnbm9yZVVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIy/TQL9wUAAEwQAAAeAAkAAAAAAAEAAAAAAH6hFQBjdXJs
*/