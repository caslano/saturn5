# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2013.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_TUPLE_PUSH_FRONT_HPP
# define BOOST_PREPROCESSOR_TUPLE_PUSH_FRONT_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_VARIADICS
#
# include <boost/preprocessor/array/push_front.hpp>
# include <boost/preprocessor/array/to_tuple.hpp>
# include <boost/preprocessor/tuple/to_array.hpp>
#
#
# /* BOOST_PP_TUPLE_PUSH_FRONT */
#
# define BOOST_PP_TUPLE_PUSH_FRONT(tuple, elem) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_PUSH_FRONT(BOOST_PP_TUPLE_TO_ARRAY(tuple), elem)) \
/**/
#
# endif // BOOST_PP_VARIADICS
#
# endif // BOOST_PREPROCESSOR_TUPLE_PUSH_FRONT_HPP

/* push_front.hpp
nazImzI4nbpBtyFRWdgOyAuaUXSSOj3B6njhZw34s6z6RTGKwnTglFxR5nSK5hSOrvPsBpKXzkiX4I/BLjvXh+a+JAn5rPsx1T1X3jMn8SPHmiaChrGwM0vLCR2KvqArzv4FsWr0zfKHWhSS8mVCJDsN9RlnpnoZZqrGQYUV79dp32+QyQ4aT3vVdLsmCOG1RkC/EtMGHEZYaCQhVL7i5SyQC5bSSjC0Hv1h2wW5tYESXZ6UvO8w0GCtNgsTh/IC0QW6NsKr5ebRDedSvlOyvUgiGAPlTPyQ1TJYbNfcSA9hdUaasK5fhjfDRqIiEIGLFVANzleLNLmMyLEsaHTgAT06eQL920v+nS99+lMSD/+R16/Dio2rQRFXJe+QlXJjdgm5kyIJsaHNrpoLOCcwFF+Q/h9KACCNVM/8CHCNuJ5wrkirq7K+adDwoPZi5k+OlqTz+I4QJyfVoQO8hdufJPY2zKLz4ieT1hjArcjn1rZJeA3xVqVG4H8RUvQQ25O5nHjaW06ba9OPJ77xInLB2+oCkl0dSAH/f0AXIZOQZim+dOzPXGd4HDVOlA==
*/