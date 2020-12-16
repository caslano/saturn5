# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  *
#  * See http://www.boost.org for most recent version.
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# ifndef BOOST_PREPROCESSOR_LIST_ADT_HPP
# define BOOST_PREPROCESSOR_LIST_ADT_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/detail/is_binary.hpp>
# include <boost/preprocessor/logical/compl.hpp>
# include <boost/preprocessor/tuple/eat.hpp>
#
# /* BOOST_PP_LIST_CONS */
#
# define BOOST_PP_LIST_CONS(head, tail) (head, tail)
#
# /* BOOST_PP_LIST_NIL */
#
# define BOOST_PP_LIST_NIL BOOST_PP_NIL
#
# /* BOOST_PP_LIST_FIRST */
#
# define BOOST_PP_LIST_FIRST(list) BOOST_PP_LIST_FIRST_D(list)
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_LIST_FIRST_D(list) BOOST_PP_LIST_FIRST_I list
# else
#    define BOOST_PP_LIST_FIRST_D(list) BOOST_PP_LIST_FIRST_I ## list
# endif
#
# define BOOST_PP_LIST_FIRST_I(head, tail) head
#
# /* BOOST_PP_LIST_REST */
#
# define BOOST_PP_LIST_REST(list) BOOST_PP_LIST_REST_D(list)
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_LIST_REST_D(list) BOOST_PP_LIST_REST_I list
# else
#    define BOOST_PP_LIST_REST_D(list) BOOST_PP_LIST_REST_I ## list
# endif
#
# define BOOST_PP_LIST_REST_I(head, tail) tail
#
# /* BOOST_PP_LIST_IS_CONS */
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_BCC()
#    define BOOST_PP_LIST_IS_CONS(list) BOOST_PP_LIST_IS_CONS_D(list)
#    define BOOST_PP_LIST_IS_CONS_D(list) BOOST_PP_LIST_IS_CONS_ ## list
#    define BOOST_PP_LIST_IS_CONS_(head, tail) 1
#    define BOOST_PP_LIST_IS_CONS_BOOST_PP_NIL 0
# else
#    define BOOST_PP_LIST_IS_CONS(list) BOOST_PP_IS_BINARY(list)
# endif
#
# /* BOOST_PP_LIST_IS_NIL */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_BCC()
#    define BOOST_PP_LIST_IS_NIL(list) BOOST_PP_COMPL(BOOST_PP_IS_BINARY(list))
# else
#    define BOOST_PP_LIST_IS_NIL(list) BOOST_PP_COMPL(BOOST_PP_LIST_IS_CONS(list))
# endif
#
# endif

/* adt.hpp
TDxpYvsgSu2ewcyyPNFIxF0HGdqJUBxC+CbovTi4lKTDvOlFQ2kCXDzlN1Ndnap51sAWXp/5ise6RzFnaDFhFOYLO8oHyh1HXOVus4yG238v4+zIdaf3erbNrTxJzLVPHP3iDNfuvVwclN5Eb+xNdEDvbUc/mHbRTyx0G1Yh3S1EV27O9ay4dg2325vWJL7D7Il9cpil94O4ryK3Uhtm4zyvIFa1+Zoo7gdXqk8W43YBP0Fdvk994RiT/mHub9TzB0Mfe3yMMtwgwtP7pMCiCVBmll0osm021JtrZLtfzdYZ2cjAZ1+sAp0WtHAbMUTOBFYyb5YPtpBLNTyaLpcdV2GH9tI9UplAzle6wsJXK2U66naID1GtNxyTaetBjZGjCoEs7Du9L69APYgoOuN0tbE7FAd4S5s5e7sOIFK7mqOBV3ejGti6b+26DKGP92qT5Ryl3OhCuYz23q2M6qpHutXIDFbvUZtqDoBWHECVrWUTGxHe+ItWaTul0qj0VrV8hLYx6RAHEWUXybu5zwlIlEaS4+mbPPLaQHYtXofxC/y+Bvce3GK4SrjVcBvhvoPz0/9iVa/ZgMENDx+H9HA2pwOVwjMhrkhOFbjnyJ8O2V97h3i8/QltLo4Q2yI9rAVgRVbzJtVp+kNfpMnZaCxHr4Uv3s+OC7qj/mL/nQ/wRsHZShbwfTX8lMufOfjRrMmASQ2jNgXyZ7phWgZfRhzN/OHS4RREL5CpC+XPIpO/HRypGIasMXDJcMPoEnx4gbw9L3+l3RuabcONRng47e6Kew5wZB7Q1vqekbBWT/erCfJqZfbewepbMdqPOLlCExBR4uFKubB4BgMJj5cDjoTDN9MbAu8W8pauDOE1R7x12ohQXnMs+AjqmG1QE8HquQmRFZdqob4UsmuhHhQar4U6UyheC1kp1EcLmREqXG/m18v+CCF/FPs97I9j/272R7B/C/tD2P81/FPX04UFDi6hpJ+/ZP97MilETfoPB4FBGZzBlVjYXyCtFAyTl6VDmAeGeXJk+Qi5lqgNS5cF7YgWW2FaW6U8re64YD+2rCY+QxLOeN9jJR9eN11CJcoRzTeH21LoOVl+AZULoYipMmIhXxY2I2KMjFhEEfsQgS85k/aW6OsQ3+1k1PHzrLmhfJC6DVFIT5Rv5qX/yfk+kPniKR+WnaQAvgBRbAOfeFi0QCv8aHycZyK1+tdihjLX8zBCpfLGpk0cQKxNnFnOazPPMXlwZbOJQ7yc/H6xjP9RKgQMo2VOGYrr0F7uA+2KEIa2uwptEpWk5jnjmR8NcF8IYXBPIwpZxL1oxF1DMHu2yvadqhGR4WIw0tQP07MY/0SyjCiniHlycy7PJm7/Sl/2xoUgkpattAUdFsVXksMn5IO/0xYOlHZac1qIw4vY8gwqU6eOHjPac4jvEK9+794MZE7xbhFVMq6M4pLFpzI0h0LdfV7c9HY0THVAtAs355NmFfYuk+vUCafo/n0ldVfsXImfoVD/qXVXFe5LkxckMYr8gP99c+Pj8Tai9MVaixfybvqlrtsQzHU9QNgFUkcqZeHpsFeCBknZ1qHM22a8f/6DHJDbI5FlhdhZwQMyXg3Aks8TF0E1tnFdRLtZnSjTMqrrOzREt/5AQqozOUe1D8NG4EXMOHmxGD35AxnocrH+/skOpiXq3onaV5LKZXq4cUMR0HiKZJ2J9Kwo+hFHxt6b6VkcyOIdTfHODJW7Wom1OzTuco4mTV8bYvRPgXPMlznikWMgfRvIBM56U0JDyMMbDLkGILfLBEaX7/zlWo6PVMEPDed3+gALzY20t1OTPUcwdQH017l54Y0saPGFSmBHnHmQRQISOznEUSXgwuk=
*/