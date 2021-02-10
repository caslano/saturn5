/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_INDEXED_BY_HPP
#define BOOST_MULTI_INDEX_INDEXED_BY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/mpl/vector.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp> 

/* An alias to mpl::vector used to hide MPL from the user.
 * indexed_by contains the index specifiers for instantiation
 * of a multi_index_container.
 */

/* This user_definable macro limits the number of elements of an index list;
 * useful for shortening resulting symbol names (MSVC++ 6.0, for instance,
 * has problems coping with very long symbol names.)
 */

#if !defined(BOOST_MULTI_INDEX_LIMIT_INDEXED_BY_SIZE)
#define BOOST_MULTI_INDEX_LIMIT_INDEXED_BY_SIZE BOOST_MPL_LIMIT_VECTOR_SIZE
#endif

#if BOOST_MULTI_INDEX_LIMIT_INDEXED_BY_SIZE<BOOST_MPL_LIMIT_VECTOR_SIZE
#define BOOST_MULTI_INDEX_INDEXED_BY_SIZE \
  BOOST_MULTI_INDEX_LIMIT_INDEXED_BY_SIZE
#else
#define BOOST_MULTI_INDEX_INDEXED_BY_SIZE BOOST_MPL_LIMIT_VECTOR_SIZE
#endif

#define BOOST_MULTI_INDEX_INDEXED_BY_TEMPLATE_PARM(z,n,var) \
  typename BOOST_PP_CAT(var,n) BOOST_PP_EXPR_IF(n,=mpl::na)

namespace boost{

namespace multi_index{

template<
  BOOST_PP_ENUM(
    BOOST_MULTI_INDEX_INDEXED_BY_SIZE,
    BOOST_MULTI_INDEX_INDEXED_BY_TEMPLATE_PARM,T)
>
struct indexed_by:
  mpl::vector<BOOST_PP_ENUM_PARAMS(BOOST_MULTI_INDEX_INDEXED_BY_SIZE,T)>
{
};

} /* namespace multi_index */

} /* namespace boost */

#undef BOOST_MULTI_INDEX_INDEXED_BY_TEMPLATE_PARM
#undef BOOST_MULTI_INDEX_INDEXED_BY_SIZE

#endif

/* indexed_by.hpp
k4oKv+MUN4EVNintppsmJq/HXtchY9wO/KBv91yr3Es3wMmRPfKqzKhUQW8VMXOIsPJPGe1lFSszM7ADr4PEW/UNE7Ph7KyXIEjWdcoqaHiqsbWhTphFK7AirZFgZ71EqZahgW3mEnvWRvQoeNJASypscaEhqfOAVi6eqLHZk7Itg5aVXk5mSh2QYUxQZFkQ+reU7WSQ/iAc9x33s9d3nde1JLvkokFtKIVf8qq4PeK1G/Z16Hm94XjkhgHyntZhjr0n9mcNrNh6A9YZYHk9UHFPuGbtbSR33H7J7L9q6/eUvMdKfK1S6ohgk/kbAVfDz1d1rB2xSQVUfh7A2TLeHkxnW52jymxh7IKUJQVRsJ9bZWS89ZXucaHnTQ3cncfzx8Vo7HeK3MU6ck31GSKgSAMMtWjBzeWDzbFiRHQRNEcfFRWsPOsCgoXxOrzx/UNF4b0pH2XsUvXYCeWjnjoc8of9cCw1an8hyTd1OeikxmxX5w0/4GRYWIr8sPGV7pWIDTdsTO94oQxna9WMfNjppU1Fp7OTBq3tfulgp2guAMWtPLV+aA/dUbf9P2B+PI0Kv232Tp1bt3PnjzrGjB0/fHv+71rNwsEF9WosTgWcAYzGfdOAnsHb9q+0eombx1fFdYHRX3V/H6wfcK6E
*/