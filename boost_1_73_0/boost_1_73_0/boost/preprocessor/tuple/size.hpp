# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_TUPLE_SIZE_HPP
# define BOOST_PREPROCESSOR_TUPLE_SIZE_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/variadic/size.hpp>
#
# if BOOST_PP_VARIADICS
#    if BOOST_PP_VARIADICS_MSVC
#        define BOOST_PP_TUPLE_SIZE(tuple) BOOST_PP_CAT(BOOST_PP_VARIADIC_SIZE tuple,)
#    else
#        define BOOST_PP_TUPLE_SIZE(tuple) BOOST_PP_VARIADIC_SIZE tuple
#    endif
# endif
#
# endif

/* size.hpp
bGliL21pbWUuaFVUBQABtkgkYFBLAQIXAwoAAAAIAC1nSlJ5JlWFTxwAAM5RAAAfAAkAAAAAAAEAAADtgfjIHQBjdXJsLW1hc3Rlci9saWIvbWstY2EtYnVuZGxlLnBsVVQFAAG2SCRgUEsBAhcDCgAAAAgALWdKUvu80K9zFQAA40AAACAACQAAAAAAAQAAAO2BjeUdAGN1cmwtbWFzdGVyL2xpYi9tay1jYS1idW5kbGUudmJzVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUqt5jrEZHwAAMXcAABkACQAAAAAAAQAAAAAAR/sdAGN1cmwtbWFzdGVyL2xpYi9tcHJpbnRmLmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSUMSt4DESAAAuRAAAFgAJAAAAAAABAAAAAACgGh4AY3VybC1tYXN0ZXIvbGliL21xdHQuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIcMpENgQMAAMsHAAAWAAkAAAAAAAEAAAAAAA4tHgBjdXJsLW1hc3Rlci9saWIvbXF0dC5oVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUraIrINVaQAAdpsBABcACQAAAAAAAQAAAAAAzDAeAGN1cmwtbWFzdGVyL2xpYi9tdWx0
*/