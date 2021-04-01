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
# ifndef BOOST_PREPROCESSOR_SEQ_POP_FRONT_HPP
# define BOOST_PREPROCESSOR_SEQ_POP_FRONT_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/seq.hpp>
#
# /* BOOST_PP_SEQ_POP_FRONT */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_POP_FRONT(seq) BOOST_PP_SEQ_TAIL(seq)
# else
#    define BOOST_PP_SEQ_POP_FRONT(seq) BOOST_PP_SEQ_POP_FRONT_I(seq)
#    define BOOST_PP_SEQ_POP_FRONT_I(seq) BOOST_PP_SEQ_TAIL(seq)
# endif
#
# endif

/* pop_front.hpp
6ZCxDLfL2GTv5jpvhTFU6+X3QgCDVFEzCGTGyT+9zKHuhUdaGsZJwl6wZesRgWK0lZaus3yd2ZkUSCh1ipnftLuJ+50Qlseg/I78UhRTj+r+lQA7mv9ekEptNe/dWwp1sHL/8DJakkuBK8cZ3Ky0a0QnK3+DmsB7iNS4YE2QapKS3wAwmdy0HeDxqLYadxOqekqf/bY0caTOV/eXf286C/f274pbjEyS+K8ytFgRbuVVsSFc3gDHYoFXxwaSz6gDb+Uy+17BIloLLWqy01ofFw608l83C58DiRVpeEUAze/zw6jjij77QmcFbex79HS5/n72/i9+r3qzAzIOOYXTYh9mPz/IIx2/EkeOf1M0C8wmYlbzNxJKZAGrKs5pm+liGqwNWJQ9ZsUKFAMdQ8ozdkST22Gzt9w+MuAp46USPvvVeNm3eI1fHBb0UJLt8KcH/TG7KaIuB8c+cyaoQU1Mj063gMYipQ9apruDHIC7jG9hgEAyYUScFU5obXPPQcmmfDWtN0oD3Vm57v42fjs9LibTz7S2gTcanvxOXnz7dw648YaMK+dBFQimqw==
*/