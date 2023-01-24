# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_LIST_FOLD_RIGHT_HPP
# define BOOST_PREPROCESSOR_LIST_FOLD_RIGHT_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/debug/error.hpp>
# include <boost/preprocessor/detail/auto_rec.hpp>
#
# if 0
#    define BOOST_PP_LIST_FOLD_RIGHT(op, state, list)
# endif
#
# define BOOST_PP_LIST_FOLD_RIGHT BOOST_PP_CAT(BOOST_PP_LIST_FOLD_RIGHT_, BOOST_PP_AUTO_REC(BOOST_PP_WHILE_P, 256))
#
# define BOOST_PP_LIST_FOLD_RIGHT_257(o, s, l) BOOST_PP_ERROR(0x0004)
#
# define BOOST_PP_LIST_FOLD_RIGHT_D(d, o, s, l) BOOST_PP_LIST_FOLD_RIGHT_ ## d(o, s, l)
# define BOOST_PP_LIST_FOLD_RIGHT_2ND BOOST_PP_LIST_FOLD_RIGHT
# define BOOST_PP_LIST_FOLD_RIGHT_2ND_D BOOST_PP_LIST_FOLD_RIGHT_D
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    include <boost/preprocessor/list/detail/edg/fold_right.hpp>
# else
#    include <boost/preprocessor/list/detail/fold_right.hpp>
# endif
#
# endif

/* fold_right.hpp
IQqGQSS7YZsQ5dzPmPSSymRwtUoTIuFKfVToKIJUvwBY7yrcizVBVC809XzR9PTe2eJrOsxKqo0MMyQDqSEM6117exB9p59cyyoCZFM2nT0ERlS82Z9dBqB9/gFyfJbxtlmMqk4fhLf4gF9g0xoh10e5EQoP8NwnO7krCh04APHmizH17qfk8n6iRpRG/EbMxrxSzAuEH8ieSJ6I5CiLCLZRG7xz5Mmv44alrwgewb7iyIWfdtG4ER+RsxHRENAQIxAiEGURZBFZg82CNffhDpFKlS4bSagIEuJ/DEwnCtWlILBFK4ln2OZga905943JnrQKRNz5DKAMpAQrVMM455URUH+sifvif0T+fVJ0DyDrjjNpAXZmf+m58GYyCWehNsF+jIvLlBBKIlYKV+Q71qbOt6DfMHsjak1xibHyJfX77d7bdE84o+PixGCqGypl2HMisLyUatUdcIzZMMTdm2qGleuyX25Gi4asOe88AomTfl+CnbAqx3WK2SoUWmViLl1C2s2VPxnOMhrr087Fe9MpsGzmLZX582QVXWAJUYMYhDoYmfVZ9WhTuOWBCdNoNHGf8lX251j02sOJa0B6xpcWqCDL6ENzWKLP9Dda1+HCpNgs9LapzT9vBS64SLy0JpEqEoUe20w+ID1iju9maTZvEqmdGs973tF+akNNMd00pHZcC0k9WRtPPIqnieWg5GLhO4ujncKitnSV
*/