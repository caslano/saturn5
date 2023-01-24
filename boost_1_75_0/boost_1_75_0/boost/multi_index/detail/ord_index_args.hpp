/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_ORD_INDEX_ARGS_HPP
#define BOOST_MULTI_INDEX_DETAIL_ORD_INDEX_ARGS_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/multi_index/tag.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <functional>

namespace boost{

namespace multi_index{

namespace detail{

/* Oredered index specifiers can be instantiated in two forms:
 *
 *   (ordered_unique|ordered_non_unique)<
 *     KeyFromValue,Compare=std::less<KeyFromValue::result_type> >
 *   (ordered_unique|ordered_non_unique)<
 *     TagList,KeyFromValue,Compare=std::less<KeyFromValue::result_type> >
 *
 * index_args implements the machinery to accept this argument-dependent
 * polymorphism.
 */

template<typename KeyFromValue>
struct index_args_default_compare
{
  typedef std::less<typename KeyFromValue::result_type> type;
};

template<typename Arg1,typename Arg2,typename Arg3>
struct ordered_index_args
{
  typedef is_tag<Arg1> full_form;

  typedef typename mpl::if_<
    full_form,
    Arg1,
    tag< > >::type                                   tag_list_type;
  typedef typename mpl::if_<
    full_form,
    Arg2,
    Arg1>::type                                      key_from_value_type;
  typedef typename mpl::if_<
    full_form,
    Arg3,
    Arg2>::type                                      supplied_compare_type;
  typedef typename mpl::eval_if<
    mpl::is_na<supplied_compare_type>,
    index_args_default_compare<key_from_value_type>,
    mpl::identity<supplied_compare_type>
  >::type                                            compare_type;

  BOOST_STATIC_ASSERT(is_tag<tag_list_type>::value);
  BOOST_STATIC_ASSERT(!mpl::is_na<key_from_value_type>::value);
  BOOST_STATIC_ASSERT(!mpl::is_na<compare_type>::value);
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* ord_index_args.hpp
38JEvO0J5GE5pvdDaIcVRZCfq4P8RA22BdQXPxMG9fo6PNcc1E/XoT4OoZ5huhnAn6fDgzxHNN0y7B8QsN85j6jGo+HMpoD47IM6xF93ECE+MxzaUwn1WI/X6NCeSPw74ReksP1zxAwATKK5n4Z/JWEjw/AfyfB/ogn4XxDCx352VUH4T2H4n2syKhyEOntYLPSZ0LKYZNx7sBmynEftgX+adQz9rNgXBWJfLNDWY2yz+yK7xX1RIPZFWYN9wbvU0ftlw74oC9sXGq7qgUwyGWqhQ3U2Z6rOU3Olui/wBKFYyDDHnMccgRVu4uFmBW+dF0gKBtOEKsXAzdYJurMdnS6MivRzqFycQ9ViQ5WLDVWIk1IsVfGGjmx2TxU2sac2WCMaHx7a6JrdTriz60aHbankvrylcnFLzQ/fUnNDW6q3HLal9CVs/Zaa+zdbSgMt7QRsaUsh7OOWqhxOWwo3R+MtdXyfvqUO7TNxzL6wPZXPe+rf3+h7ChUSWTDZw7NoSmFj5XvkOhxwuVlDgnBTQzc8P/ohE77Romij/XG8iY22kEFH7LdltNF6v9GHjeXCbfm+UX6zoaWnzNMDe81rErMPfRml7bVfeK/NMNlL9oq9Vij22kJtoT5sdq891+JeKxR7bW6DvcYYwbF8nmGvzQ3ba1pUxP6014Drll9Iqobu+SnQPJp7IveeJeN0s4wGplvNzSSjIH0LppsN
*/