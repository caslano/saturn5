# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2003.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_FACILITIES_IS_EMPTY_OR_1_HPP
# define BOOST_PREPROCESSOR_FACILITIES_IS_EMPTY_OR_1_HPP
#
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/facilities/empty.hpp>
# include <boost/preprocessor/facilities/identity.hpp>
# include <boost/preprocessor/facilities/is_1.hpp>
# include <boost/preprocessor/facilities/is_empty.hpp>
#
# /* BOOST_PP_IS_EMPTY_OR_1 */
#
# define BOOST_PP_IS_EMPTY_OR_1(x) \
    BOOST_PP_IIF( \
        BOOST_PP_IS_EMPTY(x BOOST_PP_EMPTY()), \
        BOOST_PP_IDENTITY(1), \
        BOOST_PP_IS_1 \
    )(x) \
    /**/
#
# endif

/* is_empty_or_1.hpp
ACcACQAAAAAAAQAAAAAAp8YHAGN1cmwtbWFzdGVyL2RvY3MvZXhhbXBsZXMvZ2V0aW5tZW1vcnkuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKbg42H9AMAADMJAAAnAAkAAAAAAAEAAAAAAI3MBwBjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzL2dldHJlZGlyZWN0LmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSvq0kkNkQAAAkMAAAIgAJAAAAAAABAAAAAADP0AcAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9naGlwZXIuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKkENUC9hAAAJAvAAAlAAkAAAAAAAEAAAAAAPHhBwBjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzL2hpcGVyZmlmby5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUsJCQltvBAAAdQoAACoACQAAAAAAAQAAAAAAM/MHAGN1cmwtbWFzdGVyL2RvY3MvZXhhbXBsZXMvaHJlZl9leHRyYWN0b3IuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlL3XPOAQAYAAIEPAAAkAAkAAAAAAAEAAAAAAPP3BwBjdXJsLW1h
*/