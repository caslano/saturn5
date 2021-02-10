# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2014.                                    *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_ARRAY_DETAIL_GET_DATA_HPP
# define BOOST_PREPROCESSOR_ARRAY_DETAIL_GET_DATA_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
# include <boost/preprocessor/control/if.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/facilities/is_1.hpp>
#
# /* BOOST_PP_ARRAY_DETAIL_GET_DATA */
#
# define BOOST_PP_ARRAY_DETAIL_GET_DATA_NONE(size, data)

# if BOOST_PP_VARIADICS && !(BOOST_PP_VARIADICS_MSVC && _MSC_VER <= 1400)
#    if BOOST_PP_VARIADICS_MSVC
#       define BOOST_PP_ARRAY_DETAIL_GET_DATA_ANY_VC_DEFAULT(size, data) BOOST_PP_TUPLE_REM(size) data
#       define BOOST_PP_ARRAY_DETAIL_GET_DATA_ANY_VC_CAT(size, data) BOOST_PP_TUPLE_REM_CAT(size) data
#       define BOOST_PP_ARRAY_DETAIL_GET_DATA_ANY(size, data) \
            BOOST_PP_IIF \
                ( \
                BOOST_PP_IS_1(size), \
                BOOST_PP_ARRAY_DETAIL_GET_DATA_ANY_VC_CAT, \
                BOOST_PP_ARRAY_DETAIL_GET_DATA_ANY_VC_DEFAULT \
                ) \
            (size,data) \
/**/
#    else
#       define BOOST_PP_ARRAY_DETAIL_GET_DATA_ANY(size, data) BOOST_PP_TUPLE_REM(size) data
#    endif
# else
#    define BOOST_PP_ARRAY_DETAIL_GET_DATA_ANY(size, data) BOOST_PP_TUPLE_REM(size) data
# endif

# define BOOST_PP_ARRAY_DETAIL_GET_DATA(size, data) \
    BOOST_PP_IF \
        ( \
        size, \
        BOOST_PP_ARRAY_DETAIL_GET_DATA_ANY, \
        BOOST_PP_ARRAY_DETAIL_GET_DATA_NONE \
        ) \
    (size,data) \
/**/
#
# endif /* BOOST_PREPROCESSOR_ARRAY_DETAIL_GET_DATA_HPP */

/* get_data.hpp
qWByAQAAQAIAACkACQAAAAAAAQAAAAAAtaYFAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL2ludGVyZmFjZS5kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUj5xami6AAAABgEAACQACQAAAAAAAQAAAAAAd6gFAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL2lwdjQuZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIIVFhgugAAAAYBAAAkAAkAAAAAAAEAAAAAAHypBQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9pcHY2LmRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSOHbirfcAAACPAQAANAAJAAAAAAABAAAAAACBqgUAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvanVuay1zZXNzaW9uLWNvb2tpZXMuZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJookjeVwEAAEMCAAAuAAkAAAAAAAEAAAAAANOrBQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9rZWVwYWxpdmUtdGltZS5kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUiqOS4fWAAAA
*/