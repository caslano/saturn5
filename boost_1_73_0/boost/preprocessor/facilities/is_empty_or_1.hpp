# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2003.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_FACILITIES_IS_EMPTY_OR_1_HPP
# define BOOST_PREPROCESSOR_FACILITIES_IS_EMPTY_OR_1_HPP
#
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/facilities/empty.hpp>
# include <boost/preprocessor/facilities/identity.hpp>
# include <boost/preprocessor/facilities/is_1.hpp>
# include <boost/preprocessor/facilities/is_empty.hpp>
#
# /* BOOST_PP_IS_EMPTY_OR_1 */
#
# define BOOST_PP_IS_EMPTY_OR_1(x) \
    BOOST_PP_IIF( \
        BOOST_PP_IS_EMPTY(x BOOST_PP_EMPTY()), \
        BOOST_PP_IDENTITY(1), \
        BOOST_PP_IS_1 \
    )(x) \
    /**/
#
# endif

/* is_empty_or_1.hpp
v/jKVnMffM88RLIBkM7d11ghW9XL8HvimZINhHRW4SbYxbjf+xvYi7i9YEgPuudEtVL2gQbmhTYI0tl7boVTCJYh2MB+ZZINhrmj/Ha4BMD6CQ+/R2I8IUussHJevGwJMCicFdcZAuldf30fPsY6Dw//leA6h8K89JPp02UrutLAUnG5YZD+rdewFmW/w8D/Y7EOhkJ6heM5qPMYFxh/dzvmZYRz+x3vwLxAWwDj7+4bKlkY
*/