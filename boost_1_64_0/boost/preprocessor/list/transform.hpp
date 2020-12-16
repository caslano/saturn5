# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_LIST_TRANSFORM_HPP
# define BOOST_PREPROCESSOR_LIST_TRANSFORM_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/list/fold_right.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_LIST_TRANSFORM */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_TRANSFORM(op, data, list) BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_LIST_FOLD_RIGHT(BOOST_PP_LIST_TRANSFORM_O, (op, data, BOOST_PP_NIL), list))
# else
#    define BOOST_PP_LIST_TRANSFORM(op, data, list) BOOST_PP_LIST_TRANSFORM_I(op, data, list)
#    define BOOST_PP_LIST_TRANSFORM_I(op, data, list) BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_LIST_FOLD_RIGHT(BOOST_PP_LIST_TRANSFORM_O, (op, data, BOOST_PP_NIL), list))
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_TRANSFORM_O(d, odr, elem) BOOST_PP_LIST_TRANSFORM_O_D(d, BOOST_PP_TUPLE_ELEM(3, 0, odr), BOOST_PP_TUPLE_ELEM(3, 1, odr), BOOST_PP_TUPLE_ELEM(3, 2, odr), elem)
# else
#    define BOOST_PP_LIST_TRANSFORM_O(d, odr, elem) BOOST_PP_LIST_TRANSFORM_O_I(d, BOOST_PP_TUPLE_REM_3 odr, elem)
#    define BOOST_PP_LIST_TRANSFORM_O_I(d, im, elem) BOOST_PP_LIST_TRANSFORM_O_D(d, im, elem)
# endif
#
# define BOOST_PP_LIST_TRANSFORM_O_D(d, op, data, res, elem) (op, data, (op(d, data, elem), res))
#
# /* BOOST_PP_LIST_TRANSFORM_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_TRANSFORM_D(d, op, data, list) BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_LIST_FOLD_RIGHT_ ## d(BOOST_PP_LIST_TRANSFORM_O, (op, data, BOOST_PP_NIL), list))
# else
#    define BOOST_PP_LIST_TRANSFORM_D(d, op, data, list) BOOST_PP_LIST_TRANSFORM_D_I(d, op, data, list)
#    define BOOST_PP_LIST_TRANSFORM_D_I(d, op, data, list) BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_LIST_FOLD_RIGHT_ ## d(BOOST_PP_LIST_TRANSFORM_O, (op, data, BOOST_PP_NIL), list))
# endif
#
# endif

/* transform.hpp
pWQZWU4aZAVZSQbJKrKarCHryAayiWwht5HbyVayjdxB7iTbyQ6yk+wiu8kecg/ZS+4n+8h+coAcJA+RQ6Qih8kRcpQcI8dJ2yNCO+kgnaSLdJMeMplMIVPJNDKdzCCzyGwyh8wl88kCspD0ksVkCVlKlpHlpEFWkJVkkKwiq8kaso5sIJvIFnIbuZ1sJdvIHeROsp3sIDvJLrKb7CH3kL3kfrKP7CcHyEHyEDlEKnKYHCFHyTFynLR1Ce2kg3SSLtJNeshkMoVMJdPIdDKDzCKzyRwyl8wnC8hC0ksWkyVkKVlGlpMGWUFWkkGyiqwma8g6soFsIlvIbeR2spVsI3d0Mf3JdrKD7CS7yG6yp4vpT/aS+8k+sp8cIAfJQ+QQqchhcoQcJcfIcdL2qNBOOkgn6SLdpIdMJlPIVDKNTCczyCwym8whc8l8soAsJL1kMVlClpJlZDlpkBVkJRkkq8hqsoasIxvIJrKF3EZuJ1vJNnIHuZNsJzvITrKL7CZ7yD1kL7mf7CP7yQFykDxEDpGKHCZHyFFyjBwnbY8J7aSDdJIu0k16yGQyhUwl08h0MoPMIrPJHDKXzCcLyELSSxaTJWQpWUaWkwZZQVaSQbKKrCZryDqygWwiW8ht5HaylWwjd5A7yXayg+wku8husofcQ/aS+8k+sp8cIAfJQ+QQqchhcoQcJcfIcdL2uNBOOkgn6SLdpIdMJlPIVDKNTCczyCwym8whc8l8soAsJL1kMVlClpJlZDlpkBVkJRkkq8hqsoasIxvIJrKF3EZuJ1vJNnIHuZNsJzvITrKL7CZ7yD1kL7mf7CP7yQFykDxEDpGKHCZHyFFyjBwnbd1CO+kgnaSLdJMeMplMIVPJNDKdzCCzyGwyh8wl88kCspD0ksVkCVlKlpHlpEFWkJVkkKwiq8kaso5sIJvIFnIbuZ1sJdvIHeROsp3sIDvJLrKb7CH3kL3kfrKP7CcHyEHyEDlEKnKYHCFHyTFynLQ9IbSTDtJJukg36SGTyRQylUwj08kMMovMJnPIXDKfLCALSS9ZTJaQpWQZWU4aZAVZSQbJKrKarCHryAayiWwht5HbyVayjdxB7iTbyQ6yk+wiu8kecg/ZS+4n+8h+coAcJA+RQ6Qih8kRcpQcI8dJ25NCO+kgnaSLdJMeMplMIVPJNDKdzCCzyGwyh8wl88kCspD0ksVkCVlKlpHlpEFWkJVkkKwiq8kaso5sIJvIFnIbuZ1sJdvIHeROsp3sIDvJLrKb7CH3kL3kfrKP7CcHyEHyEDlEKnKYHCFHyTFynLQ9JbSTDtJJukg36SGTyRQylUwj08kMMovMJnPIXDKfLCALSS9ZTJaQpWQZWU4aZAVZSQbJKrKarCHryAayiWwht5HbyVayjdxB7iTbyQ6yk+wiu8kecg/ZS+4n+8h+coAcJA+RQ6Qih8kRcpQcI8dJW4/QTjpIJ+ki3aSHTCZTyFQyjUwnM8gsMpvMIXPJfLKALCS9ZDFZQpaSZWQ5aZAVZCUZJKvIarKGrCMbyCayhdxGbidbyTZyRw/Tn2wnO8hOsovsJnt6mP5kL7mf7CP7yQFykDxEDpGKHCZHyFFyjBwnbVzLtZOOf/F2JuBRXHUAH05jxKZqva+xFjlMAoSCGA7J2VADxCRNaS2ETXbDLmyy6x4ctVYEVGio8nlUVKyotdYb+6EiaqXggVhrvSpiVbzXFisiKipaf///mzczOwTw+D4Dv5k37/3ffR8zq9cJer1Ur5fp9Rl6fY5eXb1eodfJeq3W63S9XqnXOXqdp9eFem3Wa5te2/XaodduvS7T6w16XanXuF6Tek3rNavXgl7X6/UmvW7U6xa9btXrdr0=
*/