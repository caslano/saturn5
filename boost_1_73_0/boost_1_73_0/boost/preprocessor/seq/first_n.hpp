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
# ifndef BOOST_PREPROCESSOR_SEQ_FIRST_N_HPP
# define BOOST_PREPROCESSOR_SEQ_FIRST_N_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/if.hpp>
# include <boost/preprocessor/seq/detail/split.hpp>
# include <boost/preprocessor/tuple/eat.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_SEQ_FIRST_N */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_FIRST_N(n, seq) BOOST_PP_IF(n, BOOST_PP_TUPLE_ELEM, BOOST_PP_TUPLE_EAT_3)(2, 0, BOOST_PP_SEQ_SPLIT(n, seq (nil)))
# else
#    define BOOST_PP_SEQ_FIRST_N(n, seq) BOOST_PP_SEQ_FIRST_N_I(n, seq)
#    define BOOST_PP_SEQ_FIRST_N_I(n, seq) BOOST_PP_IF(n, BOOST_PP_TUPLE_ELEM, BOOST_PP_TUPLE_EAT_3)(2, 0, BOOST_PP_SEQ_SPLIT(n, seq (nil)))
# endif
#
# endif

/* first_n.hpp
UEsBAgAACgAAAAgALWdKUiVHqZ35AwAAzQgAADkACQAAAAAAAQAAAAAAg+8SAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfU09DS1M1X0dTU0FQSV9ORUMuM1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJ4SNEwVQQAAEwJAAA9AAkAAAAAAAEAAAAAANzzEgBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1NPQ0tTNV9HU1NBUElfU0VSVklDRS4zVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUpLE7qM5BAAAdAkAADYACQAAAAAAAQAAAAAAlfgSAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfU1NIX0FVVEhfVFlQRVMuM1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJq5EAW9AMAAH0IAAA3AAkAAAAAAAEAAAAAACv9EgBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1NTSF9DT01QUkVTU0lPTi4zVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUlW+hMhVBAAAMgkAAD8ACQAAAAAAAQAAAAAAfQET
*/