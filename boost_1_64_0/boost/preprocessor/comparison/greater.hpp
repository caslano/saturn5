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
# ifndef BOOST_PREPROCESSOR_COMPARISON_GREATER_HPP
# define BOOST_PREPROCESSOR_COMPARISON_GREATER_HPP
#
# include <boost/preprocessor/comparison/less.hpp>
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_GREATER */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_GREATER(x, y) BOOST_PP_LESS(y, x)
# else
#    define BOOST_PP_GREATER(x, y) BOOST_PP_GREATER_I(x, y)
#    define BOOST_PP_GREATER_I(x, y) BOOST_PP_LESS(y, x)
# endif
#
# /* BOOST_PP_GREATER_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_GREATER_D(d, x, y) BOOST_PP_LESS_D(d, y, x)
# else
#    define BOOST_PP_GREATER_D(d, x, y) BOOST_PP_GREATER_D_I(d, x, y)
#    define BOOST_PP_GREATER_D_I(d, x, y) BOOST_PP_LESS_D(d, y, x)
# endif
#
# endif

/* greater.hpp
8AMLpw0dhUyxYms1k7rKIhsdcbQAwMQ/VmBl6yzcxe+oF1VVp0K9Y05Z5WVJ6idZiDqwKg+L+Mb/q71vYM0vafSO0uVdYdeYPF/paaImtxYu3YlYdJkLrKpzH7JBasIQZ1/z2BvQOT272yIKJ1QKIagqRrfJCM/L5ZtuiTilYXxIfS10PEdSlapALX1dnWp8bfumskiSuRRLL4lYEs0GFPZkFL++sH/vfpzAaTk1G9aWVhcB7QwcMk7Ck9MtVJ6SYVzJU+Ol+4hUy/3aycQlcWwAcBCvwKE95om7coBChgGPmHq9A+RmAPagDCzQP38AnJTJ7U7qJzyqsNV1UtTxy1OolW5ZVxJ5faRfWXDS2wUXd1kTg6zNUhfgtnUOKJ9uACgO04CCwCebc59lPaHEKvt9jm/rdyJQaEw5QS25FTknW2FclFaY85cHykY9DMDptEPC4ew6i8Wo1mYs6osGClz6xw99mBzTVPlH4oa2BsuwvHs6aA6S27/VH1xHO3cgVORVdI8DJbagKkYXJCCakS8E6P+UzawmNda8V5PLGQsL3ryjBM3Tar52ig==
*/