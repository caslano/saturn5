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
# ifndef BOOST_PREPROCESSOR_ARRAY_INSERT_HPP
# define BOOST_PREPROCESSOR_ARRAY_INSERT_HPP
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/array/elem.hpp>
# include <boost/preprocessor/array/push_back.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/comparison/not_equal.hpp>
# include <boost/preprocessor/control/deduce_d.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_ARRAY_INSERT */
#
# define BOOST_PP_ARRAY_INSERT(array, i, elem) BOOST_PP_ARRAY_INSERT_I(BOOST_PP_DEDUCE_D(), array, i, elem)
# define BOOST_PP_ARRAY_INSERT_I(d, array, i, elem) BOOST_PP_ARRAY_INSERT_D(d, array, i, elem)
#
# /* BOOST_PP_ARRAY_INSERT_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_INSERT_D(d, array, i, elem) BOOST_PP_TUPLE_ELEM(5, 3, BOOST_PP_WHILE_ ## d(BOOST_PP_ARRAY_INSERT_P, BOOST_PP_ARRAY_INSERT_O, (0, i, elem, (0, ()), array)))
# else
#    define BOOST_PP_ARRAY_INSERT_D(d, array, i, elem) BOOST_PP_ARRAY_INSERT_D_I(d, array, i, elem)
#    define BOOST_PP_ARRAY_INSERT_D_I(d, array, i, elem) BOOST_PP_TUPLE_ELEM(5, 3, BOOST_PP_WHILE_ ## d(BOOST_PP_ARRAY_INSERT_P, BOOST_PP_ARRAY_INSERT_O, (0, i, elem, (0, ()), array)))
# endif
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_ARRAY_INSERT_P(d, state) BOOST_PP_ARRAY_INSERT_P_I state
# else
#    define BOOST_PP_ARRAY_INSERT_P(d, state) BOOST_PP_ARRAY_INSERT_P_I(nil, nil, nil, BOOST_PP_TUPLE_ELEM(5, 3, state), BOOST_PP_TUPLE_ELEM(5, 4, state))
# endif
#
# define BOOST_PP_ARRAY_INSERT_P_I(_i, _ii, _iii, res, arr) BOOST_PP_NOT_EQUAL(BOOST_PP_ARRAY_SIZE(res), BOOST_PP_INC(BOOST_PP_ARRAY_SIZE(arr)))
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_ARRAY_INSERT_O(d, state) BOOST_PP_ARRAY_INSERT_O_I state
# else
#    define BOOST_PP_ARRAY_INSERT_O(d, state) BOOST_PP_ARRAY_INSERT_O_I(BOOST_PP_TUPLE_ELEM(5, 0, state), BOOST_PP_TUPLE_ELEM(5, 1, state), BOOST_PP_TUPLE_ELEM(5, 2, state), BOOST_PP_TUPLE_ELEM(5, 3, state), BOOST_PP_TUPLE_ELEM(5, 4, state))
# endif
#
# define BOOST_PP_ARRAY_INSERT_O_I(n, i, elem, res, arr) (BOOST_PP_IIF(BOOST_PP_NOT_EQUAL(BOOST_PP_ARRAY_SIZE(res), i), BOOST_PP_INC(n), n), i, elem, BOOST_PP_ARRAY_PUSH_BACK(res, BOOST_PP_IIF(BOOST_PP_NOT_EQUAL(BOOST_PP_ARRAY_SIZE(res), i), BOOST_PP_ARRAY_ELEM(n, arr), elem)), arr)
#
# endif

