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
#ifndef BOOST_PREPROCESSOR_DETAIL_IS_BEGIN_PARENS_HPP
#define BOOST_PREPROCESSOR_DETAIL_IS_BEGIN_PARENS_HPP

#if BOOST_PP_VARIADICS_MSVC

#include <boost/preprocessor/facilities/empty.hpp>

#define BOOST_PP_DETAIL_VD_IBP_CAT(a, b) BOOST_PP_DETAIL_VD_IBP_CAT_I(a, b)
#define BOOST_PP_DETAIL_VD_IBP_CAT_I(a, b) BOOST_PP_DETAIL_VD_IBP_CAT_II(a ## b)
#define BOOST_PP_DETAIL_VD_IBP_CAT_II(res) res

#define BOOST_PP_DETAIL_IBP_SPLIT(i, ...) \
    BOOST_PP_DETAIL_VD_IBP_CAT(BOOST_PP_DETAIL_IBP_PRIMITIVE_CAT(BOOST_PP_DETAIL_IBP_SPLIT_,i)(__VA_ARGS__),BOOST_PP_EMPTY()) \
/**/

#define BOOST_PP_DETAIL_IBP_IS_VARIADIC_C(...) 1 1

#else

#define BOOST_PP_DETAIL_IBP_SPLIT(i, ...) \
    BOOST_PP_DETAIL_IBP_PRIMITIVE_CAT(BOOST_PP_DETAIL_IBP_SPLIT_,i)(__VA_ARGS__) \
/**/

#define BOOST_PP_DETAIL_IBP_IS_VARIADIC_C(...) 1

#endif /* BOOST_PP_VARIADICS_MSVC */

#define BOOST_PP_DETAIL_IBP_SPLIT_0(a, ...) a
#define BOOST_PP_DETAIL_IBP_SPLIT_1(a, ...) __VA_ARGS__

#define BOOST_PP_DETAIL_IBP_CAT(a, ...) BOOST_PP_DETAIL_IBP_PRIMITIVE_CAT(a,__VA_ARGS__)
#define BOOST_PP_DETAIL_IBP_PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__

#define BOOST_PP_DETAIL_IBP_IS_VARIADIC_R_1 1,
#define BOOST_PP_DETAIL_IBP_IS_VARIADIC_R_BOOST_PP_DETAIL_IBP_IS_VARIADIC_C 0,

#endif /* BOOST_PREPROCESSOR_DETAIL_IS_BEGIN_PARENS_HPP */

/* is_begin_parens.hpp
5f8XbvqOvwFhZsRzw5dN5816ufkFOV1a8Si/SHK9IeIVHn3h59Htz4Mvg76JaxKinK6Cje++wZJ+/3q/d41XlNiHdMkbaZAQ1ch4nGkLOjyyLKgM+c6D1dQAs//UlbcR2K1wai5Q+d1+iIXfWJlzFEkLCsZ+KejKn06kqD20w0sac6BlPCLEHwlh+S3ISRuFW8tVZmlpuZ7CsqK8TCfGaQ/z7nvfp9Cq67w/SXF6UEUzX5ftM9CfGCCB+2Odsa6MCWQwPPCHhM4PtTp3C5cMoKvF9FyTpJKiYlSK7Bae1/fJUFW10JEfGJZXWCZTEd6rMBWZfjAL5fumwrk1/irkEQ4QdH8NNpQak7WVNb/kLn/FvOxLO3hFfbTrpPbXxo1Oq7Qn5A491LhRzhF99ka5vV1OIj/Siy5NeqV6wL1x8CHKgUe9krl7zoKn7cpf3l627/veAH1y/SWcpsGz4IISfKYJyxkAyablXLZUa9thhKCTlFuSvxJcUrzg7wx/BOYuTPLEr+OlNc2M6xUImXpJfMTPEflzcU/85ZuKUbH48Cu/+2jqXwyxarsuu5fmSsIm0QyItaF8VJJDH2zxzP6h5RyfiDJXCvYIXrp8CC7kNh2N9N5pifxiK8P5+B46ylzDBQiW4zukFAD4RwNYCrdd4j+xmP6wsqRSi/p4VP79MIW90/Vn8kgiSGNeTYuXTMBFOYFhd0swK7aMtr44
*/