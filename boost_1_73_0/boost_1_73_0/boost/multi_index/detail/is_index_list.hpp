/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_IS_INDEX_LIST_HPP
#define BOOST_MULTI_INDEX_DETAIL_IS_INDEX_LIST_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/mpl/empty.hpp>
#include <boost/mpl/is_sequence.hpp>

namespace boost{

namespace multi_index{

namespace detail{

template<typename T>
struct is_index_list
{
  BOOST_STATIC_CONSTANT(bool,mpl_sequence=mpl::is_sequence<T>::value);
  BOOST_STATIC_CONSTANT(bool,non_empty=!mpl::empty<T>::value);
  BOOST_STATIC_CONSTANT(bool,value=mpl_sequence&&non_empty);
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* is_index_list.hpp
urbnZE+qQ6bGY9i6Gfy2CpRUv0yNx7D1C9BtwQUn7vakJmVqPMZTKL9kqX6S79VXl+HFlCCPzsz0eAS2UyLAyO14JD92W167KlxWUVW/Ohyh90iiYXBf3mqsL1sb3li2orquYq0AV1bVllfTv1UNq/khFvlZktpwBAURaYiSlnAFvUgknn1pqq+LRElPVe0qZMDzVeXV4lx5dRhPVdRVht1dw8O1FWKPQXmc7yFtvFIW+8MMq8rqI3UryulbTfQ=
*/