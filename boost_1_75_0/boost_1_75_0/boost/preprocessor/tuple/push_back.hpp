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
# ifndef BOOST_PREPROCESSOR_TUPLE_PUSH_BACK_HPP
# define BOOST_PREPROCESSOR_TUPLE_PUSH_BACK_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_VARIADICS
#
# include <boost/preprocessor/array/push_back.hpp>
# include <boost/preprocessor/array/to_tuple.hpp>
# include <boost/preprocessor/tuple/to_array.hpp>
#
# /* BOOST_PP_TUPLE_PUSH_BACK */
#
# define BOOST_PP_TUPLE_PUSH_BACK(tuple, elem) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_PUSH_BACK(BOOST_PP_TUPLE_TO_ARRAY(tuple), elem)) \
/**/
#
# endif // BOOST_PP_VARIADICS
#
# endif // BOOST_PREPROCESSOR_TUPLE_PUSH_BACK_HPP

/* push_back.hpp
hfzUzw753Snqk17tc7cSg69+Fex65/Nn8XfiikpGrAJ5jctJPMZ+ejQ6NYbMOz2CPKheYoVneI+A5teS4IEWpQM2uCDsgxuhVAG6gTsGh5dGKL7IOLlZXySH/xw1y3C32zFKiMyOwsD2gU0Yo+D9E2mwe27Cu7LxqqQYczJrXzeG6CsXGAy6tYjRt3+ZaZdIJsj63NGo4x1NpjI34aw5nAt9XadIJMOKAkdUV6Fsq1kaO+iyEOk66Qqi8Cb2YoxUtFVuFNXkv53RviWRa8RnbTBCrdTiyY0x0Nj7+Q+OUPi+toQxvWCx8O6PeSAMul6ZXVEW4Izv3CynEg8QP5Z+16BeThVmuEjcZKYwD4afonLEpTVgEI0BWHVaZV0Yrj09oZSmFWqltdidDp19KrCQ1aSuUm+FtOgl8JithxppDHXUH5rT6EUH3/CB/9QBqgrirT82eGtTD+ubzlND/P3U7nxTvvr0hw+u+Zt7hJ6S/OB+hE97pmg0ux9EIsQgJRwfKcITS8hEUEMQEgdArvis+4U3P70wCyR/PfEE4mOFEuziBMIVhB/vIXZ+a7/T7kQ1lUsEKz/xP7H55+nuRt0U2kn0RZDcfG3tAA5s3rzGAdL2bZ3xb+/PlYZVzyqe5N3APNECOTPQfFoI+8gQfldh4oSAw7iAv8ro5j3Xjhg96JIQ963hOGFsQTxTwArY9yh0WgXg8qhVGItQyGbi
*/