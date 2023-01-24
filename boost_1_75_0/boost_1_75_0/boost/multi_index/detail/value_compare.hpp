/* Copyright 2003-2015 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_VALUE_COMPARE_HPP
#define BOOST_MULTI_INDEX_DETAIL_VALUE_COMPARE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/call_traits.hpp>

namespace boost{

namespace multi_index{

namespace detail{

template<typename Value,typename KeyFromValue,typename Compare>
struct value_comparison
{
  typedef Value first_argument_type;
  typedef Value second_argument_type;
  typedef bool  result_type;

  value_comparison(
    const KeyFromValue& key_=KeyFromValue(),const Compare& comp_=Compare()):
    key(key_),comp(comp_)
  {
  }

  bool operator()(
    typename call_traits<Value>::param_type x,
    typename call_traits<Value>::param_type y)const
  {
    return comp(key(x),key(y));
  }

private:
  KeyFromValue key;
  Compare      comp;
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* value_compare.hpp
NwbG0er6zTkkfkdIK23Eou8IO6BSlU//Oq2GbUOoW9CwWq7yNFcLbV1JfrGsiQYLlXyq2WjfQ7PJDSvHK2ncbAhj0LYOn+Ny4yqtd3pfsM8ZcwaZC8BOYTVHHF3GY6wJ+0qt8s2f9BVFx8FQiufW0xYNjYdaoRNp2dO83AuNym85oOkaKoJ8ih81s67BHM7xA7HbbQoKFDcqHaewYLGt+L2iL7AEy2LEGceWaDkmJaEvG6L95OUQSd97ufq34n6zl3OBrhXlX4nfL8TvIvH7tjfMJv/BBkHcaE2QuRlmwyy2KWY3EFdZT6NptdxGmYwpkH9zy3Z3iPIiJVIWjC8H2AxJvr5O8lUlhosk0ZpE+EEORxneFmWmmZkR4OZy7aW/Eqkjqt8kkkY+iEK1MZRwJdV3T1K6KZghPO0Gk3N5D9S7JGDcEtrvQFu0pWqSfGd8sB2Kt1g2+gdQ+cR/VcyaCaxaN3xtpiTfnojiAS/REGvn0PsF0rIR/J/VnTHQZi+RiWXqiSxrAdpAFJqWIxelrP3NjF4lsDeBTspMlPwJ7OafFz/Bl59g4qpkbyl4XrmcJOk48lePA7Wnrmswh07F/mT5eVU12EwCK/9AeGAtZfiZ0+F+xciDwlRcCryATbmESI7bgGHpiBwB8LbKyWPwMd/FJhE/f1y8KWRHo8UmKAQoKE7w+AsTNaYzg2MgExiMtQX7aDOe4JY746TF
*/