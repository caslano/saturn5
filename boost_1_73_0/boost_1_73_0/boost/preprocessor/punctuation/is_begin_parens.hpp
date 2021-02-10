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
c3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX0dTU0FQSV9ERUxFR0FUSU9OLjNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS61qU0n8EAACeCQAAQQAJAAAAAAABAAAAAACN8w8AY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9IQVBQWV9FWUVCQUxMU19USU1FT1VUX01TLjNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS85UqhtcDAAB9CAAANwAJAAAAAAABAAAAAAB0+A8AY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9IQVBST1hZUFJPVE9DT0wuM1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJmEplbqgQAADUKAAAuAAkAAAAAAAEAAAAAAKn8DwBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX0hFQURFUi4zVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUpYls251BAAAGAoAADIACQAAAAAAAQAAAAAAqAEQAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfSEVBREVSREFUQS4zVVQFAAG2
*/