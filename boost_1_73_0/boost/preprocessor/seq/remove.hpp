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
# ifndef BOOST_PREPROCESSOR_SEQ_REMOVE_HPP
# define BOOST_PREPROCESSOR_SEQ_REMOVE_HPP
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/first_n.hpp>
# include <boost/preprocessor/seq/rest_n.hpp>
#
# /* BOOST_PP_SEQ_REMOVE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_REMOVE(seq, i) BOOST_PP_SEQ_FIRST_N(i, seq) BOOST_PP_SEQ_REST_N(BOOST_PP_INC(i), seq)
# else
#    define BOOST_PP_SEQ_REMOVE(seq, i) BOOST_PP_SEQ_REMOVE_I(seq, i)
#    define BOOST_PP_SEQ_REMOVE_I(seq, i) BOOST_PP_SEQ_FIRST_N(i, seq) BOOST_PP_SEQ_REST_N(BOOST_PP_INC(i), seq)
# endif
#
# endif

/* remove.hpp
+C6sqYav4O6wwfjcJ5Abut18ii4Hz2ryd8opW4oxwPiKYC2Q/oIuGZ8zRyOHmx2Zu1gHNNnGXUH0kfmkWZEvkcEV2KhLOPZzckV0gjnJD5vyDv5I4AeMW+TsHpj9e3H2MYBzbGXWB5xnthJsCf5pHJ85e+Krmzu/u7hTwtwJ/HU36TkHMY/Pol9LCbajmEhBH9ZPxYkXTL+VIBz5fcvZZQL1LMn1LE3asKlYbDfrSc5nvuZ7
*/