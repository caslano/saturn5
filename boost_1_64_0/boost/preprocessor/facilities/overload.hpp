# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_FACILITIES_OVERLOAD_HPP
# define BOOST_PREPROCESSOR_FACILITIES_OVERLOAD_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/variadic/size.hpp>
#
# /* BOOST_PP_OVERLOAD */
#
# if BOOST_PP_VARIADICS
#    define BOOST_PP_OVERLOAD(prefix, ...) BOOST_PP_CAT(prefix, BOOST_PP_VARIADIC_SIZE(__VA_ARGS__))
# endif
#
# endif

/* overload.hpp
MDgtho+ONw4eyvUAbF2IkFHgEmoUjLIhLfX6kQGd19p1Pg2g0QQaU4AMRGBWdnd9LT+XsRdTzIgKO9Vi8vuIw7S9RvQrU/ReBC2/hcdobE27IxyyaN7cspBtfQ/PH+xD3Xh4/0nK/ePc1Y0lLK7xiLxGayT2KkKsGsMA2cmuHjNE8zycg2AIDZyDi11jdxNbihe0X4gcIt0zWZpEH/5HI/dFKUpTnvply7hEdf/LVs4jY+dKfbO4cc/5dSLzIOuZfAPm9/B6AlY8a6jv21ad/Qod6HAUDdfKGFbsE3KHPuNEWHqn7BrenclSgEhvqDvQpNQnvlT/7UwXsokuzVoXqwvlAO+Bc9tFZPVG+O+mR23beYwB0FJGJCM6jxtqeYthZmu57tpeAAylUvENm3yiUeihWYQ/xDhov1nnzD12/12NQyZDkeDJIzeDfpqiEwvLtwfdA9s7mIKj1zoy3oGSKTGhN3i0rehAScYg9u+a2irJtLGzjb+YbF9scQ/qXDX6Qk+nZb3P9rfBmWJ+WC9ASNIV9uPgW4VQg63MFhJsmLDrbQ3lMUEqIqvMDQ==
*/