# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2014.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
#ifndef BOOST_PREPROCESSOR_REMOVE_PARENS_HPP
#define BOOST_PREPROCESSOR_REMOVE_PARENS_HPP

#include <boost/preprocessor/config/config.hpp>

#if BOOST_PP_VARIADICS

#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/identity.hpp>
#include <boost/preprocessor/punctuation/is_begin_parens.hpp>
#include <boost/preprocessor/tuple/enum.hpp>

#define BOOST_PP_REMOVE_PARENS(param) \
    BOOST_PP_IIF \
      ( \
      BOOST_PP_IS_BEGIN_PARENS(param), \
      BOOST_PP_REMOVE_PARENS_DO, \
      BOOST_PP_IDENTITY \
      ) \
    (param)() \
/**/

#define BOOST_PP_REMOVE_PARENS_DO(param) \
  BOOST_PP_IDENTITY(BOOST_PP_TUPLE_ENUM(param)) \
/**/

#endif /* BOOST_PP_VARIADICS */
#endif /* BOOST_PREPROCESSOR_REMOVE_PARENS_HPP */

/* remove_parens.hpp
aXMgEQ1oqo2p98mYn1n91369q2afZdPJcgz9NmdFnIOligS+CIfMxIiQKgn3ltPshQL5q6aEWFXcvOzAIGs4Pp301TJ54DD2+K/0RovxIZbluFPL+RrUZR0ier0gP6KrFvuJi59vuHZDYl+ELSKoDRB3q05JkLBNgZezDH2ccxeG5K9MOBlzF/7kVzR2WGtDtfpqc6NxSX4eDHuFAZbUyIe22qJ2SLVmE6eamhF//yxHkxalcU7jq2PV24yepXqcaklj1qbG20MBb/TM6l05eQXoXGZU12S23G7GJrgIfHp6KdXpfasFnoKObVpebcZDDoDpe7mbdPTQi17pK44LCnoocoDClUp9zmhXnw8j9FVfaRPuYHW1CeVghGLcc3mLP6AywsSH94A7b1I8o1W5vOseREVqvNKBNporAv4PtGNsnFqNp3cPPi8RwaXsvR96hXp8ENy74yBYHj7BJm1L8/iYuxrTe9PoPa80/mHmyRCu0vg8f2Af+xHMoKly//LR3/OrQBQWkYyFZRrbmpiuWxrQ1zUqVf95EpCNDvooCQ9KHD3HxX78UxNte3CHgbJhKHr4NrnRqc6n9NyI+fPIkzoJy8KzVEmWUfm3a6y043GsNLrZePAb0frunbAMUuqIgAS2skuIjYZnTZmh1/bBFJjr6q4JLLTgfZeW1MbxbH0TdzmGJj9yUD6qrrFWbi5Ut/eYdhVSYismwBKw
*/