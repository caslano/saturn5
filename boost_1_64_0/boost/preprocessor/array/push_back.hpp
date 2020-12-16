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
# ifndef BOOST_PREPROCESSOR_ARRAY_PUSH_BACK_HPP
# define BOOST_PREPROCESSOR_ARRAY_PUSH_BACK_HPP
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/array/data.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/punctuation/comma_if.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
# include <boost/preprocessor/array/detail/get_data.hpp>
#
# /* BOOST_PP_ARRAY_PUSH_BACK */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_PUSH_BACK(array, elem) BOOST_PP_ARRAY_PUSH_BACK_I(BOOST_PP_ARRAY_SIZE(array), BOOST_PP_ARRAY_DATA(array), elem)
# else
#    define BOOST_PP_ARRAY_PUSH_BACK(array, elem) BOOST_PP_ARRAY_PUSH_BACK_D(array, elem)
#    define BOOST_PP_ARRAY_PUSH_BACK_D(array, elem) BOOST_PP_ARRAY_PUSH_BACK_I(BOOST_PP_ARRAY_SIZE(array), BOOST_PP_ARRAY_DATA(array), elem)
# endif
#
# define BOOST_PP_ARRAY_PUSH_BACK_I(size, data, elem) (BOOST_PP_INC(size), (BOOST_PP_ARRAY_DETAIL_GET_DATA(size,data) BOOST_PP_COMMA_IF(size) elem))
#
# endif

/* push_back.hpp
RR6YfTxXy3g5heXjNob82nOMe8Mu3T8FXXuh+bscU7W+iRdj1IkI3ZeE7VlZuO3dQLZ34Dw690Zw1ab/nf76bW6G84+JPsp5Hvk8xyPW8BcIHiL4ztEY1pBKnBc1LNqmBFV2+XyRduksDrbLtWjLSwhv7bLIPuoU7XksSWLpuDbkt+UZi2G/+M393UwKm3JXuBB9yvZmQU6ioziezZfRb27zBxaIfxDiCxyza4kL7pceQHD1d7aWgXSmwvR3TkC60l4Jbm0+vJjTmfwF4SA784kVkKHSpBli9MwuLwrobx5MNLZY4A8PIdg5Fuj6wrkEE76Q6IqzuXmT2NxBZHNV3OaKtJuuKWwuk4ntio7Hd+L+b8tGIvh4aQGzwwXCDhey8lS4athKDbNDgnv3tAs7XFwg/qGIL3CB7e4ilPNhsLE6yTPAxghubezwxZzOyB6MO1TY2DKkfYS1MdALG/sEbIzsz7a7S+h3YKE87drbUmNvkgBjmOUBtre0SNt7WQHb60I7vILb3r9pP99B+2N+c/t5OSsrhVuJ8j+K2Q/Brf2sEvbzigLx6xFf4mzbLXEF/NjRKN/V8GMNsLFjkK6KSx8bJwXzlvZHcGt/r1zM6Uzeg3H1wv7WQL7jrP0Z+qnH1I1EwwaWegxy7OKpxyDKNptgmyaysse1AfbYVKQ9vmqK9ncdt8cix8SB77BMY452/WLsdQ/m07MF20Tph+77FNhflY3S9V39HfqKlE0JUg+dWNglBJiKyN5/28J86QbIdw7m716jdZQW+eN70Gj9RW03jdH9JkMbYlm88ddM8cqoF0XrI2wvuz3RZ/e8tCq/5qS1jCyBfdvwnmUb4e0cqs23SkdEwa6XSQh0frcF6fMl4Kv02M70uHGxNxe/abFdG7D7Gjt0vrSH6x4O4JolPmYtfTPTQclEWVsUEyalRGn5Gnx3VI8N0Q4n9k5DmoX1uVYdXo557E6WfnmAjdIcFcnVo/PdhXyvCuwz2EUoXbtsCHWjZ7E3tuphuuwV/rmP+WdFdwL8cz/kBC/rC7ctZnQOowNvM47Jg9924VsVrp7hGA+MfwrF4zIWPzayepFjI4uQYyOkIfzz7zE26ia4Ggdtpb+WBcZGJ070r85JBNMvVKtDWoCdzOle7UyALWGwgThtjo+74ddSGG/W2nAmtjPqweY6p0CX53jC6XHX6whux13kz08t4M+VrZWTP48Cr2ywfBJb21ycDyiqXilbjTFbHYD9D/v2T2dp+YNOCDFfGJK+EPAy5U9tOh5uUOcpLYR7yu7vHWJ1NPwStg//Yu88wKMqtjh+7t0AAQKE3qUjooQQQoAISMqGBNLMJgE0uqaShTR2E4qigj47Ag9FmmJBfVbUJ6IPGyqIBQWxd6SogKJYsMP73buzm5vNgsTX3wef627OnTt35swp/3Nm7oxhvx5RZ32he/53O9eFmzzLqfBt11eU7n83vkSNm/+KGusktRZ9iqWtoX9A5mf8Lm/V+cl1+FpYpJZJH/T5tbBgfk35pPBj+CSXpf3tanldyRZbvDGSYWYqjc27AhgdvIRaN2Lh6UQj9aDexzf5WGmsBJZa/k2z8u8P5FN8dvSWbnXXxJd39/qrW9vW+ivj73stfwffxz45JZ2319PZOt1pPtryt7Lt07vXPVvBrXyi/9xvtebU012tLVV2eYx/TWZNhbHe2GW8o+3f89NPAUr69me0liL2sKwNndHdsnrM2NwUBuWzGLrK+K5WC0WPUcAXe1SrvnSw+lTaV+Px7pkQpfz2bMs4hfwOj/x7mlr2I9HUfiRjjD1NVR8uqO2Dd88EQ0H8TQ+k1+Z9plt8q1eXVT5I6p5Pe6GBwflczMc=
*/