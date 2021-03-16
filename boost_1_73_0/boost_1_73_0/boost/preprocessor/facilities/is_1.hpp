# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2003.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_FACILITIES_IS_1_HPP
# define BOOST_PREPROCESSOR_FACILITIES_IS_1_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/facilities/is_empty.hpp>
#
# /* BOOST_PP_IS_1 */
#
# define BOOST_PP_IS_1(x) BOOST_PP_IS_EMPTY(BOOST_PP_CAT(BOOST_PP_IS_1_HELPER_, x))
# define BOOST_PP_IS_1_HELPER_1
#
# endif

/* is_1.hpp
JnrQLz8bb8EqZbxi7P2WsWN/BxP1mQ+BNvQ+Y9D86ha+W808apCB244amMcYNW4b+0esqk/5rVeaSGQsq828KP6sieSBFrYmAosZl06yr0dYbh7zgGO9Gdv/a2IrZb65gXZLfB/JPHvqNQaa9zWxh7lO/VHEf/r89U0Zt/vQx1Loh+xnDer/BDHpSY7JghILfYgdh+kbXfYayBZ31z1rYvJHJg5SN5/QzzdRP1M4j13LcaxwmrGPse6/jHHbFtI=
*/