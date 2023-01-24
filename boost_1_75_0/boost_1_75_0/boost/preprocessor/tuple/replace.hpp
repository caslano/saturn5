# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2013.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_TUPLE_REPLACE_HPP
# define BOOST_PREPROCESSOR_TUPLE_REPLACE_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_VARIADICS
#
# include <boost/preprocessor/array/replace.hpp>
# include <boost/preprocessor/array/to_tuple.hpp>
# include <boost/preprocessor/tuple/to_array.hpp>
#
# /* BOOST_PP_TUPLE_REPLACE */
#
# define BOOST_PP_TUPLE_REPLACE(tuple, i, elem) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_REPLACE(BOOST_PP_TUPLE_TO_ARRAY(tuple), i, elem)) \
/**/
#
# /* BOOST_PP_TUPLE_REPLACE_D */
#
# define BOOST_PP_TUPLE_REPLACE_D(d, tuple, i, elem) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_REPLACE_D(d, BOOST_PP_TUPLE_TO_ARRAY(tuple), i, elem)) \
/**/
#
# endif // BOOST_PP_VARIADICS
#
# endif // BOOST_PREPROCESSOR_TUPLE_REPLACE_HPP

/* replace.hpp
z37tDiqS8PlsbSVBszucLqsZhYFGl4isqjyX1SoL0WZjrbmD+5heF91mbR22woB1s1PpilhSy7o/jKTzPCBNEaa2oNj6JX3Sy7AXjhzdVsRWFKe79IsFDNdVQpmw2uJCnw4QdSle6uGHZW/1lMYTwTuKuDoHMdHN7auw4JEMLLoL7XkPYIP5fqhTtVTDD/D6wuHGsSoqYq/+6UaRL+cHMLSrk0CvpjbPxPX+D8vpXdafqLM7BTw8rcd2Tj6gHylr/+hI/EqJKeSSH6i/7MO5X/vZRMNeGebpHLJ2XDsppYrkp5XQgdHhas7jyRosWOFUTPhin7Wk2VF+KRvYx95ZOd7Dja/tqj09arN/ELfPfjEd4Mu1lYnwiy4iUIWOVFu1VDmHVZNZWc3B+re4jpiMKCT+fg8MFTKq+r6kZjaEMky1rEGhvPaDkfCbx29lTaPoFrclrUjzVcr88r+lq/4Gxg1yvpSgVQx0d17Rc68WF3+fc/I9QLh8f0l92cf0eOcScVjk9bMxidPPkBroXqqvKSuhFu+amaBC2J4SRZqEvixDePMISpGlWYG73qW0waVk+9OznDne1ORjcDEtgvx+QjWN9VT3IlVOw0yzTL1rsHZ3p20/uhRe+2bvuv+Z6x5Ts6g3zeLce1Zz9x7IYObORjX7bRs/bwYnudEcJZM9IltSCbo2cUJfWvNkVJ5gr12a6j0vBt/rJNsOaW5n
*/