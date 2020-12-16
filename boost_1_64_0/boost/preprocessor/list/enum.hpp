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
# ifndef BOOST_PREPROCESSOR_LIST_ENUM_HPP
# define BOOST_PREPROCESSOR_LIST_ENUM_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/list/for_each_i.hpp>
# include <boost/preprocessor/punctuation/comma_if.hpp>
#
# /* BOOST_PP_LIST_ENUM */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_ENUM(list) BOOST_PP_LIST_FOR_EACH_I(BOOST_PP_LIST_ENUM_O, BOOST_PP_NIL, list)
# else
#    define BOOST_PP_LIST_ENUM(list) BOOST_PP_LIST_ENUM_I(list)
#    define BOOST_PP_LIST_ENUM_I(list) BOOST_PP_LIST_FOR_EACH_I(BOOST_PP_LIST_ENUM_O, BOOST_PP_NIL, list)
# endif
#
# define BOOST_PP_LIST_ENUM_O(r, _, i, elem) BOOST_PP_COMMA_IF(i) elem
#
# /* BOOST_PP_LIST_ENUM_R */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_ENUM_R(r, list) BOOST_PP_LIST_FOR_EACH_I_R(r, BOOST_PP_LIST_ENUM_O, BOOST_PP_NIL, list)
# else
#    define BOOST_PP_LIST_ENUM_R(r, list) BOOST_PP_LIST_ENUM_R_I(r, list)
#    define BOOST_PP_LIST_ENUM_R_I(r, list) BOOST_PP_LIST_FOR_EACH_I_R(r, BOOST_PP_LIST_ENUM_O, BOOST_PP_NIL, list)
# endif
#
# endif

/* enum.hpp
Y7Lh7aVVfjVVnnxeIN9gTQizHUxnQTmig3xHTlbHUbkUBdS0UcP5HeTvDPzyRT+JzphfCZ1bjwSiEzVKdM4yMTpTzwu2VB/YyiVs+3xgWxgAW6UK22b8ertLwN7pTWYO++qA3aECVi4BU3XTSDxNpHtnTrot7MxwOETsV5qRhF6A5Fpl1B5D/38hJ3k23gGRfx0plijpRurghVIULbyDNLHcq9h8IJYMD9XQiK0UISdtyDnEtpuhbuAWMKxBo5e4jbfaopPqcI8v1vpMGeHWFYX1GcIx46PES9UYrIYcJ3m5pTdpVaIi5UZ6WNqNioxgSTPxBCJKhljczULToZE+pBZ2WsmnbKA8JjPVc0pkUaldesxT9F+kUcmnLPDehANXdZKRD3hmjK9TDbAnivWTNC3loYAtw1pMum595/DAZS2uZH35wpPtnS1XF82Qgpufu+yS/1+dnlIu6AKGx2MpV/zY0fh6DXY0vm2DI40vXzKnPx83zEWB3AMLjif09U9p5Av0M7DvnEjqTekQszV9FTTf/uqSf4AmBH15uHdd3LczBj82rmUwQ8qHmuZaLM1LsDAeX3pbbAnGOkN/ErvSJ2keoYXdlsXJKXTUsLjyB+aVoaVwpAs6pEoq8fGgeaAX5sukV3kmPH8DrzlRa9rUqkT1SVpqpD/azX9dbT0erfcodaXSHgi2ft6CKXHig0le/DYTTx2ioKV0CZWnV5f38HG5QksvcSsalgfz8RRMRVAe1idS8CoEWUFC7jDGA2rRDXGs1KBUUlwyxbVBHCsiyJ23oRR3upKngwpGKZtP8TOIxhv+SEm3IEVWkkspB9QC8i1M/qIo+hsZnWtGtKyiHVrj7R0ZvAhB9uVEyUOL7Siht8hVhpiQiNvE3HY6YpzNZCpH7640su4zyaw7K9VtIZr8L+XF/4AxCOFjEMTLRW4zzY/fpI1njd7yDMnYXMAOERvhH9F3iMlnZ+HM+wE7RS8saPpO0aGrG9wpGjLkdF2WUr5kIK9Td+/Ae1naZop7B7ZTuiMda1VjOyXK2ULfTtnus5UiN1Ci3APQaVpKw1/4N9Qjb7ta20pwrzRpvcc2i7q1wpssOhbsGhr+fI83WNarGyyEY3kSl8ZIRZJlOWGT91iifPZXIk/3un2ISo7C2mbWGcVn2MT/ofasAfqkTphg9BjlT49H3gugR9j7TafHiKsapMeSdKKHyaBHuxo/eryY/n/SY3miRo+/K4PTY1QAPR58t8n0GFUvPWokPQqC0QMtSHqMBiREHF+i/PBOAFHGvNt0oqzu0SBRLhnERPlcJ0rBET+imAcFEiVwz7ERhInvoRHmvi+DE2Z0AGE2zvcjTCNpUgaaMDWmSWocl9T4i7ddaCIyuX/p8niExGSYxJMDz8orWbXyVSz6bBCmiagZNk1ykD4I85epq+XGBAae9ecmqFIPQSPmBxD09flNJ+iJKxokqO1GImjaUp2gHx3yI2ivGy8AQe1XaAR9dnlwgioBBD39VlMIWulLUBr4tYuLGPwvl6Tk8b8GJPuYd94spV/ykH/E7PLKsQx8UCv54Gnjq9TnK8HImVsPOfu+FUDOzW81nZyXJzRIzqk3EDkrv9DJue+/fuS894YLQM6iyzVyrvwiODlzA8h59bymkLPG//ukTQJj9JKly4LQY1E99Hj3zQB6pM1rOj1e6t4gPY4OIHr0WqbTw+bxo8eWAReAHse7afTo/XlweiwKoMdrb0irGZIelf70iNTogTaIWjo9bHf60yO98fSoqIceHd8IoMfCN5pOj/BuDdLj3lSe5Bn0qPzVjx43pl4AeoyO1+jxRkVwelQE0KP13KbQoyCAHhmNp8eyeuhRUh4=
*/