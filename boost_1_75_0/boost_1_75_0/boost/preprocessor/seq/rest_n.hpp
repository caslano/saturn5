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
# ifndef BOOST_PREPROCESSOR_SEQ_REST_N_HPP
# define BOOST_PREPROCESSOR_SEQ_REST_N_HPP
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/comparison/not_equal.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/facilities/identity.hpp>
# include <boost/preprocessor/logical/bitand.hpp>
# include <boost/preprocessor/seq/detail/is_empty.hpp>
# include <boost/preprocessor/seq/detail/split.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_SEQ_REST_N */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_REST_N(n, seq) BOOST_PP_SEQ_REST_N_DETAIL_EXEC(n, seq, BOOST_PP_SEQ_DETAIL_EMPTY_SIZE(seq))
# else
#    define BOOST_PP_SEQ_REST_N(n, seq) BOOST_PP_SEQ_REST_N_I(n, seq)
#    define BOOST_PP_SEQ_REST_N_I(n, seq) BOOST_PP_SEQ_REST_N_DETAIL_EXEC(n, seq, BOOST_PP_SEQ_DETAIL_EMPTY_SIZE(seq))
# endif
#
#    define BOOST_PP_SEQ_REST_N_DETAIL_EXEC(n, seq, size) \
        BOOST_PP_EXPR_IIF \
            ( \
            BOOST_PP_BITAND \
                ( \
                BOOST_PP_SEQ_DETAIL_IS_NOT_EMPTY_SIZE(size), \
                BOOST_PP_NOT_EQUAL(n,size) \
                ), \
            BOOST_PP_TUPLE_ELEM(2, 1, BOOST_PP_SEQ_SPLIT(BOOST_PP_INC(n), BOOST_PP_IDENTITY( (nil) seq )))() \
            ) \
/**/
#
# endif

/* rest_n.hpp
s+g28Dyt8ou7izjq2sfAO+rt1t7XOlusfmTGEr8/iO+F7t+bVMueyfIDRbOrtrrYDogHox7fok5cL18rtsMc9/fJdUiuu+v89czVfrKs9pY8J56+q1FY5nurg2qj/7nsgCa3rv9K27SOrR7q0rw8uIq1PL983V6X/2wYcDVg6oO/vknIX1y2CJzuzjcFDoO3iC9YFR+rgxfCufWbpsD91nWYzbMGl0yXwgOoUZdaXmT2l2jdaCZ/juhgKx423H/t7Qp1tRf6imSTs04P14nHfYpUT6GMoWZ3MdozamM9dHb0qyHyZNg4bazRS5Qw7vsyoRU4+KwUfUkArfy43zupwtvoUPH49H76wVfKOf/4+WhtjgkkKrZ4g4jRvxu6AD3rdHKub7+597iJOmNT2jj2j4kU6XbkciZ5oCO4DwJ92VGuJxsyyicZApuQDsEheBG+IHy8++8knzZwe1ElkALiG0y96DvKV760UCKjnYuaY4OsTLHne9AfljC61bR5Hz96rizNPfYQGU9zTdn74EEfbqIYFnwevgKDpwk6+bp679Y+bqth2zOtOzTfLLCUL4KM+sVAKbB/c5ThhP/pjye2uz+ebFNV/1xTes8lq6P844HtU2S0ivW8WkHcBZs5F1g9Wjopc6DOwI6jX9Yzd/TGmSFByZCXCDiQLh+xjquncseVOJueGj2nRdUG/R5d86RzQLpLdLpjhmvkd1YQ
*/