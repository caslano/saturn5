# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# include <boost/preprocessor/slot/detail/shared.hpp>
#
# undef BOOST_PP_LOCAL_FE
#
# undef BOOST_PP_LOCAL_FE_DIGIT_1
# undef BOOST_PP_LOCAL_FE_DIGIT_2
# undef BOOST_PP_LOCAL_FE_DIGIT_3
# undef BOOST_PP_LOCAL_FE_DIGIT_4
# undef BOOST_PP_LOCAL_FE_DIGIT_5
# undef BOOST_PP_LOCAL_FE_DIGIT_6
# undef BOOST_PP_LOCAL_FE_DIGIT_7
# undef BOOST_PP_LOCAL_FE_DIGIT_8
# undef BOOST_PP_LOCAL_FE_DIGIT_9
# undef BOOST_PP_LOCAL_FE_DIGIT_10
#
# if BOOST_PP_SLOT_TEMP_3 == 0
#    define BOOST_PP_LOCAL_FE_DIGIT_3 0
# elif BOOST_PP_SLOT_TEMP_3 == 1
#    define BOOST_PP_LOCAL_FE_DIGIT_3 1
# elif BOOST_PP_SLOT_TEMP_3 == 2
#    define BOOST_PP_LOCAL_FE_DIGIT_3 2
# elif BOOST_PP_SLOT_TEMP_3 == 3
#    define BOOST_PP_LOCAL_FE_DIGIT_3 3
# elif BOOST_PP_SLOT_TEMP_3 == 4
#    define BOOST_PP_LOCAL_FE_DIGIT_3 4
# elif BOOST_PP_SLOT_TEMP_3 == 5
#    define BOOST_PP_LOCAL_FE_DIGIT_3 5
# elif BOOST_PP_SLOT_TEMP_3 == 6
#    define BOOST_PP_LOCAL_FE_DIGIT_3 6
# elif BOOST_PP_SLOT_TEMP_3 == 7
#    define BOOST_PP_LOCAL_FE_DIGIT_3 7
# elif BOOST_PP_SLOT_TEMP_3 == 8
#    define BOOST_PP_LOCAL_FE_DIGIT_3 8
# elif BOOST_PP_SLOT_TEMP_3 == 9
#    define BOOST_PP_LOCAL_FE_DIGIT_3 9
# endif
#
# if BOOST_PP_SLOT_TEMP_2 == 0
#    define BOOST_PP_LOCAL_FE_DIGIT_2 0
# elif BOOST_PP_SLOT_TEMP_2 == 1
#    define BOOST_PP_LOCAL_FE_DIGIT_2 1
# elif BOOST_PP_SLOT_TEMP_2 == 2
#    define BOOST_PP_LOCAL_FE_DIGIT_2 2
# elif BOOST_PP_SLOT_TEMP_2 == 3
#    define BOOST_PP_LOCAL_FE_DIGIT_2 3
# elif BOOST_PP_SLOT_TEMP_2 == 4
#    define BOOST_PP_LOCAL_FE_DIGIT_2 4
# elif BOOST_PP_SLOT_TEMP_2 == 5
#    define BOOST_PP_LOCAL_FE_DIGIT_2 5
# elif BOOST_PP_SLOT_TEMP_2 == 6
#    define BOOST_PP_LOCAL_FE_DIGIT_2 6
# elif BOOST_PP_SLOT_TEMP_2 == 7
#    define BOOST_PP_LOCAL_FE_DIGIT_2 7
# elif BOOST_PP_SLOT_TEMP_2 == 8
#    define BOOST_PP_LOCAL_FE_DIGIT_2 8
# elif BOOST_PP_SLOT_TEMP_2 == 9
#    define BOOST_PP_LOCAL_FE_DIGIT_2 9
# endif
#
# if BOOST_PP_SLOT_TEMP_1 == 0
#    define BOOST_PP_LOCAL_FE_DIGIT_1 0
# elif BOOST_PP_SLOT_TEMP_1 == 1
#    define BOOST_PP_LOCAL_FE_DIGIT_1 1
# elif BOOST_PP_SLOT_TEMP_1 == 2
#    define BOOST_PP_LOCAL_FE_DIGIT_1 2
# elif BOOST_PP_SLOT_TEMP_1 == 3
#    define BOOST_PP_LOCAL_FE_DIGIT_1 3
# elif BOOST_PP_SLOT_TEMP_1 == 4
#    define BOOST_PP_LOCAL_FE_DIGIT_1 4
# elif BOOST_PP_SLOT_TEMP_1 == 5
#    define BOOST_PP_LOCAL_FE_DIGIT_1 5
# elif BOOST_PP_SLOT_TEMP_1 == 6
#    define BOOST_PP_LOCAL_FE_DIGIT_1 6
# elif BOOST_PP_SLOT_TEMP_1 == 7
#    define BOOST_PP_LOCAL_FE_DIGIT_1 7
# elif BOOST_PP_SLOT_TEMP_1 == 8
#    define BOOST_PP_LOCAL_FE_DIGIT_1 8
# elif BOOST_PP_SLOT_TEMP_1 == 9
#    define BOOST_PP_LOCAL_FE_DIGIT_1 9
# endif
#
# if BOOST_PP_LOCAL_FE_DIGIT_3
#    define BOOST_PP_LOCAL_FE() BOOST_PP_SLOT_CC_3(BOOST_PP_LOCAL_FE_DIGIT_3, BOOST_PP_LOCAL_FE_DIGIT_2, BOOST_PP_LOCAL_FE_DIGIT_1)
# elif BOOST_PP_LOCAL_FE_DIGIT_2
#    define BOOST_PP_LOCAL_FE() BOOST_PP_SLOT_CC_2(BOOST_PP_LOCAL_FE_DIGIT_2, BOOST_PP_LOCAL_FE_DIGIT_1)
# else
#    define BOOST_PP_LOCAL_FE() BOOST_PP_LOCAL_FE_DIGIT_1
# endif

