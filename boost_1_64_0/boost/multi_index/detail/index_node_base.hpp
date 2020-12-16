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
Xr+vznpVWwpx8iwhNGkO6uDDiW1FdsBWMnXAFqujU/XJuWJ08FfN+g+KR0Ru1MdC+lwaz0ymdL+dGa8o8gnxTOfcORUyoG14Hsx49nduxQXz3G3OmLpPrLpeT91ZYaoVeEu9HQeOHyw3c9cnVDrsgq5KF471tpU/l99V+fZ2Vc8268j7KUzNqnaA1XwG3/nPjfM5e3udK1PN+vBHSNe0WAXShpv5V6jwR5O9x1e0btFE5Nv8nGnEHtQ0+I18d/Pt2vVrpVruvMjf3s47vZ3R3uE7mn1LEDRUJjUsvQzt3Rat3Z3yTxm748vWPKTiBMO7fM3Wd3u9tuOVPqnhQeavL3+e8nXqEz4c+vDq8tSewd74CsXu6ZNXG/sIg/3iAfOD+lWR+2g7okxsQIrsm+/GzS8QHEyGFzuqVl1j5Lc39UpmpLPPn4hf6yp7qcuKMzV1HvV8Ik9nUwnmLIrHlKv64gQerAfi100e1/4LvOo2MFdG38yJ5YJ/D7fq9xqHw876FuK//5/wG13A49p5jn3DNpUTA5j5U3tG744352CeOgiUhVyFo+9HGN6G1iiyghg/Cn0+vmHO2I4qsLY3L/faHbUtYtKPzYzSX4zp8J9JX2f42WlM13hc676GfLNR23f0yxqoooOhPiW4rz0eyUCEOf0XZ0x5TXGnTDqWF4pr0n95Bsuri0vSsbxQXGPj/eoM5k2znnoop41PE806GAbQQlPfXbXabvpfG8HzYK9BOTX9v2oOvVf1p4fDGY0Mn97YVL9RMrgC6QkN7S2wn9B00iR9Rw33KV7Zonq30RvsqjDPJJ7dP8cwu/W+wb/Zu+7wqIogPimQiFFicqQgKioqKGASIsZ+CGjUoFGiokbjJXchZ8odd5cQrNixx94Ve1dU7A1719ixY8feO5ad3dm53ZdE8fvc94/mg9xlZ9/O7u/N7s7Ozs5SY8xYfamsAfJqQTbOcB2fbeQ1+HKsgUEmPRGabdiy6gcjjcWc14c/yfS+Iq73XVR8JS2XQmEy0gOD0un7czrGotTpKSv/iBxOx/xSjr72yiOn9y+P33jkkdMteTTzc/2xmkZ+rD+nG/m5/lhNI7+uv66+YVcy+icLojl1GHlH7tE3L0uhitjKNtEFNCc2dNnzjFwz6jnGzGONtdCh57avzDz9j8fMc5GZ1x6DOU8v5xl43N2X8iQjLTR/YSshxWuLVyQdZ3OxEavsazjZkcExFTHsE82qLFqbCRONwE3srsyW2rvoQuzTQvm4fZwx0tEVFVF1cUVglJvomz8mlhDRFC1t2a+G8mkXMJ0LA/BinfF96DIP5r1ZYQhK2QViPj3vHEH5pGaSwjzQrfE91qI1CLVFDEMyC0T6yEbIIxtGniVmHls2IiwbnOcfyEZoOWQj1Ec2eB+37AGZh7CBltV1+TLd02Rjz3aB0ud21Ibbukgj6/7Bu0iPl+pbDEf/hriyjqqgTqjEb7dddXDP9H5yj8YZGRlylH+fpd/1Lx1JqNbrxVrFm8VTymVQPW6KqqiQcISaEwxOn1QtlhMZ22vM7pTPbzWqoUErKeg5HQtzE4K1k2on4hoEW6G/76zTRJNAlwV39S0r0vHPysJ5PJqPhZEPDurVuPTAviPW3d9tJcYxkk8RoCLa3tnOWCdbos0pHO+kvYrHxoGHRsrbyWPjXw6N0haOhvpxstxo0ng9eLe3HGTWFXl+xPFd5lH3mdIiN5QyuuN4yjeybz6WQbP3VhDvsX9drlklqVM8n882nB31knD6hApJezFNm7LTdF4vDvwcrROxHjQA4+V1Us/5VbRFZKzbbmul94zEPcmt96ibis+QHsQyDMqGnBlkHtOnTkZ7PtfB4MM=
*/