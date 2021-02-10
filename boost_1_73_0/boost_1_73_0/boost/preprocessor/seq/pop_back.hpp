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
# ifndef BOOST_PREPROCESSOR_SEQ_POP_BACK_HPP
# define BOOST_PREPROCESSOR_SEQ_POP_BACK_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/first_n.hpp>
# include <boost/preprocessor/seq/size.hpp>
#
# /* BOOST_PP_SEQ_POP_BACK */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_POP_BACK(seq) BOOST_PP_SEQ_FIRST_N(BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(seq)), seq)
# else
#    define BOOST_PP_SEQ_POP_BACK(seq) BOOST_PP_SEQ_POP_BACK_I(seq)
#    define BOOST_PP_SEQ_POP_BACK_I(seq) BOOST_PP_SEQ_FIRST_N(BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(seq)), seq)
# endif
#
# endif

/* pop_back.hpp
Y3VybC9vcHRzL0NVUkxPUFRfU1RERVJSLjNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSt2ezyMIEAACyCgAANgAJAAAAAAABAAAAAAB/nBMAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9TVFJFQU1fREVQRU5EUy4zVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUmetdQn5BAAARwsAADgACQAAAAAAAQAAAAAAnqETAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfU1RSRUFNX0RFUEVORFNfRS4zVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUtgiWwKcBQAATwwAADUACQAAAAAAAQAAAAAA9qYTAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfU1RSRUFNX1dFSUdIVC4zVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUo9D9RgFBQAAFgwAAEAACQAAAAAAAQAAAAAA7qwTAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfU1VQUFJFU1NfQ09OTkVDVF9IRUFERVJTLjNVVAUAAbZIJGBQSwECAAAKAAAA
*/