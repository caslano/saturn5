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
qjGO2sxr6bfnzqklXpx8PDv6HIXQejAnIklRGLP+HNcXzVHe4bti5Sqlh5H54B4oHpGGUimt3U+cKIpFvZ1JNovyjw46D3y6HTK4Ne2ZF70r/r4u/i4Rfxe1582L5neHOF3DOC2KhHX5U8PpWPIa/ZoQOpNWNWHzSS/jnoSAvc/Y3OtbwubvviVs7vQeY7Ok/OsBxmYJ9j2XC2yWlH69RVFFZyGZvbTM2hHPal2nUUUWrojq60ELpkb0cxvCV9BAZdOrgP9dbmPRDyuUoRCWg0t1k5XVejm/Uppj1SH1tNGFTJEfMOYy/dx7THW8dhkhbffEs8LAzgBAgyQl4lNVFYBPBKyDJdJeQPYYLbM9zC/mxlq4ak06MxPaeAyDHR8ZZBGo/lZKksvCPYdN2QvDsQ+uQsOhulhd7dFvyWCMUnw3XQDuoTUjAT6GvRmoM7ou76T8viyOpnJ1hkDG/6HtS+CiqtrGZwYGRgQHl1HMjQoTw4rCCpoWJkHv5KBYWvjmQplGi4XJKGaaNZBM1ynLFnvferPdyso211IQFVxS1FLUfNU2L07lUimu9/8s5965wxbf/3u/fuHce+65557lOc959mcWzUm+pg2W5Oy5knk2Bp2UZ6O88pXlKiz7xduyApEWV0V9jEzPXrl4W0RNxekYUuW3STKFZYHQPL7itMHqrrqpun9/qn5iBRLFjvn3TN4x+bxjENpEar2k
*/