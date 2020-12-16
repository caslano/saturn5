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
# ifndef BOOST_PREPROCESSOR_ARRAY_REPLACE_HPP
# define BOOST_PREPROCESSOR_ARRAY_REPLACE_HPP
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/array/elem.hpp>
# include <boost/preprocessor/array/push_back.hpp>
# include <boost/preprocessor/comparison/not_equal.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/deduce_d.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_ARRAY_REPLACE */
#
# define BOOST_PP_ARRAY_REPLACE(array, i, elem) BOOST_PP_ARRAY_REPLACE_I(BOOST_PP_DEDUCE_D(), array, i, elem)
# define BOOST_PP_ARRAY_REPLACE_I(d, array, i, elem) BOOST_PP_ARRAY_REPLACE_D(d, array, i, elem)
#
# /* BOOST_PP_ARRAY_REPLACE_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_REPLACE_D(d, array, i, elem) BOOST_PP_TUPLE_ELEM(5, 3, BOOST_PP_WHILE_ ## d(BOOST_PP_ARRAY_REPLACE_P, BOOST_PP_ARRAY_REPLACE_O, (0, i, elem, (0, ()), array)))
# else
#    define BOOST_PP_ARRAY_REPLACE_D(d, array, i, elem) BOOST_PP_ARRAY_REPLACE_D_I(d, array, i, elem)
#    define BOOST_PP_ARRAY_REPLACE_D_I(d, array, i, elem) BOOST_PP_TUPLE_ELEM(5, 3, BOOST_PP_WHILE_ ## d(BOOST_PP_ARRAY_REPLACE_P, BOOST_PP_ARRAY_REPLACE_O, (0, i, elem, (0, ()), array)))
# endif
#
# define BOOST_PP_ARRAY_REPLACE_P(d, state) BOOST_PP_NOT_EQUAL(BOOST_PP_TUPLE_ELEM(5, 0, state), BOOST_PP_ARRAY_SIZE(BOOST_PP_TUPLE_ELEM(5, 4, state)))
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_ARRAY_REPLACE_O(d, state) BOOST_PP_ARRAY_REPLACE_O_I state
# else
#    define BOOST_PP_ARRAY_REPLACE_O(d, state) BOOST_PP_ARRAY_REPLACE_O_I(BOOST_PP_TUPLE_ELEM(5, 0, state), BOOST_PP_TUPLE_ELEM(5, 1, state), BOOST_PP_TUPLE_ELEM(5, 2, state), BOOST_PP_TUPLE_ELEM(5, 3, state), BOOST_PP_TUPLE_ELEM(5, 4, state))
# endif
#
# define BOOST_PP_ARRAY_REPLACE_O_I(n, i, elem, res, arr) (BOOST_PP_INC(n), i, elem, BOOST_PP_ARRAY_PUSH_BACK(res, BOOST_PP_IIF(BOOST_PP_NOT_EQUAL(n, i), BOOST_PP_ARRAY_ELEM(n, arr), elem)), arr)
#
# endif

/* replace.hpp
q8nMq+DtEMp/qcumiewFkGqTi3rrcjF6NnQKc3+DmaMfrMmp43Q5y87fGeS1eYfwXGRvDeM8HFmL53ecyyaXIcPGng89ZnAu66maDHqC9+C3iSxM4t3kGzRpfbNNVvPMn5CdVc1EVvfS5cFRNrl6rcjDtMH2mi7DrtVlP/K2aCtrKGjD4QTmQfqL1PD8sefZZPMBzkw/k3O48mxS8RXjgdyUTqL9jNWmEE5IpL4xZbQtXZfGPzO2DzEmhbyJ1BVe/1mXt+63SYe3dGldwJryJ9GBFZyJcQ9jhu7r13G+1unoUCIiXKrJnYzFE6fbJA9Z+LyE9ajYmdQVNrn/Al1a3GKT/HLkxanLzW/a5LlP6NcCztKfZZPOOTaZ94wm6xuzv+KHuvRZxx4oX7DvVivasUqXM7/XpfB6xu9zmzx7H3t3LGMfBGhhyPvQ19Er+Hz5ubzv8prIYto74Q3Wjn5O/ux2TeyMxfivyNO9hR3paJMBq1l7j934AT5c9DPvsj2vy47Ldbm3GeN2JbxYjqztJs9+ii5PfSryKzawoAlzqc8ju4Idw55s/NAmzRLo55XoKXI3J5l3wn/Q5RfsT8357Cn2oy7L823y9HzerUQH7Tx/2l0i4x8RKcHe3DPbJh1p+0cedOhpTRbeqsunpYzvw7Sxmnz22ejSQZvsZh76LezqpJ/QhxdF7NjJX37TZeky1ueyottDH6+jzX3CkUn4c87tyAu8OfcjTfrP12QpbXa/pclbP2Db8AvVj+ji2MR+N2xfEIud243cZMKr6GmMyyW6vPAr/OX34jBN/hSF/cdmLgjFzl7K3hHI1J/78C7ua8hSJ136Yiv3IbPJ2N/Q7/BB0CLHs08Az5rX0yYzn8NmMZaDHexdg8/RkNWf0c8qZLE4zCY//kC76etbMcjBHnR3I3p5qUhxpSYty/iNPR26mrov0+X0ezS58E+6XEHbNjfHJhch208Yp1Xhn1J16fEMvgW5f61Ck3WjdblyGzZc8IFfMz6L8WWHWHvzgE2iseWF2Ta5BbtcPI9nQg+5VpPltHP8+SLjIhjHiTbZ9g68maLLOzOQ/zM0+eUqTeakIvtluiyYhGyfp0nvIzzjK5t8lycS+5ZINe1xD7fJXyvQZ2bBT0Gvpn7GeHxvk7ALWUPQkTn58ZxN8By+HV1rO1xk+G5NrmY83+Q5XT6HV/ipFA/+PZp1aI9qci46GpaKjqzAZg7CR8OrL98mx/wj76j1QAb4fRL29ZPHbNLiTU2qz2etQZFNXj0T34rf+AZ+rcMeXTaMOYBP0WHavWGaJr+Nxp69hIwy/o9Q1y1v852IvYrEP92MPKZgU64W9FaTZ+7QxHMpuo2vPpVxDF+ryZLBurTC5rlWiXyF391Av9a4danYrsl2fMKIC+HtlZr8egjZqbDJg9iosauQsUttEtcGvWSc3puOvjyAfqDT7ySBA75hrEvwgUNE3pysy4qPkb1X4Cn6c+Vf2JPycU2e2gpPW/Kcd7Dfd+py+27sHfjkGuRq8d+QyS/hbxddTmuOD7Sh9+k2ee1j/MNPmsyl7FDKaNvg85+xz9jS29I1Gf6zLmWLkO8w7OHD5NjjsflrGSMH2GGjTU7qqcmQ+fhn7GJPfO+0/jZZjrw/gMwsmWOT36rx18w7OMo1mf2ySJd3bXLaWtraFVnJwG4s0+T8u7CzZ2oyBr+c/GcmRo6w5mEesvOULtnYt81TNNn2oCZvfKfJyxdQH3b4yf5gjPOwP+Cz2c10OQAmjF2BLDJ2a7k37Xts7aW6bL+HsaSvU9G3MGyEG7+1JxNMxDjej/1KukWXhcN0uZXfb/UUad/BBu/Ajk9gD1aB15C5/Yfw7fg=
*/