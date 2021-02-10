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
VC4zVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUloLNa0pBQAAVAsAADcACQAAAAAAAQAAAAAA914QAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfSFRUUFBST1hZVFVOTkVMLjNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSNU0ZntgDAACBCAAAPQAJAAAAAAABAAAAAAB+ZBAAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9IVFRQX0NPTlRFTlRfREVDT0RJTkcuM1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJxM/xzxgMAAGkIAAA+AAkAAAAAAAEAAAAAALpoEABjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX0hUVFBfVFJBTlNGRVJfREVDT0RJTkcuM1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlK4qkhybQYAAN8OAAA0AAkAAAAAAAEAAAAAAOVsEABjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX0hUVFBfVkVSU0lPTi4zVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUmw5/W2+BAAAJwoAAD0A
*/