/* insert.hpp
dgFZu6A4myxOMq3U/ZXEtdkHhc0+wGxW4X4Fm30IZb4eNvgAs8EK0vuvKRwkobKjB5itqfzPIBv6DbOh0P8o/0+VWhtrGd+1NUsu1IGNtaZaaR4j68FKCda9RZleZpg6XBphbG6WExcIF17mxLfElSt3gRoWJpieumGwOhafIxWumeHAzOJ2Wzk5BmPrEoMDR46bEd+YTA3Ekgxlx+Qh4GhiO8ZkdMri0AjjE/Zk61GPO8QpwOPUIzsCqXHN8Y62zi2poXzSp7PS3c5uKo3U+K6xVJ7pP7TbUeWiBidD8WE/nMpm6zj1Zi0fwENOPEKzX8ifBy8jH0Hn3sfj/bERGYfKpy+XyQ/mXISFUxl1pmi6TtJT+fRkUmRsuV0T0tlN6SuPJ+NQ2fRjA66Jw3FcKR68NN6RTMZHjAQWHoq3qFtIRjOpcVKY4Pfim16jbZtUDX4XkE88FD7x4SJ9Yp6iMneow9YfItCs/k6zBp6z374QiXE3sB/p6/088H/G56nwH+DzrkZbvBY+73cEN3lXPu8RCgtJ9rE9+/pyjHPg7x6dtr97afK4Ge1oiRNLxzK5MTJH+LMsnR1Pxr12czgTN/bmjMfzuUwsaeehBlLq/YAdZDszYTuPB9lOblTNmxNfKyODGYNhgGb7e9J+3EBxdsKYcaUVl4ayhT+JtvCPrC1UuCdgF0+iLAUusP/2Z/Tf9tHfDbAjxZerRfXXnuIwYU9Eb+1J6SJE9vQ0t6eXWBdszEE9towD+0kmUzvjQ8ZPU3hnbBfd3+Efc/w1yC5iIyMZcl36lPrk3SpG+ZL07QU/popiU0Lf/llhG88w21C4v8E2/m5sg+MK2MZzsI1/MNtQfEkXth//PIW5qLIf/wzrW50O2/gnt43/kE52FDfOpN098QTZUDEjTUM7abmPF1fukiPPZfGpoeydWv87zy9SfutZGSt8CX2zS2nfYK0CWDsh2iC6EicEOoGDnQAHO5lBcPV3Jv7Oor+nwl5e9NkL3ZNKOJlB3hd/UYz76rWNJGO71AtdQ/F0fHyIIrt6nkW2VFbL9jL8B/V8sm2nhvRcJvrcZ8XtGwlqxjkxiDDJnB+n2YbBxHCC+aTI9oil74v0butoVeFhNf8CWz2oNsBaxqjHNZVnAs1ktnlqcbZpOHFdTc0dtlgOW9xA9nWIQ/ZSi3tc2J6Besf+lnD6LMzanuI5R9veIc7Bwn6JfwBdiRMGncAF2u8hsNsK/K2kvwMl2n6Jv99+51IYyuB2S3STrOUjXGbPSfJzmvl8Ysi7ZyXsJAcpbG1/nqMOIWZSSRan2lE9K/d2HX42sZbBzdFFE6eO4ciCLXyZhuP+MfBZoWGGw1NWlqOc0cTQkD4bYmFH03q74jqYiw+x86eEG8xnc6kxDmskWrxoohWj7HEu1eF5rA6veQntca/tJ7T00ow5rSZ6a8wlCkZrrxpo6yfB+mhBWS1hE9StxwTrjWzp7o/g3J2DsTPBt2ztpK1L9t2XsIJ1dffR5Qj23eE6F9av+Xb39pt3UJp1+t2txyOd3Src2UIrBT3OKrbGOV/ZX2yEkPp9YVR5D6Dq9Qbfmo4aGHtrYSEdbrDhWTp8jGPmzMt0uNFZjj221bW+daWNWzvatML1L0psWO/LOr900vWKtWu9rUtUI47OYz+TADYXiO6uef9/rlMpn1FDOpR5RVqE2781rNlOuHRR7b+/hnUJ8aLyK27daWI5SkgWr9EIYPM0iprW9H32267PKCs9Lp6gx6zVI+HoX1bZI4WqZx1K4VDx+Zi2PZLedH9yZaXR2bTS+4/ozewxdEU6M5/KOey96Ux8jGhWYs/nEn8/KTmU2BF1NxHhN3E0/OZyfgg=
*/