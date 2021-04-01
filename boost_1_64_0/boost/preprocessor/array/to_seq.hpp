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
6qMT4QMB1xHOEnKHKyRa5ZON7PqaxJNuBpjWlboLgjGQBvfPvxoa6MGOm3s2uMzT4s/URCYq5WBM7yD0V8467zztjDmn3C5J5ZvHKTAwZCrc6bsmfeTPz0lHIhZWKe7Dc4izpONKocwRvp+trqqTeaiDxlRFOmaep9+zJ4GhpPu9VzCD7J15m/AfuG7TvlBh0PJR/2vYIFX+i46fXFGqFsWBg5i9VmXPlh03ssQw5THJhOQBsGc/AcoYl08jf8QvlSBrpAVU9gv+IFM/S11o+DueJ8ih1ZylJ1HyoYTJV3umCEy7AMjNmOjz8BInqE3+w73DhJGIJJOeoqw2TJeCB5z6g11nqg1H5DaeU/yioRism19rZZfBbmiWetPW1aL4argm/sdJ52ce7rNZ9UjBzxRCaM/4Y04E/KL/KqZrDkzu0IHKE+dWn7qH/kqxUzTkn4Zr7L3frTOzUZoRlXHDw4NY7y4j4k7AZT0iIi5GnLIX+bqEVa3uvesdzWf1LOY9JhUAGJARdnMRJdJr8X08UVUYpGHVjfGyODNO6Hx/gpfiHFeuznTYziBjiw==
*/