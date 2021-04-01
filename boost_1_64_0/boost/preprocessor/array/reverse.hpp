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
# ifndef BOOST_PREPROCESSOR_ARRAY_REVERSE_HPP
# define BOOST_PREPROCESSOR_ARRAY_REVERSE_HPP
#
# include <boost/preprocessor/array/data.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/reverse.hpp>
#
# /* BOOST_PP_ARRAY_REVERSE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_REVERSE(array) (BOOST_PP_ARRAY_SIZE(array), BOOST_PP_TUPLE_REVERSE(BOOST_PP_ARRAY_SIZE(array), BOOST_PP_ARRAY_DATA(array)))
# else
#    define BOOST_PP_ARRAY_REVERSE(array) BOOST_PP_ARRAY_REVERSE_I(array)
#    define BOOST_PP_ARRAY_REVERSE_I(array) (BOOST_PP_ARRAY_SIZE(array), BOOST_PP_TUPLE_REVERSE(BOOST_PP_ARRAY_SIZE(array), BOOST_PP_ARRAY_DATA(array)))
# endif
#
# endif

/* reverse.hpp
HsGjessQEnwEY6yma1hMhsXVb/NmfiOBtYqDMbAd6c4SqJe18Tc3z4SZYp8nP412we7Z2WODO3xhVN+qg4NsRrJMV5RIL62j/VoIkeScDbKq2b6uTq9hdQkCr1nvyHmTmLnUzu9KJ4tc1JBe9fnko5HeDaJ1ZVB3kshWXkTJPrSqwlIMPxAST1F/x/lsMSD4eGAzbuZyR/69GO3oxPW16owts9u2Ky7S6GthEZ2xVwk+6KPJ0YFwsCc6gNCV+xQPS6NqyAn/TwclWxFcBhI2Sc8W5cREhEzDEX2PK3AotHYHJd+Rjapo4W37iZgfx+GRzpBtJP0BBg4CQbYjHg5Mucvse+PRFFGBx/DN8K5j0X5CJnHRLabfO6SfPGcARlCofxlKmbaK73GlHoIYwx6VlZRTxKkz6r0lh/ihperXiETgqK9tJQE1XJ+7e3YtkeIN64zfASO9bMpyhd8U8qrFQhu0m722X10Y+AMjwAikVpVxpdJbjVSdAUC1EKzY6kbCzCr8jXDQ6SNIyapHstuf1sRltf05d/BF23YcNxo9jT3ylj6i825G4JtYyw==
*/