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
# ifndef BOOST_PREPROCESSOR_COMPARISON_EQUAL_HPP
# define BOOST_PREPROCESSOR_COMPARISON_EQUAL_HPP
#
# include <boost/preprocessor/comparison/not_equal.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/logical/compl.hpp>
#
# /* BOOST_PP_EQUAL */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EQUAL(x, y) BOOST_PP_COMPL(BOOST_PP_NOT_EQUAL(x, y))
# else
#    define BOOST_PP_EQUAL(x, y) BOOST_PP_EQUAL_I(x, y)
#    define BOOST_PP_EQUAL_I(x, y) BOOST_PP_COMPL(BOOST_PP_NOT_EQUAL(x, y))
# endif
#
# /* BOOST_PP_EQUAL_D */
#
# define BOOST_PP_EQUAL_D(d, x, y) BOOST_PP_EQUAL(x, y)
#
# endif

/* equal.hpp
gJR9unk+hNt0rIr3qkS+qlu5MO8k/QRSP3Trci8m9aOrtsjxdpnSXdIX78kAm4uv25Yct0xbbtss11P8GPoIbIsOJRtlIkzKi0hF9UwIXf1whXEnKjIteYJ87ReLkUFMdOjwFkiJIr3Ccsf7wFol5BEFG581feWMHZe3X0noqtrAM0G4cx1I9f3IdhqNYGq7AW5XEypTg9shCs2FJ+UNSCMCOvrv0IeOAt6Or/r0iEWdG1xBWrxWeqJbHMy1qTtVceDyC7+ENXmLZyIeybwaXIJzLPsv2ETCmCG207Woemzgw6Vvtb4S5wEoBgORp0YCdH5Oks0Ovf6rYW1NUpVdHfFQxeX1gJFxrJmftjdSCyomg8sym3r6ft5D1jTmyjVUJcR6oYStDmCCyt2mnb/EXPlqiDKg7xKIw2WWktouqROmtwpofbv3xsQlaYrUT+B5ahvINLLLSsjG2GbQ/YXWPLmJUx66X+BTDXx4jkw51w963yN9Y/RMmmi7X5MkiotUTrQ9g8SL6iIJE23PDdNFTSWGDuC+fxvluaNlnF4oSRfVBZnfiCKEk44h/m/hGc9p6aJBwLnCZ7+mG7yOU56KrJcrmi2LolunsVTc2QdpC/4iUGTJVS81T9LH6W04/NGFN4Xf4jEvZQir9D2vrUWEUCBJxThEI8DFfyyb/6OERIuuVaC0oE3hV+NsnXajxDgQglB6OClCa6+8COvN
*/