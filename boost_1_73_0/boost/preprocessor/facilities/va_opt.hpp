# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2019.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_FACILITIES_VA_OPT_HPP
# define BOOST_PREPROCESSOR_FACILITIES_VA_OPT_HPP
# include <boost/preprocessor/variadic/has_opt.hpp>
# if BOOST_PP_VARIADIC_HAS_OPT()
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/facilities/check_empty.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
# define BOOST_PP_VA_OPT_IMPL(atuple) \
    BOOST_PP_TUPLE_REM() atuple       \
/**/
# define BOOST_PP_VA_OPT(rdata,rempty,...)     \
    BOOST_PP_VA_OPT_IMPL                       \
        (                                      \
        BOOST_PP_IIF                           \
            (                                  \
            BOOST_PP_CHECK_EMPTY(__VA_ARGS__), \
            rempty,                            \
            rdata                              \
            )                                  \
        )                                      \
/**/
# endif /* BOOST_PP_VARIADIC_HAS_OPT() */
# endif /* BOOST_PREPROCESSOR_FACILITIES_VA_OPT_HPP */

/* va_opt.hpp
YS6ksz+6rEApHwy43xHr9Y2QHv3M90VK+3mVF0tGS3C2PW/+G7KE+2GUF7sK4wnX3vD82qQP0KDv5MWK8NxxE6RPjTZB/cRjc5oX64t192ZIL+//BrTlGLMZXmwQnqtskM68bwKUFstwkxfbiPYnSHf+bP47SluX5sVmYN1NhHmX9a9ulC0s3UtpexY6t5/+ODQzGGsYiDsvSLJFkP7i15fg1Irx3OTFfHG5xZA+MereOcrx
*/