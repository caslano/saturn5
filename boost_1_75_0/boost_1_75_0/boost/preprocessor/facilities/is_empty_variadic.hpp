# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2014,2019.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_FACILITIES_IS_EMPTY_VARIADIC_HPP
# define BOOST_PREPROCESSOR_FACILITIES_IS_EMPTY_VARIADIC_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_VARIADICS
#
# include <boost/preprocessor/punctuation/is_begin_parens.hpp>
# include <boost/preprocessor/facilities/detail/is_empty.hpp>
#
#if BOOST_PP_VARIADICS_MSVC && _MSC_VER <= 1400
#
#define BOOST_PP_IS_EMPTY(param) \
    BOOST_PP_DETAIL_IS_EMPTY_IIF \
      ( \
      BOOST_PP_IS_BEGIN_PARENS \
        ( \
        param \
        ) \
      ) \
      ( \
      BOOST_PP_IS_EMPTY_ZERO, \
      BOOST_PP_DETAIL_IS_EMPTY_PROCESS \
      ) \
    (param) \
/**/
#define BOOST_PP_IS_EMPTY_ZERO(param) 0
# else
# if defined(__cplusplus) && __cplusplus > 201703L
# include <boost/preprocessor/variadic/has_opt.hpp>
#define BOOST_PP_IS_EMPTY(...) \
    BOOST_PP_DETAIL_IS_EMPTY_IIF \
      ( \
      BOOST_PP_VARIADIC_HAS_OPT() \
      ) \
      ( \
      BOOST_PP_IS_EMPTY_OPT, \
      BOOST_PP_IS_EMPTY_NO_OPT \
      ) \
    (__VA_ARGS__) \
/**/
#define BOOST_PP_IS_EMPTY_FUNCTION2(...) \
    __VA_OPT__(0,) 1 \
/**/
#define BOOST_PP_IS_EMPTY_FUNCTION(...) \
    BOOST_PP_IS_EMPTY_FUNCTION2(__VA_ARGS__) \
/**/
#define BOOST_PP_IS_EMPTY_OPT(...) \
    BOOST_PP_VARIADIC_HAS_OPT_ELEM0(BOOST_PP_IS_EMPTY_FUNCTION(__VA_ARGS__),) \
/**/
# else
#define BOOST_PP_IS_EMPTY(...) \
    BOOST_PP_IS_EMPTY_NO_OPT(__VA_ARGS__) \
/**/
# endif /* defined(__cplusplus) && __cplusplus > 201703L */
#define BOOST_PP_IS_EMPTY_NO_OPT(...) \
    BOOST_PP_DETAIL_IS_EMPTY_IIF \
      ( \
      BOOST_PP_IS_BEGIN_PARENS \
        ( \
        __VA_ARGS__ \
        ) \
      ) \
      ( \
      BOOST_PP_IS_EMPTY_ZERO, \
      BOOST_PP_DETAIL_IS_EMPTY_PROCESS \
      ) \
    (__VA_ARGS__) \
/**/
#define BOOST_PP_IS_EMPTY_ZERO(...) 0
# endif /* BOOST_PP_VARIADICS_MSVC && _MSC_VER <= 1400 */
# endif /* BOOST_PP_VARIADICS */
# endif /* BOOST_PREPROCESSOR_FACILITIES_IS_EMPTY_VARIADIC_HPP */

/* is_empty_variadic.hpp
77E+88DVzXgl0KQKF4J9a32hxuX1ungnROpD28pY23bTYcjHqhDVFAdnIf6N+IvatoHno/NxO9CH3oO3kf9cynMKMgp1zn/BI746POQDv3thPeQ1OIKDcDBJgrWQtROFRB/gk2m3eltNPZ49tz04PbF0hy9WSdb9WoXMLhS1gFYqH6pLPxOU2sSHFYYVpM73PgQujLWYS9hrqA5IT9lwr4+OqOdI56jnKM1IzmgbO1N/wpACLph/bWctVImJEArTO+IVrKELIQu9CwDWUpMi4U7pX7ycRMfZoUwnu57Vvv860JQHiKX4iEJgrpf2XiWW4bue2/DcEOu6nAfuVeuYXL9HroAduXmmrVLnbo730ZcTTZ1ZWWXdnFTLY0aN1FTKqQm9db05hYyVrfdcxRl+ZnR5jL8O+utshMI2ZIdifqTWogHHE+eYOL+Xqq4TsFiEtpfh6P5V4ItPFq8rt13Od4xU2/6i0lBl21o87D69gD+fSPY8IEDbI+x2wkQH6nMJLTnvygSKqarWg+aThfHCfeLvKy7cRByEHb8iP7Cdl+r+hd9XkSt5a41CKabw10e9mtxG5EFd2y1bZt1zTEGoXO/naFnaX/F0UhBxYQHieOWIkO9x7+1pqz1lw7mN3k9fbKNYpv/izevokugxDaSzlGlDzYarMyanOhX5KEG+bDimF6jlYzxhy1SVFmSSUhm7Y4Wbj6Rzq9cvU2Oj
*/