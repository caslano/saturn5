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
rZjb2V/N6L09sYX4aldDIFrKI7sw5W8v0JfGMp/p5Uj+fKl+L1ZiJwGW9+Lvs1KoO1L8h5eztED8kU2fz3b06D9j/U1pJyP8zzuMY0WzVrSPqCCtKwe0rbxpXO9j1IdqXKQ2JoTFrNlmeeWZ1aGpebjaUK2mhfJC1i+0a87kcI5m0JB1elZtoTG+Q54l6FgxD0jP73724x4Nxnt2ziw53Wfb9DaKiUvHb+ApwD0T87NEFLMe0+X0rMICQZ8D+dUgAA7Yy0K86V4mnFFvPA1fCIh/OueNSthfdog8k9/CytguCsqHzPbM3XOVS4QtEZaiKGzLatnDxPfyQujgI05gskMW4tEWG/p3YB1aylHZm25/3LM330xvrVmOxx9dsy/HyW+muq74wCofTQ8a3LrxHuqFBT/3rKedjo9mdp69U/AwgB22fhXrX1dUILL7bQSuIDKi95H8NBYQ0v0l6KhPADVIHy3oFuVqxON3A2+5gR7u+sjaCtEdiSFLnj4KDa04DtVDl5SxQO2kI7rIiH8l1j21I0a1nx7xEy2iBFfCddeYHGdh5L3lecaUwWrg0lQsd70QZ5ZjC2PkZXWo09mL4PpUrhVWeppHA18l6kpfc92mpAq5qYETVlNie4hZrUCdb3NmlaXhKqA5jtom5wJbZ1inrskRd330rl6qMoRdHBfQEFev7hkRg0LxRb9JLa4Wad4QPk1yaWuyjT/O
*/