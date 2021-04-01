# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2003.
#  *     (C) Copyright Edward Diener 2014.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_FACILITIES_IS_EMPTY_HPP
# define BOOST_PREPROCESSOR_FACILITIES_IS_EMPTY_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_VARIADICS
#
# include <boost/preprocessor/facilities/is_empty_variadic.hpp>
#
# else
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC() && ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/facilities/identity.hpp>
# else
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/detail/split.hpp>
# endif
#
# /* BOOST_PP_IS_EMPTY */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC() && ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_IS_EMPTY(x) BOOST_PP_IS_EMPTY_I(x BOOST_PP_IS_EMPTY_HELPER)
#    define BOOST_PP_IS_EMPTY_I(contents) BOOST_PP_TUPLE_ELEM(2, 1, (BOOST_PP_IS_EMPTY_DEF_ ## contents()))
#    define BOOST_PP_IS_EMPTY_DEF_BOOST_PP_IS_EMPTY_HELPER 1, BOOST_PP_IDENTITY(1)
#    define BOOST_PP_IS_EMPTY_HELPER() , 0
# else
#    if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#        define BOOST_PP_IS_EMPTY(x) BOOST_PP_IS_EMPTY_I(BOOST_PP_IS_EMPTY_HELPER x ())
#        define BOOST_PP_IS_EMPTY_I(test) BOOST_PP_IS_EMPTY_II(BOOST_PP_SPLIT(0, BOOST_PP_CAT(BOOST_PP_IS_EMPTY_DEF_, test)))
#        define BOOST_PP_IS_EMPTY_II(id) id
#    else
#        define BOOST_PP_IS_EMPTY(x) BOOST_PP_IS_EMPTY_I((BOOST_PP_IS_EMPTY_HELPER x ()))
#        define BOOST_PP_IS_EMPTY_I(par) BOOST_PP_IS_EMPTY_II ## par
#        define BOOST_PP_IS_EMPTY_II(test) BOOST_PP_SPLIT(0, BOOST_PP_CAT(BOOST_PP_IS_EMPTY_DEF_, test))
#    endif
#    define BOOST_PP_IS_EMPTY_HELPER() 1
#    define BOOST_PP_IS_EMPTY_DEF_1 1, BOOST_PP_NIL
#    define BOOST_PP_IS_EMPTY_DEF_BOOST_PP_IS_EMPTY_HELPER 0, BOOST_PP_NIL
# endif
#
# endif /* BOOST_PP_VARIADICS */
#
# endif /* BOOST_PREPROCESSOR_FACILITIES_IS_EMPTY_HPP */

/* is_empty.hpp
AdeJU6CzQ2Rt1PHQjAOP6JFiNSdat5Hw2rRKYPo5cxb3gUvoCn3Gkzta8eRlolfKs6s3SJQhMqQ7MJQqLA9MLmB+HVPHXOxNHQwIMvFWfztKqqdHfYA2qAi3Zkj05J1TUCfR2qqA8goPlJ/rdj8M1HC1lTIxIgXgDLY9aW/BI0lQJmbUkwP6jFqQuK3IuI7MyUi5fpaLe/YKSHNYH5iyvOZHLXgucVdqc3RWD9bvLhP1YfnbC2VuWjGf/UbpFFg6bqrSj+8G0fKzNsH5vfKW8zlfTHxZQmBjvuhrNRwQ2gmTvYZ0fgvTaIJokU/2nC+KgbJfAKraxfJbi3BveN+BXv9TsQAy2uLoVEm5tKF+/TruW2xqezZFGrevoXsYil5lYjuwof/epdRHz5nhjdBAUMEGY8VqxtEkyrheRy0tq4uGrw460NOb4iQW9x029Jucqi+6jGm5mDIenuuUYXvmcuCWdm5Vq+YqeW0Gn+QVdgqbVNeqXjzLacikMhbeL83cV+nceB4LIrl51kBevUy4ylNqVxe65AjWl4VjmmqeeRNOpOXyUMCw97vvyg==
*/