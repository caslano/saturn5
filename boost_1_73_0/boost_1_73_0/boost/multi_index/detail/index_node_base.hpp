/* Copyright 2003-2016 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_INDEX_NODE_BASE_HPP
#define BOOST_MULTI_INDEX_DETAIL_INDEX_NODE_BASE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/type_traits/aligned_storage.hpp>
#include <boost/type_traits/alignment_of.hpp> 

#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
#include <boost/archive/archive_exception.hpp>
#include <boost/serialization/access.hpp>
#include <boost/throw_exception.hpp> 
#endif

namespace boost{

namespace multi_index{

namespace detail{

/* index_node_base tops the node hierarchy of multi_index_container. It holds
 * the value of the element contained.
 */

template<typename Value>
struct pod_value_holder
{
  typename aligned_storage<
    sizeof(Value),
    alignment_of<Value>::value
  >::type                      space;
};

template<typename Value,typename Allocator>
struct index_node_base:private pod_value_holder<Value>
{
  typedef index_node_base base_type; /* used for serialization purposes */
  typedef Value           value_type;
  typedef Allocator       allocator_type;

#include <boost/multi_index/detail/ignore_wstrict_aliasing.hpp>

  value_type& value()
  {
    return *reinterpret_cast<value_type*>(&this->space);
  }

  const value_type& value()const
  {
    return *reinterpret_cast<const value_type*>(&this->space);
  }

#include <boost/multi_index/detail/restore_wstrict_aliasing.hpp>

  static index_node_base* from_value(const value_type* p)
  {
    return static_cast<index_node_base *>(
      reinterpret_cast<pod_value_holder<Value>*>( /* std 9.2.17 */
        const_cast<value_type*>(p))); 
  }

private:
#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
  friend class boost::serialization::access;
  
  /* nodes do not emit any kind of serialization info. They are
   * fed to Boost.Serialization so that pointers to nodes are
   * tracked correctly.
   */

  template<class Archive>
  void serialize(Archive&,const unsigned int)
  {
  }
#endif
};

template<typename Node,typename Value>
Node* node_from_value(const Value* p)
{
  typedef typename Node::allocator_type allocator_type;
  return static_cast<Node*>(
    index_node_base<Value,allocator_type>::from_value(p));
}

} /* namespace multi_index::detail */

} /* namespace multi_index */

#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
/* Index nodes never get constructed directly by Boost.Serialization,
 * as archives are always fed pointers to previously existent
 * nodes. So, if this is called it means we are dealing with a
 * somehow invalid archive.
 */

#if defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP)
namespace serialization{
#else
namespace multi_index{
namespace detail{
#endif

template<class Archive,typename Value,typename Allocator>
inline void load_construct_data(
  Archive&,boost::multi_index::detail::index_node_base<Value,Allocator>*,
  const unsigned int)
{
  throw_exception(
    archive::archive_exception(archive::archive_exception::other_exception));
}

#if defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP)
} /* namespace serialization */
#else
} /* namespace multi_index::detail */
} /* namespace multi_index */
#endif

#endif

} /* namespace boost */

#endif

/* index_node_base.hpp
vSnIAsVAuz+F4bQNM6q5DuBmGF9F1zHc9CeTfhjfQnQJ/fDWkn0YhhdYeo7BFLDHUjGNwRXwRSk4S5uYr/d0W9/zIhFVyqBtmMZStVs7JtwFwprXVlxoIVDYtnXBFimbVXNHoflHRgzcKG5YVJmyMt695Cl0SqMCaGbtsPooED8LoPbCBDK68HtbPFeMYlG+jaelDTU8wbpqPi+wMEIWczwAVNSsUwTDKRyhJy9wY+K6vSSnCjrXk5Hf+qcFNSJfeffQdI6TicTF25+lATr2FCBZeD0aWaMlxDo29ABzIWdUEF5w41kAeT+Kzvoj0h+NfOfAqH6qpy3Thk0zg8fGWQMXKxrHZDyJ/rwNsCHMrGpC1fzY70G3g6fE2IaQcYV1TQBr/VWem8kwHlxeh+fxMAoD6GzUzu99FXk16F8MJrvQOrH71NfYAN6M9gT5YzA5i6aDf+GJQwC2bHtUx/HY5S6+DsPBqCFGiKvoKVhv4uDYQzKpFstqYEUzV7gBiT7Ad6cO4IPdIwBZqbDemacNLh63aPtAnxykL5D5kGEDZSm6tDavlPYDHv5aA+K8A+3fFe1gy4WQyyEGJwG+jYahe/Mwqm9RwUYsu/2VkspzCp10aLZiPJjGZDCZkN/7v0UTcta/qGfnEpug20iJ
*/