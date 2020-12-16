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
YYKrHxvmamRHXM2socmTTTAZ2ccmPevk5skeczMyE+ahdHdPpjPraQ5Jhj07EM+vDV06VCet9zHN9T7gdbpvlO4h1v0oHncz9GBb2AThH7oGlTjrEdIY891wdpadFDoxL11YsNi/+qFMFyrz16E/9H6QtesTLJzg89J56jt52TkZ8vyR/5XymkJeoqT9Ybx/e5O+q0ObdTQYtnYxGHx7JLBBPV7Qj+o9znAIutXfbMhGnk/pvFh/2Ne87A+o7MKsaCqaX8/801r26EDKmyX3Xj7vKe/R+H1D3gRruq2PHvtcLOeSuY0wj7XWz2I39b6Gzm7zWAfzLBbH+Tr8T1FmuXcHoYSdFSoEX0OZcNq4RbfS9Lg+yqM+K/E4KEz26sleqbOaTUCfEtuQgjb8Sm1wGXYObZDXObFgkzchJz0vmwXzMasjfn4fetIU0uYWztGnIC/PueMgZ7XvJzS2H+6TxV6JimvjH9CmZ7beZuvXqI/udW0Jiz6OM1SYmEeaBz/EHJTFCrCSelw41Ptin11seZofn0epD4syRn98Rfiq8IBuJl/nzSBe5fng5u/WuSIz0DZO5LTLlKawRS4lUto+2EHa86G8D+P3sO8TTwuHDsMcMqZ3WyGmz0B327XjGKrbIIOXsBq1a4Vvybdkn+B+mPJKffl0/eHsnXpDQy6xRfV9WIMqc8Ov3m19dguedR/QPeVntc8g8F5B5boPuwC+pXUOjTUZWnegc80oXOc1kPpOy1coLqY1uwB/871bnGw5i/VvFeDyTttZ0Id80vX7QCENHsHdcF3RkddtHdl89NCF2CPaXohlS7BK8LzQsmV46zLhg0gPl5jYMuHbuC26lxKN7O1EV/ZR4jf13hs8RBDrHiWeMyj/6aGreV+JrMufofD7Kavdv0tzrXTtUURAazDAsJ8hgyv8SOahG6EzsCJdOAvj589QShtt0KHFbcH8D8I9rImuQuhJV/e4dpHOW0Umce61V8aG36qW0YCXsY7SYquUUVn/Bx6NWS+TUr9y3aZAJ/IbLu1nHkTHT+qNeA+7G+uir6wrAXPedg95TuC+kHKyxElFuo/ZT2Mpm5nQimZ4VzuT4tVzfR3dDfRDf31fYY7BcNvzPa+T/E5gUd4DOemZUjtfpDr5Stz50nFH9Jpt7Dh2dV1mLbDG1MyOngx+PYNlMcrnbT23qfQcgv4PaX+46roE4+den2W4Flmn0D8mLyc/m9Qr1y4HGUV93+NMeUp6ZjOYyjCyCKz5H8Z6xug+WNwRnx0ssriYPOLc9O1cXDwMeo+A+ng8sesa1v9NdZXPEj5GsEjrBuJy6oSJTLHv4sAxsZ5zpXvmwGvy84qmvMx9fWzPGTxcFr5pNpkjzK3NESjXxQP/GHP4vIHfI62iciJIbzTXG5rGn7cszK36vEUXgAbtfrW2z1vuVdQ/mJeTi3ICqJxQPG+JsPu8JRxy2QjW5y0LR4k6xBDG9ZxJ49wv3qDiXuZgWjV8p/6ter6b95X5XjzCOb6bUzkRlfSOFvVS37mhxbdSbyX+tiFfAOUrdchfNn3HwMbfou/U/OX34/w9fm9l/gJrzt9nr4vtKmH3c/6uUjvHtPoJcStwLvibrpytMOA+FHNImWsJ6+ZWws67l7AcjxL2k2cJm1OnhPn5lLDNlhIW61vCjvuVsMEBJeyzQKQFxbPjweV46FXCVtavEM41LBMWN1rtruTwWD/ZNo9d5baJrJ1tDlIbIivZ5ibXq39sca1sk9wftqF8SbDNPXZtwyCXhGC1zWOPqG3DBnDbLPVw2jYvnRTb9TTmfBxL9ycrIn5i5eyYroQNgl2uGEvYZNjFALssh13CYZe9sEsy7HLOu4Q=
*/