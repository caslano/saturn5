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
juKTWEe6RwpEv/CDDZour6ZEvMU9yCV/qyewgFRUWBBxt3TlLnyE8ooFoidT+1zRnuo1AFjkvSmLfklVLkJKhP4uYqgn3KKlgLbHQIPf7LO0fBWGirJCnLMPK9mMInxzwjW1qzaz/EDi7sCdYcrZHuSICDDwu9fTa8kWIZZfrBjcSCOOxF6IlbZrz1LZbFuID6a4Fy1ABTuo24bZlXuILqMad6mP+cZtQt8XoxnODUzQ9X0NFtO9BkPfVxeB++lMM8pJXLOBy30tIoxEfE3aptnXLQKkKk1XbC65QB6lQDfu7ss1jRLIWqlFLWkVJh9MHYmKih1lrANcvob/rhfnJXiOVRTmixuz1pDpK1+c5oq/z1D7nUqheG56mWazNWoNUVaKi5AYpGy3P/+pmh4rFTycpJeZodo0hbvz2q3rhqqL4Tdi+cwt8Zt3wDo4qUZaNlNfSJWX/duIxcauKTxai7n+lMwnniiQn3bgOs2fzuGmeD8W7v+X7t8VozoS+P4wNiACWKikp/gYspPqodexFj30OlT8tqle74/xTKIpKUXGBzwUXviL3+C5A9dymCR/ao9JjQIUGBhlim+VPcNY2X+/Jcoi35XJJ14LFp65K9asAbvoM5ulkU4waB895zWT7NBElPlta2NW5Z8yLC0wOJOIHNpgX4OxbsJ1B+nMat3W1jCrb65uurdWOq2m/Gi8N3jq3f/LvUGYeW9g
*/