# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     (C) Copyright Edward Diener 2014.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_ARRAY_PUSH_FRONT_HPP
# define BOOST_PREPROCESSOR_ARRAY_PUSH_FRONT_HPP
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/array/data.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/punctuation/comma_if.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
# include <boost/preprocessor/array/detail/get_data.hpp>
#
# /* BOOST_PP_ARRAY_PUSH_FRONT */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_PUSH_FRONT(array, elem) BOOST_PP_ARRAY_PUSH_FRONT_I(BOOST_PP_ARRAY_SIZE(array), BOOST_PP_ARRAY_DATA(array), elem)
# else
#    define BOOST_PP_ARRAY_PUSH_FRONT(array, elem) BOOST_PP_ARRAY_PUSH_FRONT_D(array, elem)
#    define BOOST_PP_ARRAY_PUSH_FRONT_D(array, elem) BOOST_PP_ARRAY_PUSH_FRONT_I(BOOST_PP_ARRAY_SIZE(array), BOOST_PP_ARRAY_DATA(array), elem)
# endif
#
# define BOOST_PP_ARRAY_PUSH_FRONT_I(size, data, elem) (BOOST_PP_INC(size), (elem BOOST_PP_COMMA_IF(size) BOOST_PP_ARRAY_DETAIL_GET_DATA(size,data)))
#
# endif

/* push_front.hpp
ocAJM8ZUKH5LVQh+6+A5PXq5X4pxGlM2owp68mBnnuuQF1yXdXpUZr+UOqgdRhK9ci1zZFdAL2iP/ma3E2tg5mTl7FehyDo0nAmAZPobIvu/oGzCR8Ox9X6cv/LCucZIhFl4t0EFoQAVoPY7vbQmStvjOI4+oIRIouLecuS/LPP7HUGW/eLS5ZOD+8ofHNUlH/iBW8S3u6PPsTxX2h2jSgCRhksXtypEEfA2N/kmBo9IR15wODetnWn7/w9w6J/ceEKyRdzjnusrsypqeGb5pGwJ3ZjY/66MTzxJjMWFSXT4El+ifXz823ZKZRe7Llty355GSDPRFNXsLTWGYSphLPSlz7H20wt2x/FDtQJUOZ9yAOWiQCj+98e7nPXkLCOTQkTNlc5h5ewZH6LUInleoLSmCccYdJjmQAqPy7/XsIeNhmlX+qQmYKX881+EcWPRZjJquAjnPS+3nVJV1l9QLsodjcb+WlUgMZVa9a930YtF0zOIrML6F6yQS6aB5XZTP7e7Y0jTPnFhL6OwHGU4Cb+BeMV7KBUY9W/xMertS0SZsVr6SKbnFtggKQ==
*/