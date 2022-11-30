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

# if !(BOOST_PP_VARIADICS_MSVC && _MSC_VER <= 1400)
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
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
*/