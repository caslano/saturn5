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
# ifndef BOOST_PREPROCESSOR_LIST_FOR_EACH_HPP
# define BOOST_PREPROCESSOR_LIST_FOR_EACH_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/list/for_each_i.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_LIST_FOR_EACH */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_FOR_EACH(macro, data, list) BOOST_PP_LIST_FOR_EACH_I(BOOST_PP_LIST_FOR_EACH_O, (macro, data), list)
# else
#    define BOOST_PP_LIST_FOR_EACH(macro, data, list) BOOST_PP_LIST_FOR_EACH_X(macro, data, list)
#    define BOOST_PP_LIST_FOR_EACH_X(macro, data, list) BOOST_PP_LIST_FOR_EACH_I(BOOST_PP_LIST_FOR_EACH_O, (macro, data), list)
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_FOR_EACH_O(r, md, i, elem) BOOST_PP_LIST_FOR_EACH_O_D(r, BOOST_PP_TUPLE_ELEM(2, 0, md), BOOST_PP_TUPLE_ELEM(2, 1, md), elem)
# else
#    define BOOST_PP_LIST_FOR_EACH_O(r, md, i, elem) BOOST_PP_LIST_FOR_EACH_O_I(r, BOOST_PP_TUPLE_REM_2 md, elem)
#    define BOOST_PP_LIST_FOR_EACH_O_I(r, im, elem) BOOST_PP_LIST_FOR_EACH_O_D(r, im, elem)
# endif
#
# define BOOST_PP_LIST_FOR_EACH_O_D(r, m, d, elem) m(r, d, elem)
#
# /* BOOST_PP_LIST_FOR_EACH_R */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_FOR_EACH_R(r, macro, data, list) BOOST_PP_LIST_FOR_EACH_I_R(r, BOOST_PP_LIST_FOR_EACH_O, (macro, data), list)
# else
#    define BOOST_PP_LIST_FOR_EACH_R(r, macro, data, list) BOOST_PP_LIST_FOR_EACH_R_X(r, macro, data, list)
#    define BOOST_PP_LIST_FOR_EACH_R_X(r, macro, data, list) BOOST_PP_LIST_FOR_EACH_I_R(r, BOOST_PP_LIST_FOR_EACH_O, (macro, data), list)
# endif
#
# endif

/* for_each.hpp
XvQNn5zyfMdr7OOYsOcbTs73MEPDiX5w6bSxJkDToBPKOLr7prqopmUAvFMjXbBL8FydaaRMR+ekHOJa/BV2AdnqPMzTowC/PqH9fMXG4iZb3eGeJbUV/eLceTuWFHI8BBtCXLzE5vZ4PifxSe1NPt9tTu6KUSnxZjq+xde/asSdRVR6rXAyPEvwxHL/ilYsM08WKcmy8vZ6ToL20cmjS5NcWUnQ09bcsUskif9c8j0S+xd5uq2AUb0cEpKHx6vE7QPtlbo/C1iP6EGROKSC/iQkDjjS/ShXIyZonuBZcLrgFbQY8ihd2ymgHCrJHL/OsymtuKXYViBqUGnxfZWMY7v9wZHLsvtKL97i/LgRqy9q7eHhwWAvLzCoJKgC0DSHHYUaaz7vXsg0NBLpe2zC1n6ccffnheKbIWrsRLXfnrVWhVIy+61p3C277PxBRa2yfmpXKkpHQUzWPfIGbwGXffRDAUUz25WnD0QzhacuCYkOeGQcMilqfEfuQzeIYWMPi/yeH8J3gwWaR20OqrMYFo8yDRec6IWH0PkfK+2YeOKz0fkZBf7sqqiD5vMC60a7iWOPAgrnuNbzPPAfe0wqdSUbS5C3G/ElO5HEB+qv6VO6kEnTi2lxiMqBeLqnD/juwGlAZNENEc/ebsi+8PPk1rF1/x+WGu2aWlKam+NhKW86zkQBnpuewNJerpVOf8qNz1P0TipXXxcLf51Z
*/