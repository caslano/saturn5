/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_IS_NOTHROW_EQ_COMPARABLE_HPP
#define BOOST_POLY_COLLECTION_DETAIL_IS_NOTHROW_EQ_COMPARABLE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/poly_collection/detail/is_equality_comparable.hpp>
#include <type_traits>
#include <utility>

namespace boost{

namespace poly_collection{

namespace detail{

template<typename T,typename=void>
struct is_nothrow_equality_comparable:std::false_type{};

template<typename T>
struct is_nothrow_equality_comparable<
  T,
  typename std::enable_if<
    is_equality_comparable<T>::value
  >::type
>:std::integral_constant<
  bool,
  noexcept(std::declval<T>()==std::declval<T>())
>{};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* is_nothrow_eq_comparable.hpp
fE03Qpd5L9R00+nn+zXemm6LdLr2jkrSraxkzIzyUJka94tV/RhGxO3Fqn4u+iV+F38l7pe46cq3XRX9phSX2c1Ssu9yXT+CkfS/UtdPo1/l1/mr8+pXu+jqe3hFP61dLtN1k9redbpeEu16v8pTbgezfCpNf7cv6TNtysTQWN4WejH6DapODkaeI1+u6uaJWeH3kMNij2NWemFSxR/JM2XlmPnsAHTot+i5jWIcf9ym5zeNvsrv5k/U5Dre4UE=
*/