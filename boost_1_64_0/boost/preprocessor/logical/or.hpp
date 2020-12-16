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
# ifndef BOOST_PREPROCESSOR_LOGICAL_OR_HPP
# define BOOST_PREPROCESSOR_LOGICAL_OR_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/logical/bool.hpp>
# include <boost/preprocessor/logical/bitor.hpp>
#
# /* BOOST_PP_OR */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_OR(p, q) BOOST_PP_BITOR(BOOST_PP_BOOL(p), BOOST_PP_BOOL(q))
# else
#    define BOOST_PP_OR(p, q) BOOST_PP_OR_I(p, q)
#    define BOOST_PP_OR_I(p, q) BOOST_PP_BITOR(BOOST_PP_BOOL(p), BOOST_PP_BOOL(q))
# endif
#
# endif

/* or.hpp
2QOsbGhdJpNXW2iD6M1sfC9LdXDhGxDKQZZFZpQA3ysPqsGnqgsZQ/YT49S5ZV/HnVb7MSeK2vxzwgdBGceGGcTiVCFaFbaDHJC2UqUhMGOq03Ka3nqz+eDCiIZn0/oV5YWRwSEy7RKvuA/X3YcHr6i7j7Q7sCgrOVKaVA/DHHykMUCvU1+41+4CO3l2kFj3xX0hwSTfXmi1zHQ1i5Zee0/Xp+6+OB3Gb6eZjn2moulkNJ0eNO2Mph1prK/s38Yzd8osd8/P6XS0zs++6iGn43Jcj8Qx2Pz6nJ+HqXNLRGo40XOuF9rJLjF+nxhc8f1IrjxBe1CqaDOty8Nqy2sRP3hP17JpMGwYOKKRcTL2E7pne5NJCu+6i3ocTPh0PKnJGJ/r3aZ41BZEB+ZRhXR9XEoG36iapfd4lpBm5R8doh7oDcJLsu762rdr7oLSrpbRxvOrRMrdx1Pu4agWzTNBnWZwVn2hlKZTarhpqUQdoLk6HJerYsHT4m1fuv4yUJQ03/OyR/Y0seelzeDiKXZZcB95fVcX5ffTpObp8buUB2aHGOCyQKvPsstekEoyVeu6f1td0/Zyv4mkrxp+s0k91PBexnZvTuQedOSer2t47LNyikILqhCgt80hHfjFPI3KevGs0L4oV4TmwrcYSu96MtxPT7UdcS1+AAk0VZk6I6Z2NeDydI5qVbRiprs2Fh4kh67u+Zl/O2SokfIQcM+E+cWtXu6ZzP52y4VXhdzvDnQP8uLkUf4+0u8rfx9JtAXudbfWORHcYporTZ6p2WlIUpre2j2tk3iPTvVixeL3E/SDx7jdHTmHqYnRM+a4/fq94jeNdG1rbY9YizzPVSVqgfXW12xMTdPYzK90Lud0XRrQR+0tWs8OxcN4VmXcd86ZfU2hVpxczLHyfIJswjwG+pS5iCZH3V8Im283Xj72cPtLf6upfSxc9jnKADrG25kSpiI8tfXQtvvTdNi+aybVFQ7qtNvUjmnQMHE6qE6VhIkr+nfDRcrmjspRNroC9BLK0S9/WQyNHnpeSXEju/cdm5/WSY5k/xpvit1dR4+VRRNWkHWVGuKYqFlNnJt8QJBjZa3n+utdMETn3FR3/UJPSWhfL1BfIrwQ9wOJfhmfUaOnvjleN8xckSov0+36YV0D6rHaKjVXpcSt5KX3VdzxUDc65zKiFitlXjHshUY0OJioVg95WErN7eVVZsiiefs+t2AYqpZ2nZyoHtayxFe3mNPE/VdBCP9HtHvYQJ+s6w0RNIWSTs1QpuItnQx62J3I9YLLGTXOPfQdKl/+cVWNzVVtAo3YiWEbKGlLJrNuwt3bq8ltoloacq4OmlVAx/wtdW0b7mOItVXQj6k4q6yrOjw8WUnGoSe89dVOlZfbTU8+6Ha2yaykZTcpwG64b+n3lXxNVbvWQc/I+HpxvReKx+YsCoIcW5V5DekInLetuhEnIdBZKjFASegpQu8iREt4Pt5PuXzrfi1Mow/LjUUvy3S2saWU3yNXXVf9mp4dO58LLWxpB0rENvy+pd1FhKmR6RsWJfrj6XSWu+NHQyBhGZnnKaG+nzpU6YdOW5rfAKSO0zBIalB0hqf9afSYXeMLtbmIzJaE7d/6PiC/vXqM1a5GKvxHi9eC0si97WY5YwYgjC25a7nH/P5cEpadXfp4txKpfFCD6v7qqNfvqiFvvnKl3WyuOvXJRNZ0JQ06Bqf9JNLnutszwx/3tz5yMrlxDDridS4XdaapSDuduIdOwqwge7unRXDwnpiAmHUpZ5hoKjMjqd/dEDsBanIzCV/7qLaBONrW6pm8m3PXZVgTE9D6ewh1zjbGDm68g3QfY41AFWkQtI2p+DfFAo/jRrs=
*/