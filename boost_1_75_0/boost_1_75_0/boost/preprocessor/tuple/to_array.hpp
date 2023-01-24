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
# ifndef BOOST_PREPROCESSOR_TUPLE_TO_ARRAY_HPP
# define BOOST_PREPROCESSOR_TUPLE_TO_ARRAY_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/facilities/overload.hpp>
# include <boost/preprocessor/tuple/size.hpp>
# include <boost/preprocessor/variadic/size.hpp>
#
# /* BOOST_PP_TUPLE_TO_ARRAY */
#
# if BOOST_PP_VARIADICS
#    if BOOST_PP_VARIADICS_MSVC
#        define BOOST_PP_TUPLE_TO_ARRAY(...) BOOST_PP_TUPLE_TO_ARRAY_I(BOOST_PP_OVERLOAD(BOOST_PP_TUPLE_TO_ARRAY_, __VA_ARGS__), (__VA_ARGS__))
#        define BOOST_PP_TUPLE_TO_ARRAY_I(m, args) BOOST_PP_TUPLE_TO_ARRAY_II(m, args)
#        define BOOST_PP_TUPLE_TO_ARRAY_II(m, args) BOOST_PP_CAT(m ## args,)
#        define BOOST_PP_TUPLE_TO_ARRAY_1(tuple) (BOOST_PP_TUPLE_SIZE(tuple), tuple)
#    else
#        define BOOST_PP_TUPLE_TO_ARRAY(...) BOOST_PP_OVERLOAD(BOOST_PP_TUPLE_TO_ARRAY_, __VA_ARGS__)(__VA_ARGS__)
#        define BOOST_PP_TUPLE_TO_ARRAY_1(tuple) (BOOST_PP_VARIADIC_SIZE tuple, tuple)
#    endif
#    define BOOST_PP_TUPLE_TO_ARRAY_2(size, tuple) (size, tuple)
# else
#    define BOOST_PP_TUPLE_TO_ARRAY(size, tuple) (size, tuple)
# endif
#
# endif

/* to_array.hpp
TvhBUzlIBC+/3bf8liR604fgXJhOjws13caI+5h6WHd2T6Y0NVMYJLLUW8Ywl68r0NsdD9HE1FrDrxJYqG1+6vupOZVnfJUc+dH2PJGGY4P4iH3muKw+6y0QA/HD3KxInh0lMCt2iv1XWaHj1G7twfCcK0vKbNPlBJzHIxXH6/R3geWPuqCMAPnskLmHADrWfvR/ddEBLzWFqQ8In/ysxcIBMpO7670P6/RVUuI8U1Gh8ogd79/oiArSwE9osL/Nm6a1fZAKq7B383KmlI4tb119Yt5C3vC40b1my1NZREKLI25b68/TbpE3eL8ISEGKQPm8x7y3us8PXFw3rJeKiJ8mxes73vlcBM9j7o6rKkI+BDH2wm5ukc7iqA6ZP8pRimRA2ECGHEXnTX2JFJp5/GTvZuJpuj7r9Tzd2ppTEqoWnB9yDNDhqofToXP2nwZYnZgxPaM1mQ0faJkHKWPpDDJp54CXxcWjkxjzsRGFAR7itMoz2Rb82XZHY3hyF/13P7+QukskOaPGuTlyYMSEJTrjdNMUVoxXY25Ecg8mOUcTHsmv5leT6lyMkzv1j5jWCmFFEOavn0barxMvZ75vFYdHmLnZcmGrvxFdU5/FYMasNud/QB1IkP8LlczE7m9oQMa0FE3lypuFAyHnVYFJ48aYM0BfcVuCzDTRN642S12FU5eNJZl/qdRtcDanQewJUXQop/QnnbEjWh2+
*/