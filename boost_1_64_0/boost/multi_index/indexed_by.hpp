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
kuXAqb3WT6LeZbz0ZHj432S3xxZgIApZcsmJBObCdGzQCTTO7wkZeIlZNaHWR5MOCCOGk7jKmRMiqZPRIpC/1dx+VlZRhC10hzqqNW7MOKTHnIbnYVHdHJrhBAV7BpWWVYonAb4QG+Kiqidc+e3C54y3THi/qhKPWoJHaWzWj1/myktDupB90TN3nu0SJCln1tgJLLJ8XVyLPmWM4/PpoRhElVKKXszv4SVsMYXTrDiIWJXPKB8aJ924vkMGY85JAPtfWdXyNf3Eh32Oy0teHha+80aPpoCpc4JuDwBOF6cRep00HwqmxCImgn4IddwnqCpvBURu+BIpc0QCRJsibid7v9t2aYGnp9nKQzMsg7gq3qZNwAQSRLZM66xU/uae4YDla8S8SDpckavOI/Ca8oIz/jOa6NbF1cYbbjZdqLHQo7sjsL1KdQPdZ2x6UENpcTrAiHZZaENAjqs9OlzahDBONQlA9PnFH6MNBjll2q+xlGenzhUYNC6PF9JzXbAGghIRaiixPAkKKcSjJJd+GcILgcTNQLWDoh1kKAowXgSsxSZlZK5ANHPa+w==
*/