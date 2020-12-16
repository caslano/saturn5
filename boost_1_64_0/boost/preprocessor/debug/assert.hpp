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
# ifndef BOOST_PREPROCESSOR_DEBUG_ASSERT_HPP
# define BOOST_PREPROCESSOR_DEBUG_ASSERT_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/logical/not.hpp>
# include <boost/preprocessor/tuple/eat.hpp>
#
# /* BOOST_PP_ASSERT */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ASSERT BOOST_PP_ASSERT_D
# else
#    define BOOST_PP_ASSERT(cond) BOOST_PP_ASSERT_D(cond)
# endif
#
# define BOOST_PP_ASSERT_D(cond) BOOST_PP_IIF(BOOST_PP_NOT(cond), BOOST_PP_ASSERT_ERROR, BOOST_PP_TUPLE_EAT_1)(...)
# define BOOST_PP_ASSERT_ERROR(x, y, z)
#
# /* BOOST_PP_ASSERT_MSG */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ASSERT_MSG BOOST_PP_ASSERT_MSG_D
# else
#    define BOOST_PP_ASSERT_MSG(cond, msg) BOOST_PP_ASSERT_MSG_D(cond, msg)
# endif
#
# define BOOST_PP_ASSERT_MSG_D(cond, msg) BOOST_PP_EXPR_IIF(BOOST_PP_NOT(cond), msg)
#
# endif

/* assert.hpp
FatsxjjA+HvQQjFNpkdpTyt+DDkoz8PNOfwPm5zDf+Et5X4A+Mm4Bc+/TJv54XPaeMB3Kt2m38qOhB2Rl9f2qt8Z4vtGtacnhpLpGyGu2tNjQr3WXmujjUy0s8fk2om4fPxB5A4oGZ02fVJKFbe5C23U76evTZroDA8CtovWzrRNnEb21LY4mFSBpPu/B0WrJD6MHnaKzfF6UxqX8RWor6nK+2afyxSTbINt3U4+5uMGc7zUWUS9gwZxE6JVoDThg68PfzhrHn06uQo1VWlB2sHTwpQnBsXpn7AIbY4sk1fdC0UPRWourat6kuWYP2dB1tYcOpqZYzVpuxaHNdoWb54BYrqss7J/gWxi9TKyIvrFCw7DtD04IDYgom6yYL8O2GgGAGPnxEIk0gqH/cKgeOrXEpSq0i1Tn/nYYD2CuoWyyqZbGv67jwdphozFT4QtIujtSnJHjc47K9dZ3rhnWp1efTaO2fgryN/dLE+uUmL88dB23f+OPaDoH7aJrGONG8rVO9KBXUVeh3z1shnT3GoSxyNln3xdjNeD8nUB9m7S/QZbgLGA7pJNPiKzC5B5VGZOQ2Yi76SRXq6bisi0DGinjUGyAEKapX7hqcTQlY0PADfWQDXZJt3otvGguPoangah3NmluF+31RTS5gSewJRxRC+nf1COb9j1sxMDXK7F6Wp24oRtpAOT9rzG4pgrPo2Tn5b7SxwJ0ezjPr6ElWU3Z73Lpvv74h8pGGVne4bItcv7lKMZzA3hm7+P/83FoqAYaKejjcNSbGDfscqRFu6J29xy4iPaP5xYp2WFEvGlVfoiMt7DfZDcL9wDKf1pAMVGHbgri50UTrAF9jafaIhJJ0yuhh/y11yRMpT+RaLE0ERtPM6KxVWy+rqu5PCQCcWOEP5RTKvPuZ/IaXaGzoK7+ocTqPbQa3VEH6qoFzZaGpom9cS0KT5xcZz5jy2cJAf5Fz6N0y8+hLNiTeSvn5GY76errs1WjTv19EakoxoPV+MildIvNCk7OvuzeW4jMONGsmK4/Tp525lOpz4lKEyHMfjHJw+j8qIA8SsyC8QaoNfNT9iAGPLUB00JGRE6yEujL7Tf8onlNMMXyD2yaroNgsU/CC/yIpvdOGa6/Z+MXQ18VMURv0su4YBIDgh4QoQoUQNEjSZqwCBHCSHV1B4edwc2VlpRn2laUe8wSopgiBCOaFpRUFGpgqKiIkUNiBC+UVBQEKmgYkW754miIAZBrv+Z2ffeYWt/vd9v7+3OzH68/ZidnZ3dd0pDErvLE6g3H0hkgfGfq9tUxSa6Y8fQT8esqE0MhxKK15v/rzVQNJs4YwaJf9/JDeV1lMjGlv9rP82Mf5bE5zmkNUFzyP8/f6xEXErjSTzx3pa9PW3xEI8PqSEOqxqyZ/Rzcl2eD1gQfX4oniGqMnURfH74xsSOYdIo8yuDB6EXZfw7RfyaEkUtQSNwGs0jMi4PJdPM5SSrk5EScuZVPiI1TUT/om0VaunhIW7eZ46mmeviAt6+g10MKZe6OfXN3uXHaFp5BbmnTIaRvvHvJP0cLK6NaQm7/yM9Xok1vJ3kbSQX4pOqJaB++AE+dCukcuk6ulI7DoDsL90XdNMC8yMBxH+FUEhdjTx5ACSebEBaw2nyXF725XDiVen0cRH0UzLVaSVYIj3mc4/yA5ZLJar80irRM+1pLNbchPnMLLBCgeOXpwDaCDDIAriN2UiAp0B0bqOUsL0Ji7fXeny6hdxos7P5BWfjtjhKJslMiRuDatKPUnUuAjQeOHnfK0tixbei7iEMFAWVF29tfjqofziochAOU9/oCk9IjUBqQvj1j0KY15i84310heqwerBdj1XYSFQ=
*/