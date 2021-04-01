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
# ifndef BOOST_PREPROCESSOR_DETAIL_IS_BINARY_HPP
# define BOOST_PREPROCESSOR_DETAIL_IS_BINARY_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/detail/check.hpp>
#
# /* BOOST_PP_IS_BINARY */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_IS_BINARY(x) BOOST_PP_CHECK(x, BOOST_PP_IS_BINARY_CHECK)
# else
#    define BOOST_PP_IS_BINARY(x) BOOST_PP_IS_BINARY_I(x)
#    define BOOST_PP_IS_BINARY_I(x) BOOST_PP_CHECK(x, BOOST_PP_IS_BINARY_CHECK)
# endif
#
# define BOOST_PP_IS_BINARY_CHECK(a, b) 1
# define BOOST_PP_CHECK_RESULT_BOOST_PP_IS_BINARY_CHECK 0, BOOST_PP_NIL
#
# endif

/* is_binary.hpp
YhwVBtP9E3TWXk7ENG3/f/ES9wth7qkAKo7TInIKOkbvrVfw/lSYzWqXKBPozCdQX0gzSPbQH3xt5Y8YsUhiYfnVPSLilqvLnt7XmwEmb+ByUtk6mv1f+QAmi3VbPIA9xqW/HwZt6hluMWm4dEdxSqjPNbqhYUvOq/Gs24n9tYOiF3v/VS2pr/occ9OxERkP9VN2bWCzs4FKnWD4cDtWKmHRf4NGaw4ffyJsErPrkCT7gNFgGyyUs4VxC5HHFbcpud3OVzgCTuUvY0a0mf5X3FzKKNQFcm7lZwEntG66s1eZMfCwzWBkejog55m0rGFVCjvZm+1E7czEIfEzTO9L8422g/ageAn63hjUxVTll972zgVrE3U6dKWOqysSAUf8LO2bYP4EMQPGlAsErJwa6Xqa9zcqqVV1DZ3YqD1ahQ4p5O91QQeY7Ej4PLBloW9EKgxY3Cq2ky6NX1X+PULcu3xkmmB+HRXBxMTDpJi5mDKSRwv0z32mJaSojbYsv9Urjh1hBOqWxI8VpE+YpppJPXDwEEox/oyoiPSC8SfAu5zlZSw2VR9wuZa9uA==
*/