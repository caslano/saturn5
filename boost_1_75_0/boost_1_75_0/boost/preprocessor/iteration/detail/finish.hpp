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
# include <boost/preprocessor/slot/detail/shared.hpp>
#
# undef BOOST_PP_LOCAL_FE
#
# undef BOOST_PP_LOCAL_FE_DIGIT_1
# undef BOOST_PP_LOCAL_FE_DIGIT_2
# undef BOOST_PP_LOCAL_FE_DIGIT_3
# undef BOOST_PP_LOCAL_FE_DIGIT_4
# undef BOOST_PP_LOCAL_FE_DIGIT_5
# undef BOOST_PP_LOCAL_FE_DIGIT_6
# undef BOOST_PP_LOCAL_FE_DIGIT_7
# undef BOOST_PP_LOCAL_FE_DIGIT_8
# undef BOOST_PP_LOCAL_FE_DIGIT_9
# undef BOOST_PP_LOCAL_FE_DIGIT_10
#
# if BOOST_PP_SLOT_TEMP_3 == 0
#    define BOOST_PP_LOCAL_FE_DIGIT_3 0
# elif BOOST_PP_SLOT_TEMP_3 == 1
#    define BOOST_PP_LOCAL_FE_DIGIT_3 1
# elif BOOST_PP_SLOT_TEMP_3 == 2
#    define BOOST_PP_LOCAL_FE_DIGIT_3 2
# elif BOOST_PP_SLOT_TEMP_3 == 3
#    define BOOST_PP_LOCAL_FE_DIGIT_3 3
# elif BOOST_PP_SLOT_TEMP_3 == 4
#    define BOOST_PP_LOCAL_FE_DIGIT_3 4
# elif BOOST_PP_SLOT_TEMP_3 == 5
#    define BOOST_PP_LOCAL_FE_DIGIT_3 5
# elif BOOST_PP_SLOT_TEMP_3 == 6
#    define BOOST_PP_LOCAL_FE_DIGIT_3 6
# elif BOOST_PP_SLOT_TEMP_3 == 7
#    define BOOST_PP_LOCAL_FE_DIGIT_3 7
# elif BOOST_PP_SLOT_TEMP_3 == 8
#    define BOOST_PP_LOCAL_FE_DIGIT_3 8
# elif BOOST_PP_SLOT_TEMP_3 == 9
#    define BOOST_PP_LOCAL_FE_DIGIT_3 9
# endif
#
# if BOOST_PP_SLOT_TEMP_2 == 0
#    define BOOST_PP_LOCAL_FE_DIGIT_2 0
# elif BOOST_PP_SLOT_TEMP_2 == 1
#    define BOOST_PP_LOCAL_FE_DIGIT_2 1
# elif BOOST_PP_SLOT_TEMP_2 == 2
#    define BOOST_PP_LOCAL_FE_DIGIT_2 2
# elif BOOST_PP_SLOT_TEMP_2 == 3
#    define BOOST_PP_LOCAL_FE_DIGIT_2 3
# elif BOOST_PP_SLOT_TEMP_2 == 4
#    define BOOST_PP_LOCAL_FE_DIGIT_2 4
# elif BOOST_PP_SLOT_TEMP_2 == 5
#    define BOOST_PP_LOCAL_FE_DIGIT_2 5
# elif BOOST_PP_SLOT_TEMP_2 == 6
#    define BOOST_PP_LOCAL_FE_DIGIT_2 6
# elif BOOST_PP_SLOT_TEMP_2 == 7
#    define BOOST_PP_LOCAL_FE_DIGIT_2 7
# elif BOOST_PP_SLOT_TEMP_2 == 8
#    define BOOST_PP_LOCAL_FE_DIGIT_2 8
# elif BOOST_PP_SLOT_TEMP_2 == 9
#    define BOOST_PP_LOCAL_FE_DIGIT_2 9
# endif
#
# if BOOST_PP_SLOT_TEMP_1 == 0
#    define BOOST_PP_LOCAL_FE_DIGIT_1 0
# elif BOOST_PP_SLOT_TEMP_1 == 1
#    define BOOST_PP_LOCAL_FE_DIGIT_1 1
# elif BOOST_PP_SLOT_TEMP_1 == 2
#    define BOOST_PP_LOCAL_FE_DIGIT_1 2
# elif BOOST_PP_SLOT_TEMP_1 == 3
#    define BOOST_PP_LOCAL_FE_DIGIT_1 3
# elif BOOST_PP_SLOT_TEMP_1 == 4
#    define BOOST_PP_LOCAL_FE_DIGIT_1 4
# elif BOOST_PP_SLOT_TEMP_1 == 5
#    define BOOST_PP_LOCAL_FE_DIGIT_1 5
# elif BOOST_PP_SLOT_TEMP_1 == 6
#    define BOOST_PP_LOCAL_FE_DIGIT_1 6
# elif BOOST_PP_SLOT_TEMP_1 == 7
#    define BOOST_PP_LOCAL_FE_DIGIT_1 7
# elif BOOST_PP_SLOT_TEMP_1 == 8
#    define BOOST_PP_LOCAL_FE_DIGIT_1 8
# elif BOOST_PP_SLOT_TEMP_1 == 9
#    define BOOST_PP_LOCAL_FE_DIGIT_1 9
# endif
#
# if BOOST_PP_LOCAL_FE_DIGIT_3
#    define BOOST_PP_LOCAL_FE() BOOST_PP_SLOT_CC_3(BOOST_PP_LOCAL_FE_DIGIT_3, BOOST_PP_LOCAL_FE_DIGIT_2, BOOST_PP_LOCAL_FE_DIGIT_1)
# elif BOOST_PP_LOCAL_FE_DIGIT_2
#    define BOOST_PP_LOCAL_FE() BOOST_PP_SLOT_CC_2(BOOST_PP_LOCAL_FE_DIGIT_2, BOOST_PP_LOCAL_FE_DIGIT_1)
# else
#    define BOOST_PP_LOCAL_FE() BOOST_PP_LOCAL_FE_DIGIT_1
# endif