/* finish.hpp
cDJco+yKdH1tV+RmGGkErnDzWBgxAWhFfZiuS0zt8YMp1RV367q8DQZ4XpjqeQvfVjE3Z1m0j2A41a6aXDVQH/Nfdmkk53GyTB367ic5qj0AP4l5ekpMd2qpzI4c+YDLjvyURKY1nS5FUMfZKG6i8Tgf+4pQ6yArGflwq4uijjfpOr5I9sIO0e1xWlzfSmX/GwwCy+NykqLlH5iLCfONwAyN3HRe3ULjDIRHEiP7PZydjtibtQDL+7a611RG26jfM7ocXhVoUvmtin3f1CUf5YtlgW8vyB4+26Nt6mO0vb9kT97/NCInIWViqWVWh8J/sGGYOu8Z0i6+FiF5NzIXBuMqGo5DUQoOMZCcRqQ4DVKFcMJCOB91JO/gFOuD+GnH3DiI0wrauOCBUhfBTsD6eaWu7wHJ+0tdX+B7CJAOcxtAZ0A7hDkfMAhwI6A33C4H1AK2URzA94B8QH0Jv/901E37Xd7R5lJdRoy5a+WVUX7buphM6Aqgiup3rYOAbvp960GACqozignzUEAeIBdQZK1ovLJMxprDLat+3CQL7QlRFxbwz/haeKqyHi3VT9iTmJcavY4m8E34p/nnNb3s0AI8hH2WiA8T4tXFsPCjIQ+T7QKxFSfqZOHpwhH2vGQtPAFzvGopYbqZo5VHjGXmNUyZYdYsoURXmJfDSfNrZaV6mr+xXMzu9qLVxbpqMU9lIoDasp0SfnmttQi1Vwc3yvLjIX6tU7by8jOxyfvG2/8uYwBLA3atX1Nv2/nUiSQ4D79wU2F64WOsooNJ0fVlsiffjyjG6hSnMvURnOjZKsybsjMvaeSGVT+tl/UKDWQ+3BvNGDsFR+H0uquIIWoPHLKimfjP1leQu3k94z/Cy732wknWepadSvRviyRZWTKKxpe8HHjAlBTF0jwVo2BIoCLawVCIHGLKhFuHL1Y/PXgiaZ7Gi9jJXlvvAyrrBv5zrN/CHU1KWgpkHrgBW+aLMI/cxqNZttv+6XcJrTNbv2sVvVWVy3RkPbKUuE+QDXKmEK5FhG2ufDJlmC+rov1iWsyTRlieu3bD27xPBeBnzk6dNLx7pTouoo3GM980TbCr7Kk7/K2UYRrgzAWlrv6A4YAqwATAHMBDgEWAFYB1gB2AjwDfAvYB7PNrNnX9g4d4PGMUr+NRXNhzv361TWwHMapl/OahyfHJAeSqz9ZbZ9Q8FWrkXjkIgzNjfD8MTLWwFHxKq3iQBPA88DtizDJRVWojLEE1RWRT+VTanA91tCPKVhmMK7ZMddrMSHtQk6b29k8/k/0FcTJwntXQ17iDJmpdTV9FnfQXe8sTvc15DTVHXQcP6+XNP9J70Q+Ybvt1ulxj/vWO/CsS08aiz+Wk2407Rqw5Os31ptVpcvSxEY4HeeMMMYqwunSfWxTx9H+ChuM7QFapFn8m+41GGWXZjXObobYIugLWYUp7A/APwAHALkCKPjNfP7q3m3JDdGD1YR/pJM1lWlP2SZClT9lZjZAl/1X/eeL/654Pa89+xPAXzelHK3LsVXgFNGSqB+RI/evx/yTxf50/6y4iSNPBUp42L0AHo4UiUJ30RQPTkpykD19K84zqo+5oJ5pcMHGUVDn6Hz6RkTLJ4qfOCsp2Tm0Zb880qe9DPyMR+Ka42nRHh9JfT/zFbjJGV4kgBIGqr7EZTKNgc3zoS8qsUpei0ZjBi2YgTkmP+EICdRumAzPH+FH7UUWk+Jbdre/t6CISSoog0wG1VbwhknfsuuI+6GubKPe0HnlBtVYJdeCAeQ7t2km5eqVaRTsA3JVRQpW1bnUvAlXijuvjvfqOK3ojao96yQXRs6lST69OBsBWmsyNDQirFzCtmL3wWjN9e4Q=
*/