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
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
*/