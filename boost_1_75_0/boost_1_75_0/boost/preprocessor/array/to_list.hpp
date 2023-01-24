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
# ifndef BOOST_PREPROCESSOR_ARRAY_TO_LIST_HPP
# define BOOST_PREPROCESSOR_ARRAY_TO_LIST_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/control/if.hpp>
# include <boost/preprocessor/tuple/to_list.hpp>
#
# /* BOOST_PP_ARRAY_TO_LIST */
#
#    define BOOST_PP_ARRAY_TO_LIST(array) \
        BOOST_PP_IF \
            ( \
            BOOST_PP_ARRAY_SIZE(array), \
            BOOST_PP_ARRAY_TO_LIST_DO, \
            BOOST_PP_ARRAY_TO_LIST_EMPTY \
            ) \
        (array) \
/**/
#
#    define BOOST_PP_ARRAY_TO_LIST_EMPTY(array) BOOST_PP_NIL
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_ARRAY_TO_LIST_DO(array) BOOST_PP_ARRAY_TO_LIST_I(BOOST_PP_TUPLE_TO_LIST, array)
#    define BOOST_PP_ARRAY_TO_LIST_I(m, args) BOOST_PP_ARRAY_TO_LIST_II(m, args)
#    define BOOST_PP_ARRAY_TO_LIST_II(m, args) BOOST_PP_CAT(m ## args,)
# elif BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_ARRAY_TO_LIST_DO(array) BOOST_PP_ARRAY_TO_LIST_I(array)
#    define BOOST_PP_ARRAY_TO_LIST_I(array) BOOST_PP_TUPLE_TO_LIST ## array
# else
#    define BOOST_PP_ARRAY_TO_LIST_DO(array) BOOST_PP_TUPLE_TO_LIST array
# endif
#
# endif

/* to_list.hpp
K76SbFYnddoZZAxOIZMni5kvVp4dckElx89Ec1Ir/DKLpmx4qzrPG2NQ+B3s/bQ5PAHQ/RQ5TiFjcPA+O0PEdkrseMNtuut4ahMRJQF8mbLd3oDda+moqOEHqNkVtr+h0GRWJA6WEg9SYyahct0tOURqwbnU+lurNPdPenPifMRqUVf+MkI1wjbCMMI3Qvf/ep2WSjbzvuYz0h4+yn7MglorX/J68LvqnBFco9ZOX/W91xS09cFqnvVLkGE3AYeZc+72PWKhRY+9/A5T4WbmQ5E9hdlfmyVmg9p6ySQkUb9Lh8lne9J4u0na+NkGj2h37JWXnuhoRIRmg1a2SfW/xZGnahdyiTPpMFOmztm8Lk0qQFpBEH9md7Lyrc9Na48ARcrkV6QtSCbVqTCLXnJVfyFv73fidgZhgdR2fmOw+y1csElu4NAy3XtNpUUOxZACpG6IX184oga+jef52HKH1DQDautUhgd289ezwkB0rtDygiClncGdrplbNY+1CIO8HgOknCLMrcOH+cpoKkBv8nH62JjHhX30ebcSeR7s7wt8JY668WoDbwNtA2cDc0OFW/XiTwCTC7mLwJWC2ScXwus25UbCVhpvFO/XK5iir0TxHLF8g8V3iMywajVHwUMI5lqsB5Jacm887+yHrbCTj7Wq14+LYr/85BfJ+3l2hHBFdYPvfWbCgsl/cKBwoEmgdb7qxKPKB1U+ew+l
*/