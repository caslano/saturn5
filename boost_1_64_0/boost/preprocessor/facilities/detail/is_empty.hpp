# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2014.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
#ifndef BOOST_PREPROCESSOR_DETAIL_IS_EMPTY_HPP
#define BOOST_PREPROCESSOR_DETAIL_IS_EMPTY_HPP

#include <boost/preprocessor/punctuation/is_begin_parens.hpp>

#if BOOST_PP_VARIADICS_MSVC

# pragma warning(once:4002)

#define BOOST_PP_DETAIL_IS_EMPTY_IIF_0(t, b) b
#define BOOST_PP_DETAIL_IS_EMPTY_IIF_1(t, b) t

#else

#define BOOST_PP_DETAIL_IS_EMPTY_IIF_0(t, ...) __VA_ARGS__
#define BOOST_PP_DETAIL_IS_EMPTY_IIF_1(t, ...) t

#endif

#if BOOST_PP_VARIADICS_MSVC && _MSC_VER <= 1400

#define BOOST_PP_DETAIL_IS_EMPTY_PROCESS(param) \
    BOOST_PP_IS_BEGIN_PARENS \
        ( \
        BOOST_PP_DETAIL_IS_EMPTY_NON_FUNCTION_C param () \
        ) \
/**/

#else

#define BOOST_PP_DETAIL_IS_EMPTY_PROCESS(...) \
    BOOST_PP_IS_BEGIN_PARENS \
        ( \
        BOOST_PP_DETAIL_IS_EMPTY_NON_FUNCTION_C __VA_ARGS__ () \
        ) \
/**/

#endif

#define BOOST_PP_DETAIL_IS_EMPTY_PRIMITIVE_CAT(a, b) a ## b
#define BOOST_PP_DETAIL_IS_EMPTY_IIF(bit) BOOST_PP_DETAIL_IS_EMPTY_PRIMITIVE_CAT(BOOST_PP_DETAIL_IS_EMPTY_IIF_,bit)
#define BOOST_PP_DETAIL_IS_EMPTY_NON_FUNCTION_C(...) ()

#endif /* BOOST_PREPROCESSOR_DETAIL_IS_EMPTY_HPP */

/* is_empty.hpp
GE4/+FtRjNk3XdBSpryuXTHVx3uRkESOsdyWoo67Xw+rxLADc8VGZPoxVhnIjZfsyzsQwSHjjf5C6gH29lQhlgW9s7Bi6PLsDnN3eaknyOkdZ8enEigst/nSo5qsl0AHsPggx0csBKtEVBrH8H9Vuz9PxwQEpKqpGzWnNab3mKz7KsAkOlU97SNYRxcfwhZ955DtUx4BxfFF+9V1kP4Vj0WOjEGXk5QRTJ79/77LtmRmThxxtyifvOsPh5yA7l6FBvHQqPJu2m6GCkTvKn+Cz6Se+/4DhzyKh20JPntFzcE8DOdgTI47zX83H0EavlcmFWRFOEvwPS3DlJRUXdH127XU4iCAPYNwP65/DpHflISwdZ3sOGxe7htvJxxtBgzGTxT9OgxYcmIU68pa2H6VHa2edYm/gXNyF+ti+jXO9Ib/5V4YRzQBE1mwtc+8InRnqAd/BfZDlwKi8gMqQat5qahIR6qJijLR4KtZDBB4boDsaJQBQs40tyOu0A+wRvXzCAHtpFkZkC8euKNO/w76+8o8BcIGPB4F7X6leoYzueNXtnII98BOZdygfA==
*/