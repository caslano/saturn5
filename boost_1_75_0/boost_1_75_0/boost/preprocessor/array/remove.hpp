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
# ifndef BOOST_PREPROCESSOR_ARRAY_REMOVE_HPP
# define BOOST_PREPROCESSOR_ARRAY_REMOVE_HPP
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/array/elem.hpp>
# include <boost/preprocessor/array/push_back.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/comparison/not_equal.hpp>
# include <boost/preprocessor/control/deduce_d.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/tuple/eat.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_ARRAY_REMOVE */
#
# define BOOST_PP_ARRAY_REMOVE(array, i) BOOST_PP_ARRAY_REMOVE_I(BOOST_PP_DEDUCE_D(), array, i)
# define BOOST_PP_ARRAY_REMOVE_I(d, array, i) BOOST_PP_ARRAY_REMOVE_D(d, array, i)
#
# /* BOOST_PP_ARRAY_REMOVE_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_REMOVE_D(d, array, i) BOOST_PP_TUPLE_ELEM(4, 2, BOOST_PP_WHILE_ ## d(BOOST_PP_ARRAY_REMOVE_P, BOOST_PP_ARRAY_REMOVE_O, (0, i, (0, ()), array)))
# else
#    define BOOST_PP_ARRAY_REMOVE_D(d, array, i) BOOST_PP_ARRAY_REMOVE_D_I(d, array, i)
#    define BOOST_PP_ARRAY_REMOVE_D_I(d, array, i) BOOST_PP_TUPLE_ELEM(4, 2, BOOST_PP_WHILE_ ## d(BOOST_PP_ARRAY_REMOVE_P, BOOST_PP_ARRAY_REMOVE_O, (0, i, (0, ()), array)))
# endif
#
# define BOOST_PP_ARRAY_REMOVE_P(d, st) BOOST_PP_NOT_EQUAL(BOOST_PP_TUPLE_ELEM(4, 0, st), BOOST_PP_ARRAY_SIZE(BOOST_PP_TUPLE_ELEM(4, 3, st)))
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_ARRAY_REMOVE_O(d, st) BOOST_PP_ARRAY_REMOVE_O_I st
# else
#    define BOOST_PP_ARRAY_REMOVE_O(d, st) BOOST_PP_ARRAY_REMOVE_O_I(BOOST_PP_TUPLE_ELEM(4, 0, st), BOOST_PP_TUPLE_ELEM(4, 1, st), BOOST_PP_TUPLE_ELEM(4, 2, st), BOOST_PP_TUPLE_ELEM(4, 3, st))
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_DMC()
#    define BOOST_PP_ARRAY_REMOVE_O_I(n, i, res, arr) (BOOST_PP_INC(n), i, BOOST_PP_IIF(BOOST_PP_NOT_EQUAL(n, i), BOOST_PP_ARRAY_PUSH_BACK, res BOOST_PP_TUPLE_EAT_2)(res, BOOST_PP_ARRAY_ELEM(n, arr)), arr)
# else
#    define BOOST_PP_ARRAY_REMOVE_O_I(n, i, res, arr) (BOOST_PP_INC(n), i, BOOST_PP_IIF(BOOST_PP_NOT_EQUAL(n, i), BOOST_PP_ARRAY_PUSH_BACK, BOOST_PP_TUPLE_ELEM_2_0)(res, BOOST_PP_ARRAY_ELEM(n, arr)), arr)
# endif
#
# endif

/* remove.hpp
QuXqoQ5zVUaJPBQf81L82QXywm0Biyf1O0uumAmCdBNpr4d51JqujkfCof5x+e8TkNDp0ho4NM3rhH1dA3uW6zbuVQ1DbSGjkWJyxE9leicSH7iKZvTF/K0H/Eu8Y33fEg5Q1mYfLBZivdSoNJlVdkXqaeLZ3aKNW4xIHYMPZrryH2gHOXWUT0K9TWZzjckcCDqei+Z2mguXXjv3h3pNzmEZ+xBrX3ncQ3LcpDKVX+2pDqhXpb9MbTcSjUPGOEpfhSej0zbDPextsyiv830tAP+C+6+d79GGNlJJIFq3XvtkRCiYJ6NHJ3kUE9T2BqGCoJ1MM1l5WUYLhmWLI/ptP0ckU88dojvE1ZTRIVFr8tGKwY+9IoIankg0rbW088qfPrpMwzyQXi7HnAoRUcRXGhpiWaVBsLo+YVqQkeRaXPZ+k9mGGkpOr6i7+RrocTlurcQ8N8N8WS0S2cn4DRKY+zzXyZ9eoPq2kxF/3xOmrm+H4198JcE7Vuap0ds8CbFFqs4ZKfyINTNiLKKP3TiXxCoLZrus65HlsTAF+vHNIsWOjmYWVYujRXI+IxRlFUXqvTccU68Udr68PmbZkAoN4XzbVVAczhkAcCTAHw/BEiQECBo43C3BJbi7W5AjuBNCgeDuchDc3S24u7s7xwF3yAHHtX1pO9NpVx52Znd2dmZffvN9H6OoCYFbRYgneDKc+Uxx36sqWZ1XFRR0
*/