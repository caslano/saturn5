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
# ifndef BOOST_PREPROCESSOR_SEQ_TO_ARRAY_HPP
# define BOOST_PREPROCESSOR_SEQ_TO_ARRAY_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/enum.hpp>
# include <boost/preprocessor/seq/size.hpp>
#
# /* BOOST_PP_SEQ_TO_ARRAY */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_TO_ARRAY(seq) (BOOST_PP_SEQ_SIZE(seq), (BOOST_PP_SEQ_ENUM(seq)))
# else
#    define BOOST_PP_SEQ_TO_ARRAY(seq) BOOST_PP_SEQ_TO_ARRAY_I(seq)
#    define BOOST_PP_SEQ_TO_ARRAY_I(seq) (BOOST_PP_SEQ_SIZE(seq), (BOOST_PP_SEQ_ENUM(seq)))
# endif
#
# endif

/* to_array.hpp
Ifm2ghgvs1zyJ3xVAdriBU2Qbw3ybEQbKXtp4ewzeVm8VY24ZhpBzlybKsjVhXoKbXazvvvr1nlSSSt8g9nnLshOt/rzpHk2CDOsz2dgkqmz1GkbFDPlA9xGIVXyWfXu7qK+u1r3Ge92JcyTuJzjuLaOvvFxRYaFqIcPfUp7C5LWsyJ1KUg9PGiLO3UnrLab9Ucgvq9k1W9XM+ocaT07Q1aSRn0Gw17K2wf74SM4AAfhEByG
*/