/* Copyright 2003-2015 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_ORDERED_INDEX_HPP
#define BOOST_MULTI_INDEX_ORDERED_INDEX_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/multi_index/detail/ord_index_impl.hpp>
#include <boost/multi_index/ordered_index_fwd.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* no augment policy for plain ordered indices */

struct null_augment_policy
{
  template<typename OrderedIndexImpl>
  struct augmented_interface
  {
    typedef OrderedIndexImpl type;
  };

  template<typename OrderedIndexNodeImpl>
  struct augmented_node
  {
    typedef OrderedIndexNodeImpl type;
  };

  template<typename Pointer> static void add(Pointer,Pointer){}
  template<typename Pointer> static void remove(Pointer,Pointer){}
  template<typename Pointer> static void copy(Pointer,Pointer){}
  template<typename Pointer> static void rotate_left(Pointer,Pointer){}
  template<typename Pointer> static void rotate_right(Pointer,Pointer){}

#if defined(BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING)
  /* invariant stuff */

  template<typename Pointer> static bool invariant(Pointer){return true;}

#endif
};

} /* namespace multi_index::detail */

/* ordered_index specifiers */

template<typename Arg1,typename Arg2,typename Arg3>
struct ordered_unique
{
  typedef typename detail::ordered_index_args<
    Arg1,Arg2,Arg3>                                index_args;
  typedef typename index_args::tag_list_type::type tag_list_type;
  typedef typename index_args::key_from_value_type key_from_value_type;
  typedef typename index_args::compare_type        compare_type;

  template<typename Super>
  struct node_class
  {
    typedef detail::ordered_index_node<detail::null_augment_policy,Super> type;
  };

  template<typename SuperMeta>
  struct index_class
  {
    typedef detail::ordered_index<
      key_from_value_type,compare_type,
      SuperMeta,tag_list_type,detail::ordered_unique_tag,
      detail::null_augment_policy>                        type;
  };
};

template<typename Arg1,typename Arg2,typename Arg3>
struct ordered_non_unique
{
  typedef detail::ordered_index_args<
    Arg1,Arg2,Arg3>                                index_args;
  typedef typename index_args::tag_list_type::type tag_list_type;
  typedef typename index_args::key_from_value_type key_from_value_type;
  typedef typename index_args::compare_type        compare_type;

  template<typename Super>
  struct node_class
  {
    typedef detail::ordered_index_node<detail::null_augment_policy,Super> type;
  };

  template<typename SuperMeta>
  struct index_class
  {
    typedef detail::ordered_index<
      key_from_value_type,compare_type,
      SuperMeta,tag_list_type,detail::ordered_non_unique_tag,
      detail::null_augment_policy>                            type;
  };
};

} /* namespace multi_index */

} /* namespace boost */

#endif

/* ordered_index.hpp
BV9SrqzXKWoyTV5PkZjkCLUShnQl1T9do20a22vOlC75N4BgLubj9ItCLpnsfc4lZvZxpMJb66wifb6c36BdPLIR56FKWQwURLtWVWE1kgMHHBMe07L5LgSeRbWlL3HZywrZWTPgWC3uZyrVp2Ck1pOiFZqF5XV2UV6LCtEgX1l1ijoI1+7sFXdylUVwZ9PPtoIfrcKzFfdXmr/wAxusHJqRT8EYIjOJW7uaK65SaoDr+WrEO9g1X0fFujJ6g5VdU6nVV+XijHqq1M7obWvhjCJfMI2UXiuX88qm+YkArRezV51GVXTlRSIsV0QaLEzhKsjfWXRHXfE5JKw9s55BjDJAxKFU1q8XYFCrG8uttC4qhPabHKXlz9P6VcHgWwbayzpEufpt8gFmVYQVbfOdcMOSSGoMN8o0HMozHsVpDV4B5/FbaDd8A9KJPI7uA0m1p7foZF64xz+KQtNt2f4e3qJjeeGYbl8ov3rqIAfKrARcqVDNv7paOADTmD9ZpofJjNEOc5X7tMN8ZYh2mKkM0g6zlCQ8rItyyWuEP7DhQBy8M9Icf5+8OMhd3pQYedcS4X/YSFdzhLF2uKxjLT0sHyB5RW5AeQ72CUmIgxLh4uuEoIiwiJusypGovAR9dykrV9k9kdLZYaKXnw9FEq6vtHDV6RvjkKNWYP2DcRz7jXeUF3+yWs5utubdBY98fChSi32qVsL09iPHaQ73
*/