/* finish.hpp
GG+3WTyugNpb5OBWDGUKgxtpXAyrFq0VXYdFIrgKZWGs2bF1k+UGokwd65GdQZP1iXWQs1Xfodztkw6vo0WQ98SNT+vCyk4KSFtzqKuToMzZE870jKc5Rg0gtAxKtRDgxZ2hXH+t3aFlrc/GzyIbtk6dhuQ8HlQJsNT5EkY8SXXzXblNym3mXnb3R3UIcTR9pr7y7T3sV7hVQY6vr4fnnt/TGk6v1n07qWlHvPYAnRD+fgzm0KOi0M2Ic90wPD3tfBCeS3W1BOg+Z6mgYlYlAGfnS5P6q5ChPfsJCNjO1s34ovXg5eH8ENINineoGY2KPRI1xqKomKr5cnBeYfmqT5v2y9tM22ze1rrSkQgOOZqevHcGvAvgOBQxOHuC/K6TrkRQhDwHK/VYbQVtmfcQbyExFMMlg5GFsB1QAaZmykJojSirpODVmLM3APTcN17IHcHriqdfqFrR3xBhIH8w4ajFO3rbHvzaMxTitCW/9WYX4kh6guQXIkKDLRXM1FPywbgxFxlffXK2lRoZF0U2uKDni8kbHzR+XDr6C/k1dEs497l1sHVIQ4+ArpFM804bvnkpX/DXntbwtJpwhs9InW906icGhdEN7i432KjmB28JVlz0RM3i9mb85qZmDo4iyzCFzYrddzNKc5V0B384pmd0E0Jk/vyJ+M0l/xqWnSsPRUkVyNe/m4NylcS892fNpygw9wI76g+6TCw0
*/