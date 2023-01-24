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
# ifndef BOOST_PREPROCESSOR_TUPLE_POP_FRONT_HPP
# define BOOST_PREPROCESSOR_TUPLE_POP_FRONT_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_VARIADICS
#
# include <boost/preprocessor/array/pop_front.hpp>
# include <boost/preprocessor/array/to_tuple.hpp>
# include <boost/preprocessor/comparison/greater.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/tuple/size.hpp>
# include <boost/preprocessor/tuple/to_array.hpp>
#
#
# /* BOOST_PP_TUPLE_POP_FRONT */
#
# define BOOST_PP_TUPLE_POP_FRONT(tuple) \
    BOOST_PP_IIF \
        ( \
        BOOST_PP_GREATER(BOOST_PP_TUPLE_SIZE(tuple),1), \
        BOOST_PP_TUPLE_POP_FRONT_EXEC, \
        BOOST_PP_TUPLE_POP_FRONT_RETURN \
        ) \
    (tuple) \
/**/
#
# define BOOST_PP_TUPLE_POP_FRONT_EXEC(tuple) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_POP_FRONT(BOOST_PP_TUPLE_TO_ARRAY(tuple))) \
/**/
#
# define BOOST_PP_TUPLE_POP_FRONT_RETURN(tuple) tuple
#
# /* BOOST_PP_TUPLE_POP_FRONT_Z */
#
# define BOOST_PP_TUPLE_POP_FRONT_Z(z, tuple) \
    BOOST_PP_IIF \
        ( \
        BOOST_PP_GREATER(BOOST_PP_TUPLE_SIZE(tuple),1), \
        BOOST_PP_TUPLE_POP_FRONT_Z_EXEC, \
        BOOST_PP_TUPLE_POP_FRONT_Z_RETURN \
        ) \
    (z, tuple) \
/**/
#
# define BOOST_PP_TUPLE_POP_FRONT_Z_EXEC(z, tuple) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_POP_FRONT_Z(z, BOOST_PP_TUPLE_TO_ARRAY(tuple))) \
/**/
#
# define BOOST_PP_TUPLE_POP_FRONT_Z_RETURN(z, tuple) tuple
#
# endif // BOOST_PP_VARIADICS
#
# endif // BOOST_PREPROCESSOR_TUPLE_POP_FRONT_HPP

/* pop_front.hpp
m+Ynn0lapS3aX1mdwo/cbiFxX4ev47G43eYC42JeD5eUxkO+xbyeeChtyRfa7pt0f8H26RhRnWWdtVRZsqdD1sWySMyOvS4IJ16LIK/MKOw12DWTnVvEhEh9Wgk1/ipY2fBBeNQfe59l9DNLNE7JRcPa+3RzsdgBBxZ5xPbWmNMBaJPTp1GlnMoYRWvwD7PB3HkfEMTgK3bNW98s8maIHTWnhvWTr5n35qbE/cL0ryUftDUyowYX1GrFi64S6G50zaUTwzv5KwJuV1w/V8kshyYPAyOqda9jh5FOULXxxLuX/2SbuFOD4t/tkmnXnXA+j9M96UK0pPUtQSVoZm/WlwX7nEtLlWWHAHc1sLlwhb5g/rO/pGKoEfATf1pkIoc3f2JMnchZjB7kc6Lt9Z9C9Z/NyfOlKlEWp/h3Tf2q9sVwXp7pAjGiy/EBkTdOviiA8O5AIiiZG2QwpJ93GAD/R1sAcsPA+U2QL0Jw/7H5ewgcH1l+qzMh88n3pm9/nwaDh3wV1hZSz6cUVqH3hNRi4ABXvLiQ4z95dQP7Am9HVEUhrf6HpwTBwQ9laOLqY2JBDwFn97D3Q1JoRpet+1zp9/SWM1fUlpBW82Fp0xnOkyEUKa/XFk+eEXsgaYBx791KuoeuqQ57X1lCr/up6XJsQ/Uxe4Kx9qVPk+7OL3+nC78/hkAva1bZej1P22bcnVvZz8jS2V6wDlDshQuT
*/