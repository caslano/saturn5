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
# ifndef BOOST_PREPROCESSOR_IS_BEGIN_PARENS_HPP
# define BOOST_PREPROCESSOR_IS_BEGIN_PARENS_HPP

# include <boost/preprocessor/config/config.hpp>

#if BOOST_PP_VARIADICS

#include <boost/preprocessor/punctuation/detail/is_begin_parens.hpp>

#if BOOST_PP_VARIADICS_MSVC && _MSC_VER <= 1400

#define BOOST_PP_IS_BEGIN_PARENS(param) \
    BOOST_PP_DETAIL_IBP_SPLIT \
      ( \
      0, \
      BOOST_PP_DETAIL_IBP_CAT \
        ( \
        BOOST_PP_DETAIL_IBP_IS_VARIADIC_R_, \
        BOOST_PP_DETAIL_IBP_IS_VARIADIC_C param \
        ) \
      ) \
/**/

#else

#define BOOST_PP_IS_BEGIN_PARENS(...) \
    BOOST_PP_DETAIL_IBP_SPLIT \
      ( \
      0, \
      BOOST_PP_DETAIL_IBP_CAT \
        ( \
        BOOST_PP_DETAIL_IBP_IS_VARIADIC_R_, \
        BOOST_PP_DETAIL_IBP_IS_VARIADIC_C __VA_ARGS__ \
        ) \
      ) \
/**/

#endif /* BOOST_PP_VARIADICS_MSVC && _MSC_VER <= 1400 */
#endif /* BOOST_PP_VARIADICS */
#endif /* BOOST_PREPROCESSOR_IS_BEGIN_PARENS_HPP */

/* is_begin_parens.hpp
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
*/