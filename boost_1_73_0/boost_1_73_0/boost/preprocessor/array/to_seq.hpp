# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_ARRAY_TO_SEQ_HPP
# define BOOST_PREPROCESSOR_ARRAY_TO_SEQ_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/control/if.hpp>
# include <boost/preprocessor/tuple/to_seq.hpp>
#
# /* BOOST_PP_ARRAY_TO_SEQ */
#
#    define BOOST_PP_ARRAY_TO_SEQ(array) \
        BOOST_PP_IF \
            ( \
            BOOST_PP_ARRAY_SIZE(array), \
            BOOST_PP_ARRAY_TO_SEQ_DO, \
            BOOST_PP_ARRAY_TO_SEQ_EMPTY \
            ) \
        (array) \
/**/
#    define BOOST_PP_ARRAY_TO_SEQ_EMPTY(array)
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_ARRAY_TO_SEQ_DO(array) BOOST_PP_ARRAY_TO_SEQ_I(BOOST_PP_TUPLE_TO_SEQ, array)
#    define BOOST_PP_ARRAY_TO_SEQ_I(m, args) BOOST_PP_ARRAY_TO_SEQ_II(m, args)
#    define BOOST_PP_ARRAY_TO_SEQ_II(m, args) BOOST_PP_CAT(m ## args,)
# elif BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_ARRAY_TO_SEQ_DO(array) BOOST_PP_ARRAY_TO_SEQ_I(array)
#    define BOOST_PP_ARRAY_TO_SEQ_I(array) BOOST_PP_TUPLE_TO_SEQ ## array
# else
#    define BOOST_PP_ARRAY_TO_SEQ_DO(array) BOOST_PP_TUPLE_TO_SEQ array
# endif
#
# endif

/* to_seq.hpp
tkgkYFBLAQIAAAoAAAAIAC1nSlKA+MdNcwEAAHQCAAAkAAkAAAAAAAEAAAAAALuZBQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9oc3RzLmRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSLW8CC/4AAACWAQAAJwAJAAAAAAABAAAAAAB5mwUAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvaHR0cDAuOS5kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUsphK6mYAAAA1QAAACcACQAAAAAAAQAAAAAAxZwFAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL2h0dHAxLjAuZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLA67MafAAAAJwAAAAnAAkAAAAAAAEAAAAAAKudBQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9odHRwMS4xLmRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSWw7kDBABAADCAQAANQAJAAAAAAABAAAAAAB1ngUAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvaHR0cDItcHJpb3Ita25vd2xlZGdlLmRVVAUAAbZIJGBQSwECAAAK
*/