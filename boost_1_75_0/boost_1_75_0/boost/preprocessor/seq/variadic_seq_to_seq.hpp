# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2012.                                  *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_SEQ_VARIADIC_SEQ_TO_SEQ_HPP
# define BOOST_PREPROCESSOR_SEQ_VARIADIC_SEQ_TO_SEQ_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_VARIADIC_SEQ_TO_SEQ */
#
# if BOOST_PP_VARIADICS
#    define BOOST_PP_VARIADIC_SEQ_TO_SEQ(vseq) BOOST_PP_CAT(BOOST_PP_VARIADIC_SEQ_TO_SEQ_A vseq, 0)
#    define BOOST_PP_VARIADIC_SEQ_TO_SEQ_A(...) ((__VA_ARGS__)) BOOST_PP_VARIADIC_SEQ_TO_SEQ_B
#    define BOOST_PP_VARIADIC_SEQ_TO_SEQ_B(...) ((__VA_ARGS__)) BOOST_PP_VARIADIC_SEQ_TO_SEQ_A
#    define BOOST_PP_VARIADIC_SEQ_TO_SEQ_A0
#    define BOOST_PP_VARIADIC_SEQ_TO_SEQ_B0
# endif
#
# endif

/* variadic_seq_to_seq.hpp
OmBJU30iNG/qw/09YHQAGjoySHWfWpf1pz9Qxpcrp2liEfmBAPTHd4SlBAgD6CkNCZCHm8cBX80er5icQPkls0L26/otKAH+eVJ3hrUBOeyUyLaurj9Bev0CXs2I47aZSu6b+Q7IwRFI6DLgATRIk/wIzqCqNQiC03wLheIiX/7N3l6ofTSM/7+9zV3kHSwc/2XCOuFoBtKnWPqNyh/caL/M3kfHR39vlpALxJN7wmP7hNvU+ALLm6w55G8bQzPALfFCiYvDvQ+4GpZdOxtG46zbQ8ouh+XBNMXRkTQY7WcrgvFDsVAXHfefVGkKKdfJGpEEdqcBYNEu8h7imvEOYZ2SroB5UbDJ/TL89v7W9mB8fxjgf1aRAijCcGAyn5EtEuIdTRxRepWmmB8PpYmJjX2XKIs8EVO7kPzU387ONzobFh/nTRyPvffC9W/V+b8V53UZtT4ly7d/7IZ8oDuvu0C2rat8fWCu2CvFkwiBMSmjsoC5G9/a556O9nRcS8MmuLs2FXxhNxeZEKlNi4yIUZ0xXgpvFhnRy8wtcKA2pWTU64Q3JS92CgifseTJBA5/FU/6eglJj9iK5oH369jcNX0sNi2rslQwd/n77b+VPsP7yBUuIVqiOxsnPuOitgjreyDJlvwdcLlWzHPGfXmqzKikKV784v0DyZ/36+8u63pPes09nsny4tqVJ5MBnsBf8pfIQltJ/4rdr6Ma
*/