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
# ifndef BOOST_PREPROCESSOR_LIST_AT_HPP
# define BOOST_PREPROCESSOR_LIST_AT_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/list/adt.hpp>
# include <boost/preprocessor/list/rest_n.hpp>
#
# /* BOOST_PP_LIST_AT */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_AT(list, index) BOOST_PP_LIST_FIRST(BOOST_PP_LIST_REST_N(index, list))
# else
#    define BOOST_PP_LIST_AT(list, index) BOOST_PP_LIST_AT_I(list, index)
#    define BOOST_PP_LIST_AT_I(list, index) BOOST_PP_LIST_FIRST(BOOST_PP_LIST_REST_N(index, list))
# endif
#
# /* BOOST_PP_LIST_AT_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_AT_D(d, list, index) BOOST_PP_LIST_FIRST(BOOST_PP_LIST_REST_N_D(d, index, list))
# else
#    define BOOST_PP_LIST_AT_D(d, list, index) BOOST_PP_LIST_AT_D_I(d, list, index)
#    define BOOST_PP_LIST_AT_D_I(d, list, index) BOOST_PP_LIST_FIRST(BOOST_PP_LIST_REST_N_D(d, index, list))
# endif
#
# endif

/* at.hpp
SkryXyP5A/UH1pqzLzh/8Hs+KUknSu+Icd8T4X5UwzF0MrT+XyH775yWkpmVE22HsFm6VxtUooegoFbvJtRLr+wop3bpA0fcBpPm/XUD440vKCKXf/turX3S01Nh6K0CcOVZAFyvATC5nRv59Z5t1CCI2q1D8Np6HYJ/+UPg1/7MWBqiX4+i/x/F4L8PIIPkeYkKTh8GJ7Nu0TSSzfhhg4gP7ZE6ENhNzYEXYGEX0ICsWoXM2N07f/yna9237jk3/uON3pev03v/4PrzxH+SCkCPswCYtZsBIB1pfwJ8o4GQYoDQ2QDhALwGCGfpx0QTIh34vDTNgvR4ntMGMn2aHz16A6BvdvFFSN6j9/tcxSSkSFx11qFcRVAC7iicnWzhjyO6GsEYhgtxy2Vc/fAt2dcE+JKCwrd757nhu6Ye+DoHgS+G93/94IumjYCG4Xt5ZzD4BpwDvmjA8qz8FAm+WA2+STLuLPjSWf8JiQZ8abQmbxC+uj41iAd0eK0lAL5XfwwOXxpgOcrfSjrBl6HBt1vGGfDVPx7E8XhwiCBKUSHLUWG6zwcIxlq2DSPDFQyL8TVs9fbTRJnPeNK93rI7fwgoWziAWuZOI93ZWmxBDvkWMUYb8bFvyJc/2+85iz+1Tg2PcFfEG4PcIBWg/rTMk8d2pegBg2cMoQWIYs7oRe8ycQ8TdSiXE9kZBqD1qd3+bMnnOinR40LxBg8dVqw2EYDkIyfcsgfVgd//7ga/ryQ//ujmbkUQy9dUkkslW3wiK9cB/Zb3CVcx+ffsknDWN55erRFJVpqdrdaoCITEc1xrlEEkHkmbKs9jIU7j7TmPibt3nFuebzPG081fmXT7X1+fpzw3xtNAAH7a3sB4KgwIbjcgaOcPgZQ/L+5sUP40gn6PbD+bfrEq/bpIkVQtz4e7+7UXR8dvTWjPUk97CWp7HzLTx1dL+bXkxwblVyPae+X7s9vLUNu7nttLV9sbckHaW3WO9jb+INtTFUmbgQ/7YhEb6d7USA1xp9WNZ5RX0bbnerZi4SbC3w492JII1ouu9nkvezxawz399aQfAOWAMH7OHCtueoVLSUkCW63A5o9qhksZlaS+6viuT+Q+GZkiZiGSyw1FDDaFinxLJiNqhxjLe0upbkEaCyZnhnxS7kay1oG1eF8cVvfJsmdjxxn55PUzWNiQr3fjNyapDvcvkCT3elvgPqX6ADtuNawzSY3pxJXsiRWXwZMtOuO/XXTA/yzRZqW8kVKJglzs7PfjH9hB+MhZVy8+9qET4kPsOKlmx5SIPio+XvaNvFbFRxEiudzxZMaH0zfTdYyPe79tHD72fxsUHxu+rRcfH6xV8RFbpeKjLTzQp8Z/uwjHf9xlqmoQH47thI9/rK0XH8uuoRn9Vu7ljcrma1RkzJAxaUpCbxUTTyCGS0T3ZkzkaDmU3oyGf2xtHBp+3BoUDV9vrRcNb69R0dCuUkVDJDzZohn+24WpktDw15dno8HQryUs2L73/erHkEptRLay7xcSwzEpZDttOLY1W5F3apXJIk9wlFqkZ4rRSKKgeIv2qUjJaoQN/8ZggoddyRgIbVWly5YTR6/YPY1sDvHaWkQIpRpF+oyABucXEagbKCqRm9EJcXcOMX0+DA2QPorUH0sqHFDLVkZCbRXpSLGmr7Rp9j9W6PeiZcSXiIAQXR12CiUqWrL1qiyUNan5yAjMQDYywppYuYDgzV1Z0i7cVn7qi7O7WiH1ezXg/B1G1QElJrBj0GdoN4QdV405A6m7d0jxaC3aggh9/MWpPYLui4ER6lsva3YlvIkPWL9HhC0nCi/u0WF3h9AQ0ypSktU0JuhoCf4MZtLszdqdkQSSdXQ=
*/